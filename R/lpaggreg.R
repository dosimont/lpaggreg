require(inline)
require(Rcpp)
require(RcppArmadillo)

source("functions.R")
library(sets)

#Modify
lpaggreg_location="/opt/ptools/lpaggreg";
#Don't touch
cxxflags=paste("-I",lpaggreg_location,"/include/ -std=c++11", sep="");
libs=paste("-L",lpaggreg_location,"/lib/ -llpaggreg -Wl,-rpath=",lpaggreg_location,"/lib/", sep="");
Sys.setenv("PKG_CXXFLAGS"=cxxflags);
Sys.setenv("PKG_LIBS"=libs);

src <- '
  // Enable C++11
  // [[Rcpp::plugins(cpp11)]]

  #include <RcppArmadillo.h>
  // [[Rcpp::depends(RcppArmadillo)]]

  #include <iostream>
  #include <vector>
  #include <map>
  #include <memory>
  #include <lpaggreg/oqualities.h>
  #include <lpaggreg/opartitioner.h>
  #include <lpaggreg/ovaluesn.h>  
  #include <lpaggreg/hqualities.h>
  #include <lpaggreg/hpartitioner.h>
  #include <lpaggreg/hvaluesn.h>
  #include <lpaggreg/dqualities.h>
  #include <lpaggreg/dpartitioner.h>
  #include <lpaggreg/dvaluesn.h>  

  using namespace Rcpp;
  using namespace arma;
  using namespace std;
  using namespace lpaggreg;
 
  
  vector<vector<vector<double> > > convertToMicroModel(NumericVector micro){
    NumericVector vecArray(micro);
    IntegerVector arrayDims = vecArray.attr("dim");
    arma::cube cubeArray(vecArray.begin(), arrayDims[0], arrayDims[1], arrayDims[2], false);
    vector<vector<vector<double> > > micromodel;
    for (int i=0; i<arrayDims[0]; i++){
      micromodel.push_back(vector<vector<double> >());
      for (int j=0; j<arrayDims[1]; j++){
        (micromodel[i]).push_back(vector<double>());
        for (int k=0; k<arrayDims[2]; k++){
          (micromodel[i][j]).push_back(cubeArray(i, j, k));
        }
      }
    }
    return micromodel;
  }

  vector<int > convertToHierarchy(NumericVector h){
    NumericVector vecArray(h);
    vector<int> hierarchy;
    for (int i=0; i<vecArray.size(); i++){
      hierarchy.push_back(vecArray(i)-1);
    }
    return hierarchy;
  }
  
  // [[Rcpp::export]]
  NumericMatrix oaggregate(NumericVector micro, SEXP th) {
    float threshold=as<float>(th);
    shared_ptr<OValuesN3> values = shared_ptr<OValuesN3>(new OValuesN3(convertToMicroModel(micro)));
    OQualities qualities = OQualities(values);
    qualities.computeQualities();
    qualities.normalize();
    OPartitioner partitioner = OPartitioner(qualities);
    partitioner.computeBestPartitions(threshold);
    list< tuple<float, int, int> > partitionsTuples=partitioner.getPartitionsTuples();
    NumericMatrix matrixResults(partitionsTuples.size(),3);
    int i=0;
    for (tuple<float, int, int> line: partitionsTuples){
      matrixResults(i, 0)=get<0>(line);
      matrixResults(i, 1)=get<1>(line)+1;
      matrixResults(i, 2)=get<2>(line)+1;
      i++;
    }
  return matrixResults;
  }

  // [[Rcpp::export]]
  NumericMatrix haggregate(NumericVector micro, NumericVector h, SEXP th) {
    float threshold=as<float>(th);
    shared_ptr<HValuesN3> values = shared_ptr<HValuesN3>(new HValuesN3(convertToMicroModel(micro),convertToHierarchy(h)));
    HQualities qualities = HQualities(values);
    qualities.computeQualities();
    qualities.normalize();
    HPartitioner partitioner = HPartitioner(qualities);
    partitioner.computeBestPartitions(threshold);
    list< tuple<float, int, int> > partitionsTuples=partitioner.getPartitionsTuples();
    NumericMatrix matrixResults(partitionsTuples.size(),3);
    int i=0;
    for (tuple<float, int, int> line: partitionsTuples){
      matrixResults(i, 0)=get<0>(line);
      matrixResults(i, 1)=get<1>(line)+1;
      matrixResults(i, 2)=get<2>(line);
      i++;
    }
    return matrixResults;
  }

  // [[Rcpp::export]]
  NumericMatrix daggregate(NumericVector micro, NumericVector h, SEXP th) {
    float threshold=as<float>(th);
    shared_ptr<DValuesN3> values = shared_ptr<DValuesN3>(new DValuesN3(convertToMicroModel(micro),convertToHierarchy(h)));
    DQualities qualities = DQualities(values);
    qualities.computeQualities();
    qualities.normalize();
    DPartitioner partitioner = DPartitioner(qualities);
    partitioner.computeBestPartitions(threshold);
    list< tuple<float, int, int, int, int> > partitionsTuples=partitioner.getPartitionsTuples();
    NumericMatrix matrixResults(partitionsTuples.size(),5);
    int i=0;
    for (tuple<float, int, int, int, int> line: partitionsTuples){
      matrixResults(i, 0)=get<0>(line);
      matrixResults(i, 1)=get<1>(line)+1;
      matrixResults(i, 2)=get<2>(line);
      matrixResults(i, 3)=get<3>(line)+1;
      matrixResults(i, 4)=get<4>(line)+1;
      i++;
    }
    return matrixResults;
  }
'

sourceCpp(code=src, verbose=TRUE, rebuild=TRUE)

#Synthetic example: 2 processes, 2 types, 5 timeslices (keep the same order)
testArray = array(dim=c(2,2,5))
testArray[1,1,] = c(0.5, 0.2, 0.0, 0.1, 0.4)
testArray[1,2,] = c(0.5, 0.8, 1.0, 0.9, 0.6)
testArray[2,1,] = c(0.4, 0.3, 0.1, 0.2, 0.3)
testArray[2,2,] = c(0.6, 0.7, 0.9, 0.8, 0.7)
print(testArray)
#Threshold: 0<th<1, lower value means more accuracy for retrieving the list of partitions but longer computation time
th=0.001
#Output: a 2D matrix (n,3) with the list of parts for each parameter
#Columns: parameter p, start timeslice, end timeslice
oaggregate(testArray, th)
#define hierarchy: vector[index]= index's father index; vector[index]0 means index=root
h=c(3,3,0)
#Columns: parameter p, node, size
haggregate(testArray, h, th)
#Columns: parameter p, node, size, start, end
daggregate(testArray, h, th)

trace <- read.table("cholesky_11520_960_starpu_25_3_dmda_1_idcin-2.grenoble.grid5000.fr_2016-08-21_20-49-12_pjdump.csv", sep=",", fill=TRUE, header=TRUE)

head(trace)
unique(trace$Nature)
unique(trace$ResourceId)
unique(trace$Type)
unique(trace$Value)
min(trace$Start)
max(trace$End)

subtrace <- trace[trace$Depth == 0,]
space <- unique(subtrace$ResourceId[substr(subtrace$ResourceId,1,1) == "C"])
space <- space[order(space)]
subtrace <- subtrace[subtrace$ResourceId %in% space,]

head(subtrace)
unique(subtrace$Nature)
unique(subtrace$ResourceId)
unique(subtrace$Type)
unique(subtrace$Value)
min(subtrace$Start)
max(subtrace$End)

stepNb <- 20
start <- min(subtrace$Start)
end <- max(subtrace$End)
step <- (end-start)/stepNb
time <- seq(start,end-step,step)

value <- unique(subtrace$Value)
value <- value[order(value)]

dataCube <- array(0,
                  dim = c(length(space), length(value), length(time)),
                  dimnames = list("space"=space, "value"=value, "time"=time)
)

dataCube[c("CPU0","CPU1"),"Idle",]

for (r in 1:nrow(subtrace)) {
  row <- subtrace[r,]
  for (t in time) {
    interval <- interval_intersection(interval(row$Start,row$End),interval(t,t+step))
    size <- 0
    if (!interval_is_empty(interval)) { size <- max(interval) - min(interval) }
    dataCube[as.character(row$ResourceId),as.character(row$Value),as.character(t)] <- dataCube[as.character(row$ResourceId),as.character(row$Value),as.character(t)] + size
  }
}


#apply(dataCube,c(1,3),sum)
step
value
dataCube

oaggregate(dataCube, th)
