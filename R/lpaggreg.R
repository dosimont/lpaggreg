require(inline)
require(Rcpp)
require(RcppArmadillo)

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
  NumericMatrix oaggregate(NumericVector micro) {
  
  shared_ptr<OValuesN3> values = shared_ptr<OValuesN3>(new OValuesN3(convertToMicroModel(micro)));
  OQualities qualities = OQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  OPartitioner partitioner = OPartitioner(qualities);
  partitioner.computeBestPartitions(0.001);
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
  NumericMatrix haggregate(NumericVector micro, NumericVector h) {
  shared_ptr<HValuesN3> values = shared_ptr<HValuesN3>(new HValuesN3(convertToMicroModel(micro),convertToHierarchy(h)));
  HQualities qualities = HQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  HPartitioner partitioner = HPartitioner(qualities);
  partitioner.computeBestPartitions(0.001);
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
  NumericMatrix daggregate(NumericVector micro, NumericVector h) {
  shared_ptr<DValuesN3> values = shared_ptr<DValuesN3>(new DValuesN3(convertToMicroModel(micro),convertToHierarchy(h)));
  DQualities qualities = DQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  DPartitioner partitioner = DPartitioner(qualities);
  partitioner.computeBestPartitions(0.001);
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
options(digits=12)

sourceCpp(code=src, verbose=TRUE, rebuild=TRUE)

#Synthetic example: 2 processes, 2 types, 5 timeslices (keep the same order)
testArray = array(dim=c(2,2,5))
testArray[1,1,] = c(0.5, 0.2, 0.0, 0.1, 0.4)
testArray[1,2,] = c(0.5, 0.8, 1.0, 0.9, 0.6)
testArray[2,1,] = c(0.4, 0.3, 0.1, 0.2, 0.3)
testArray[2,2,] = c(0.6, 0.7, 0.9, 0.8, 0.7)
print(testArray)
#Output: a 2D matrix (n,3) with the list of parts for each parameter
#Columns: parameter p, start timeslice, end timeslice
oaggregate(testArray)
#define hierarchy: vector[index]= index's father index; vector[index]0 means index=root
h=c(3,3,0)
#Columns: parameter p, node, size
haggregate(testArray,h)
#Columns: parameter p, node, size, start, end
daggregate(testArray,h)
