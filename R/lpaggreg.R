require(inline)
require(Rcpp)
require(RcppArmadillo)
library(sqldf)
library(dplyr)
library(ggplot2)
library(reshape2)
library(RColorBrewer)
library(digest)
library(treemap)
library(gplots)

hspace=0.1

string2colorRandom<- function(string){
  digested=digest(as.character(string), serialize=FALSE)
  r=substr(digested,1,10)
  r=digest(as.character(r), serialize=FALSE)
  g=substr(digested,11,20)
  g=digest(as.character(g), serialize=FALSE)
  b=substr(digested,21,30)
  b=digest(as.character(b), serialize=FALSE)
  r=substr(r,1,2)
  g=substr(g,1,2)
  b=substr(b,1,2)
  h<-paste(r,g,b,sep="")
  if ((r>230&g>230&b>230)|(r<30&g<30&b<30)){
    h = string2colorRandom(paste(string,":-o",string,sep=""))
  }
  h
}

color_generator <- function(stringlist, aggString=c("")){
  sorted<-sort(stringlist)
  hashcoded<-rep(0, length(stringlist))
  for (i in 1:length(sorted)){
    if (sorted[i]==aggString){
      hashcoded[i]=0
    }
    else{
      hashcoded[i]=string2colorRandom(sorted[i])
    }
  }
  hexed<-format(as.hexmode(hashcoded),width=6)
  color=paste("#",hexed,sep="")
  names(color)=sorted
  color
}

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

parsepjdump <- function (file){
  
  names <- c("Nature", "ResourceId", "Type", "Start", "End", "Duration", "Depth", "Value", "a", "b", "c", "d", "e", "f", "g")
  trace <- read.table(file, sep=",", fill=TRUE, header=FALSE, strip.white=TRUE, col.names=names)
  
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
  
  trace <- trace[!(trace$Nature %in% "Container"),]
  ret<-list("data"=trace,"resources"=resources)
  ret
}
  
pjdump2microstate <- function(trace, timeSliceNumber, enable_hierarchy=TRUE){
  
  data <- trace$data
  data <- data[data$Nature %in% "State",]
  
  #carefull, for spatial, only leaves should produce values!
  df <- slicer(data, timeSliceNumber)
  
  time <- unique(df$SliceId)
  time <- time[order(time)]
  
  value <- unique(df$Value)
  value <- value[order(value)]
  
  if (enable_hierarchy){
    resources <- trace$resources
    
    parents <- unique(resources$ParentId)
    parents<-parents[order(parents)]
    parents<-rev(parents)
    
    #remove parents from df
    df <- df[!(df$ResourceId %in% parents),]
  }

  space <- unique(df$ResourceId)
  space <- space[order(space)]
  
  if (enable_hierarchy){
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
  }else{
    vhierarchy=0
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
  h=1;
  while(i<=length(vhierarchy)){
    if (!(vhierarchy[path[h]] %in% path)){
      path[i]=vhierarchy[path[h]]
      i=i+1
    }
    h=h+1
  }
  path
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
  dfdata <- melt(micro$data)
  vhierarchy <- micro$hierarchy
  leavesize= length(unique(dfdata$Space))
  for (r in 1:nrow(df)) {
    df[r,"Space"]<-names(vhierarchy)[df[r,"Node"]]
  }
  path=getpath(vhierarchy,leavesize)
  for (h in 1:(length(path)-1)){
    dfdata2<-dfdata[dfdata$Space %in% names(vhierarchy)[path[h]],]
    dfdata2$Space<-names(vhierarchy)[vhierarchy[path[h]]]
    dfdata=rbind(dfdata,dfdata2)
  }
  agg <- dfdata[dfdata$Space %in% df$Space,]
  agg <- aggregate(value ~ Space+Type+Time, data = agg, FUN = sum)
  agg
}

qualplot <- function(results){
  qualities<-results$Qualities
  popt<-results$POpt
  opt<-qualities[(qualities$Parameter %in% popt),]
  xlabel<- "Information Loss"
  ylabel<- "Complexity Reduction"
  plot<-ggplot()
  plot<-plot + geom_line(data=qualities,aes(x=Loss,y=Gain), color="black")
  plot<-plot + geom_point(data=qualities,aes(x=Loss,y=Gain), color="black")
  plot<-plot + geom_point(data=opt,aes(x=Loss,y=Gain), color="red")
  plot<-plot + theme_bw()
  plot<-plot + labs(x=xlabel,y=ylabel)
  plot
}

oplot <-function(agg, FUN=color_generator){
  agg <- aggregate(value ~ Type+Start+End, data = agg, FUN = mean)
  agg$Duration<-agg$End-agg$Start+1
  vcolors=FUN(unique(agg$Type))
  p<-ggplot(agg, aes(x=Start+((End-Start)/2)+0.5-(hspace/2), y=value, width=Duration-hspace, fill=Type))
  p<-p + scale_fill_manual(values = vcolors, breaks = names(vcolors), labels = names(vcolors))
  p<-p + geom_bar(stat="identity")
  p<-p + theme_bw()
  p<-p + labs(x="Time slices",y="Normalized value")
  p
}

hplot <-function(agg, FUN=color_generator){
  agg <- aggregate(value ~ Space+Type, data = agg, FUN = mean)
  vcolors=FUN(unique(agg$Type))
  agg$Color=vcolors[agg$Type]
  treemap(agg, index=c("Space", "Type"), vSize="value", vColor="Color", type="color", algorithm="squarified", border.col="white", bg.labels="grey", title="")
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
List oaggregate(NumericVector micro, SEXP th) {
  float threshold=as<float>(th);
  shared_ptr<OValuesN3> values = shared_ptr<OValuesN3>(new OValuesN3(convertToMicroModel(micro)));
  OQualities qualities = OQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  OPartitioner partitioner = OPartitioner(qualities);
  partitioner.computeBestPartitions(threshold);
  list< tuple<float, int, int, lp_quality_type, lp_quality_type> > partitionsTuples=partitioner.getPartitionsTuples();
  NumericVector parameters(partitionsTuples.size());
  IntegerVector start(partitionsTuples.size());
  IntegerVector end(partitionsTuples.size());
  NumericVector gain(partitionsTuples.size());
  NumericVector loss(partitionsTuples.size());
  int i=0;
  for (tuple<float, int, int, lp_quality_type, lp_quality_type> line: partitionsTuples){
    parameters[i]=get<0>(line);
    start[i]=get<1>(line)+1;
    end[i]=get<2>(line)+1;
    gain[i]=get<3>(line);
    loss[i]=get<4>(line);
    i++;
  }
  DataFrame results = DataFrame::create(Named("Parameter")=parameters,
  Named("Start")=start,
  Named("End")=end,
  Named("Gain")=gain,
  Named("Loss")=loss);
  map<float, shared_ptr<Quality> > qualities2=partitioner.getQualityList();
  NumericVector parameters2(qualities2.size());
  NumericVector gain2(qualities2.size());
  NumericVector loss2(qualities2.size());
  i=0;
  for(auto it: qualities2){
    parameters2[i]=it.first;
    gain2[i]=it.second->getGain();
    loss2[i]=it.second->getLoss();
    i++;
  }
  DataFrame qualitydf = DataFrame::create(Named("Parameter")=parameters2,
  Named("Gain")=gain2,
  Named("Loss")=loss2);
  float popt=partitioner.getP(P_OPT);
  float auc=partitioner.computeAUC();
  return Rcpp::List::create(Named("Partitions") = results, Named("Qualities")= qualitydf, Named("POpt") = popt, Named("AUC") = auc);
}

// [[Rcpp::export]]
List haggregate(NumericVector micro, NumericVector h, SEXP th) {
  float threshold=as<float>(th);
  shared_ptr<HValuesN3> values = shared_ptr<HValuesN3>(new HValuesN3(convertToMicroModel(micro),convertToHierarchy(h)));
  HQualities qualities = HQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  HPartitioner partitioner = HPartitioner(qualities);
  partitioner.computeBestPartitions(threshold);
  list< tuple<float, int, int, lp_quality_type, lp_quality_type> > partitionsTuples=partitioner.getPartitionsTuples();
  NumericVector parameters(partitionsTuples.size());
  IntegerVector node(partitionsTuples.size());
  IntegerVector size(partitionsTuples.size());
  NumericVector gain(partitionsTuples.size());
  NumericVector loss(partitionsTuples.size());
  int i=0;
  for (tuple<float, int, int, lp_quality_type, lp_quality_type> line: partitionsTuples){
    parameters[i]=get<0>(line);
    node[i]=get<1>(line)+1;
    size[i]=get<2>(line);
    gain[i]=get<3>(line);
    loss[i]=get<4>(line);
    i++;
  }
  DataFrame results = DataFrame::create(Named("Parameter")=parameters,
  Named("Node")=node,
  Named("Size")=size,
  Named("Gain")=gain,
  Named("Loss")=loss);
  map<float, shared_ptr<Quality> > qualities2=partitioner.getQualityList();
  NumericVector parameters2(qualities2.size());
  NumericVector gain2(qualities2.size());
  NumericVector loss2(qualities2.size());
  i=0;
  for(auto it: qualities2){
    parameters2[i]=it.first;
    gain2[i]=it.second->getGain();
    loss2[i]=it.second->getLoss();
    i++;
  }
  DataFrame qualitydf = DataFrame::create(Named("Parameter")=parameters2,
  Named("Gain")=gain2,
  Named("Loss")=loss2);
  float popt=partitioner.getP(P_OPT);
  float auc=partitioner.computeAUC();
  return Rcpp::List::create(Named("Partitions") = results, Named("Qualities")= qualitydf, Named("POpt") = popt, Named("AUC") = auc);
}

// [[Rcpp::export]]
List daggregate(NumericVector micro, NumericVector h, SEXP th) {
  float threshold=as<float>(th);
  shared_ptr<DValuesN3> values = shared_ptr<DValuesN3>(new DValuesN3(convertToMicroModel(micro),convertToHierarchy(h)));
  DQualities qualities = DQualities(values);
  qualities.computeQualities();
  qualities.normalize();
  DPartitioner partitioner = DPartitioner(qualities);
  partitioner.computeBestPartitions(threshold);
  list< tuple<float, int, int, int, int, lp_quality_type, lp_quality_type> > partitionsTuples=partitioner.getPartitionsTuples();
  NumericVector parameters(partitionsTuples.size());
  IntegerVector node(partitionsTuples.size());
  IntegerVector size(partitionsTuples.size());
  IntegerVector start(partitionsTuples.size());
  IntegerVector end(partitionsTuples.size());
  NumericVector gain(partitionsTuples.size());
  NumericVector loss(partitionsTuples.size());
  int i=0;
  for (tuple<float, int, int, int, int, lp_quality_type, lp_quality_type> line: partitionsTuples){
    parameters[i]=get<0>(line);
    node[i]=get<1>(line)+1;
    size[i]=get<2>(line);
    start[i]=get<3>(line)+1;
    end[i]=get<4>(line)+1;
    gain[i]=get<5>(line);
    loss[i]=get<6>(line);
    i++;
  }
  DataFrame results = DataFrame::create(Named("Parameter")=parameters,
  Named("Node")=node,
  Named("Size")=size,
  Named("Start")=start,
  Named("End")=end,
  Named("Gain")=gain,
  Named("Loss")=loss);
  map<float, shared_ptr<Quality> > qualities2=partitioner.getQualityList();
  NumericVector parameters2(qualities2.size());
  NumericVector gain2(qualities2.size());
  NumericVector loss2(qualities2.size());
  i=0;
  for(auto it: qualities2){
    parameters2[i]=it.first;
    gain2[i]=it.second->getGain();
    loss2[i]=it.second->getLoss();
    i++;
  }
  DataFrame qualitydf = DataFrame::create(Named("Parameter")=parameters2,
  Named("Gain")=gain2,
  Named("Loss")=loss2);
  float popt=partitioner.getP(P_OPT);
  float auc=partitioner.computeAUC();
  return Rcpp::List::create(Named("Partitions") = results, Named("Qualities")= qualitydf, Named("POpt") = popt, Named("AUC") = auc);
}
'

sourceCpp(code=lpaggreg_src, verbose=TRUE, rebuild=TRUE)