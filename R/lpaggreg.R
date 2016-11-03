require(inline)
require(Rcpp)
require(RcppArmadillo)
library(sqldf)
library(dplyr)
library(ggplot2)
library(reshape2)

vspace=0.1

factor2numeric <- function(f)
{
  if(!is.factor(f)) stop("the input must be a factor")
  as.numeric(levels(f))[as.integer(f)]
}

slicer <- function (trace, timeSliceNumber)
{
  start <- min(trace$Start)
  trace$Start <- trace$Start - start
  trace$End <- trace$End - start
  maxts <- max(trace$End)
  slicets = maxts/timeSliceNumber;
  slices <- data.frame(SliceId=1:timeSliceNumber, TsStart=(0:(timeSliceNumber-1))*slicets, TsEnd=(1:timeSliceNumber)*slicets);
  h <- sqldf('SELECT trace.ResourceId, trace.Start, trace.End, trace.Duration, trace.Value, slices.SliceId, slices.TsStart, slices.TsEnd
             FROM trace
             INNER JOIN slices
             ON (trace.Start+trace.Duration > slices.TsStart) AND (trace.End-trace.Duration < slices.TsEnd)')
  h$Duration <- NULL;
  m <- h %>% group_by(ResourceId, Start, End, SliceId, Value) %>%
    mutate(N=n(), TinTS = (min(End,TsEnd) - max(Start,TsStart))) %>%
    group_by(ResourceId, SliceId, Value, TsStart, TsEnd) %>%
    summarize (Sum=sum(TinTS), Normalized=Sum/slicets) %>%
    as.data.frame();
  p <- expand.grid(ResourceId=unique(m$ResourceId), SliceId = 1:max(m$SliceId), Value = unique(m$Value));
  p$TsStart = 0;
  p$TsEnd = 0;
  p$Sum = 0;
  p$Normalized = 0;
  n <- rbind(p, m);
  o <- n %>% group_by (ResourceId, SliceId, Value) %>%
    summarize(TsStart = max(TsStart), TsEnd = max(TsEnd), Sum = max(Sum), Normalized=max(Normalized)) %>% as.data.frame;
  return (o);
}

parsepjdump <- function (file, timeSliceNumber){
  
  names <- c("Nature", "ResourceId", "Type", "Start", "End", "Duration", "Depth", "Value", "a", "b", "c", "d", "e", "f", "g")
  trace <- read.table(file, sep=",", fill=TRUE, header=FALSE, col.names=names)
  
  trace$a <- NULL
  trace$b <- NULL
  trace$c <- NULL
  trace$d <- NULL
  trace$e <- NULL
  trace$f <- NULL
  trace$g <- NULL
  
  resources <- trace[trace$Nature %in% "Container",]
  resources$Nature <- NULL
  resources$Type <- NULL
  resources$Start <- NULL
  resources$End <- NULL
  resources$Duration <- NULL
  resources$Value <- NULL
  resources$ParentId <- resources$ResourceId
  resources$ResourceId <- resources$Depth
  resources$Depth <- NULL
  
  #does not work, why???
  resources <- resources[!(resources$ResourceId %in% '0'),]
  
  subtrace <- trace[trace$Nature %in% "State",]
  
  #carefull, for spatial, only leaves should produce values!
  df <- slicer(subtrace, timeSliceNumber)
  
  time <- unique(df$SliceId)
  time <- time[order(time)]
  
  value <- unique(df$Value)
  value <- value[order(value)]
  
  parents <- unique(resources$ParentId)
  parents<-parents[order(parents)]
  parents<-rev(parents)
  
  #remove parents from df
  df <- df[!(df$ResourceId %in% parents),]
  
  space <- unique(df$ResourceId)
  space <- space[order(space)]
  
  hierarchy <- factor(c(as.character(space),as.character(parents)))
  hierarchy<-unique(hierarchy)
  names(hierarchy)=as.character(hierarchy)
  resources$ParentIndex=-1
  vhierarchy <- rep(-1,length(hierarchy))
  names(vhierarchy)=as.character(hierarchy)
  
  for (i in 1:length(vhierarchy)){
    resources[resources$ResourceId %in% hierarchy[i],"ParentIndex"]=match(resources[resources$ResourceId %in% hierarchy[i],"ParentId"],hierarchy)[1]
  }
  resources[1,"ParentIndex"]=0
  for (i in 1:length(vhierarchy)){
    vhierarchy[i]=resources[resources$ResourceId %in% hierarchy[i],"ParentIndex"]
  }
  
  dataCube <- array(0,
                    dim = c(length(space), length(value), length(time)),
                    dimnames = list("Space"=space, "Type"=value, "Time"=time)
  )
  
  for (r in 1:nrow(df)) {
    row <- df[r,]
    dataCube[as.character(row$ResourceId),as.character(row$Value),as.character(row$SliceId)] <- row$Normalized
  }
  ret<-list("data"=dataCube,"hierarchy"=vhierarchy)
  ret
}

getpath<-function(vhierarchy, leavesize){
  path <- rep(-1,length(vhierarchy))
  for (h in 1:leavesize){
    path[h]=h
  }
  i=leavesize+1;
  h=0;
  while(vhierarchy[path[h]]!=0){
    if (!(vhierarchy[path[h]] %in% path[i])){
      path[i]=vhierarchy[path[h]]
      i=i+1
    }
    h=h+1
  }
}

omacro <- function(df, micro, p){
  df <- df[df$Parameter %in% p,]
  dfdata <- melt(micro$data)
  dfdata$Start=-1
  dfdata$End=-1
  for (i in 1:nrow(df)){
    dfdata[dfdata$Time>=df[i,"Start"]&dfdata$Time<=df[i,"End"],"Start"]=df[i,"Start"]
    dfdata[dfdata$Time>=df[i,"Start"]&dfdata$Time<=df[i,"End"],"End"]=df[i,"End"]
  }
  agg <- aggregate(value ~ Space+Type+Start+End, data = dfdata, FUN = mean)
  agg
}

hmacro <- function(df, micro, p){
  df <- df[df$Parameter %in% p,]
  df$Space<-"Unknown"
  dfdata <- melt(micro$data)
  leavesize= length(unique(dfdata$Space))
  vhierarchy <- micro$hierarchy
  for (h in getpath(vhierarchy,leavesize)){
    df[df$Node %in% vhierarchy[h],"Space"]<-names(vhierarchy)[h]
    dfdata2<-dfdata[dfdata$ResourceId %in% names(vhierarchy)[h]]
    dfdata2$Space<-names(vhierarchy)[vhierarchy[h]]
    rbind(dfdata,dfdata2)
  }
  agg <- aggregate(value ~ Space+Type, data = dfdata, FUN = mean)
  agg
}

oplot <-function(agg){
  agg <- aggregate(value ~ Type+Start+End, data = agg, FUN = mean)
  agg$Duration<-agg$End-agg$Start+1
  print(agg)
  p<-ggplot(agg, aes(x=Start+((End-Start)/2)+0.5, fill = Type, y=value, width=Duration))
  p<-p + geom_bar(stat="identity")
  p<-p + theme_bw()
  p<-p + labs(x="Time slices",y="Normalized value")
  p
}

cxxflags=paste("-I",lpaggreg_location,"/include/ -std=c++11", sep="");
libs=paste("-L",lpaggreg_location,"/lib/ -llpaggreg -Wl,-rpath=",lpaggreg_location,"/lib/", sep="");
Sys.setenv("PKG_CXXFLAGS"=cxxflags);
Sys.setenv("PKG_LIBS"=libs);

lpaggreg_src <- '
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
DataFrame oaggregate(NumericVector micro, SEXP th) {
  float threshold=as<float>(th);
  shared_ptr<OValuesN3> values = shared_ptr<OValuesN3>(new OValuesN3(convertToMicroModel(micro)));
  OQualities qualities = OQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  OPartitioner partitioner = OPartitioner(qualities);
  partitioner.computeBestPartitions(threshold);
  list< tuple<float, int, int> > partitionsTuples=partitioner.getPartitionsTuples();
  NumericVector parameters(partitionsTuples.size());
  IntegerVector start(partitionsTuples.size());
  IntegerVector end(partitionsTuples.size());
  int i=0;
  for (tuple<float, int, int> line: partitionsTuples){
    parameters[i]=get<0>(line);
    start[i]=get<1>(line)+1;
    end[i]=get<2>(line)+1;
    i++;
  }
  DataFrame results = DataFrame::create(Named("Parameter")=parameters,
  Named("Start")=start,
  Named("End")=end);
  return results;
}

// [[Rcpp::export]]
  DataFrame haggregate(NumericVector micro, NumericVector h, SEXP th) {
  float threshold=as<float>(th);
  shared_ptr<HValuesN3> values = shared_ptr<HValuesN3>(new HValuesN3(convertToMicroModel(micro),convertToHierarchy(h)));
  HQualities qualities = HQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  HPartitioner partitioner = HPartitioner(qualities);
  partitioner.computeBestPartitions(threshold);
  list< tuple<float, int, int> > partitionsTuples=partitioner.getPartitionsTuples();
  NumericVector parameters(partitionsTuples.size());
  IntegerVector node(partitionsTuples.size());
  IntegerVector size(partitionsTuples.size());
  int i=0;
  for (tuple<float, int, int> line: partitionsTuples){
    parameters[i]=get<0>(line);
    node[i]=get<1>(line)+1;
    size[i]=get<2>(line);
    i++;
  }
  DataFrame results = DataFrame::create(Named("Parameter")=parameters,
  Named("Node")=node,
  Named("Size")=size);
  return results;
}

// [[Rcpp::export]]
  DataFrame daggregate(NumericVector micro, NumericVector h, SEXP th) {
  float threshold=as<float>(th);
  shared_ptr<DValuesN3> values = shared_ptr<DValuesN3>(new DValuesN3(convertToMicroModel(micro),convertToHierarchy(h)));
  DQualities qualities = DQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  DPartitioner partitioner = DPartitioner(qualities);
  partitioner.computeBestPartitions(threshold);
  list< tuple<float, int, int, int, int> > partitionsTuples=partitioner.getPartitionsTuples();
  NumericVector parameters(partitionsTuples.size());
  IntegerVector node(partitionsTuples.size());
  IntegerVector size(partitionsTuples.size());
  IntegerVector start(partitionsTuples.size());
  IntegerVector end(partitionsTuples.size());
  int i=0;
  for (tuple<float, int, int, int, int> line: partitionsTuples){
    parameters[i]=get<0>(line);
    node[i]=get<1>(line)+1;
    size[i]=get<2>(line);
    start[i]=get<3>(line)+1;
    end[i]=get<4>(line)+1;
    i++;
  }
  DataFrame results = DataFrame::create(Named("Parameter")=parameters,
  Named("Node")=node,
  Named("Size")=size,
  Named("Start")=start,
  Named("End")=end);
  return results;
}
'

sourceCpp(code=lpaggreg_src, verbose=TRUE, rebuild=TRUE)