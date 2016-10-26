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

  using namespace Rcpp;
  using namespace arma;
  using namespace std;
  using namespace lpaggreg;
 
  // [[Rcpp::export]]
  NumericMatrix oaggregate(NumericVector myArray) {

  NumericVector vecArray(myArray);
  
  IntegerVector arrayDims = vecArray.attr("dim");

  cout<<"Dimension 1:"<<arrayDims[0]<<endl;
  cout<<"Dimension 2:"<<arrayDims[1]<<endl;
  cout<<"Dimension 3:"<<arrayDims[2]<<endl;
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
  shared_ptr<OValuesN3> values = shared_ptr<OValuesN3>(new OValuesN3(micromodel));
  OQualities oqualities = OQualities(values);
  oqualities.computeQualities();
  oqualities.normalize();
  OPartitioner opartitioner = OPartitioner(oqualities);
  opartitioner.computeBestPartitions(0.001);
  list< tuple<float, int, int> > partitionsTuples=opartitioner.getPartitionsTuples();
  NumericMatrix matrixResults(partitionsTuples.size(),3);
  int i=0;
  for (tuple<float, int, int> line: partitionsTuples){
    matrixResults(i, 0)=get<0>(line);
    matrixResults(i, 1)=get<1>(line);
    matrixResults(i, 2)=get<2>(line);
    i++;
  }
  return matrixResults;
}
'

sourceCpp(code=src, verbose=TRUE, rebuild=TRUE)

set.seed(345)
testArray = array(dim=c(2,2,5))
testArray[1,1,] = c(50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0)
testArray[1,2,] = c(50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0)
testArray[2,1,] = c(50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0)
testArray[2,2,] = c(50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0)
print(testArray)
oaggregate(testArray)