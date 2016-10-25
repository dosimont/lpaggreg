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

  #include <RcppArmadillo.h>
  // [[Rcpp::depends(RcppArmadillo)]]

  #include <lpaggreg/oqualities.h>
  #include <lpaggreg/opartitioner.h>
  #include <lpaggreg/ovaluesn.h>  

  using namespace Rcpp;
  using namespace arma;
 
  // [[Rcpp::export]]
  arma::cube readCube(NumericVector myArray) {


  NumericVector vecArray(myArray);
  IntegerVector arrayDims = vecArray.attr("dim");

  
  arma::cube cubeArray(vecArray.begin(), arrayDims[0], arrayDims[1], arrayDims[2], false);
 
  //change one element in the array/cube
  cubeArray(0,0,0) = 518;  
 
  return cubeArray;
  }
'

sourceCpp(code=src, verbose=TRUE, rebuild=TRUE)

set.seed(345)
testArray = array(rnorm(18), dim=c(3,3,2))
#print(testArray)
readCube(testArray)