library(Rcpp)
#Modify
lpaggreg_location="/opt/ptools/lpaggreg";
#Don't touch
cxxflags=paste("-I",lpaggreg_location,"/include/ -std=c++11", sep="");
libs=paste("-L",lpaggreg_location,"/lib/ -llpaggreg -Wl,-rpath=",lpaggreg_location,"/lib/", sep="");
Sys.setenv("PKG_CXXFLAGS"=cxxflags);
Sys.setenv("PKG_LIBS"=libs);
#Modify
cppFunction(rebuild = TRUE, showOutput = TRUE, 
'#include <Rcpp.h>

using namespace Rcpp;

#include <lpaggreg/oqualities.h>
#include <lpaggreg/opartitioner.h>
#include <lpaggreg/ovaluesn.h>

// [[Rcpp::export]]
double meanC(NumericVector x) {
  int n = x.size();
  double total = 0;

  for(int i = 0; i < n; ++i) {
    total += x[i];
  }
  return total / n;
}');

meanC(c(1,2,3));
