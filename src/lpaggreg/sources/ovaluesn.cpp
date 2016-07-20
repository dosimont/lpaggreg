#include "ovaluesn.h"

lpaggreg::OValuesN1::OValuesN1(unsigned int osize):OValues(osize, 1){values=vector<double>(osize, 0);}

vector<double> lpaggreg::OValuesN1::operator[](unsigned int index) {return values;}

double lpaggreg::OValuesN1::operator()(unsigned int o) {return values[o];}

lpaggreg::OValuesN2::OValuesN2(unsigned int vsize, unsigned int osize):OValues(osize, vsize){values=vector< vector <double > >(vsize, vector<double>(osize, 0));}

vector<double> lpaggreg::OValuesN2::operator[](unsigned int index) {return values[index];}

double lpaggreg::OValuesN2::operator()(unsigned int o, unsigned int a) {return values[a][o];}

unsigned int lpaggreg::OValuesN3::toI(unsigned int index){return index/j;}

unsigned int lpaggreg::OValuesN3::toJ(unsigned int index){return index%j;}

lpaggreg::OValuesN3::OValuesN3(unsigned int i, unsigned int j, unsigned int osize):OValues(osize, i*j), i(i),j(j){values=vector< vector < vector<double > > >(i, vector< vector<double> >(j, vector<double>(osize, 0)));}

vector<double> lpaggreg::OValuesN3::operator[](unsigned int index) {return values[toI(index)][toJ(index)];}

double lpaggreg::OValuesN3::operator()(unsigned int o, unsigned int a, unsigned int b) {return values[a][b][o];}

unsigned int lpaggreg::OValuesN4::toI(unsigned int index){return index/(k*j);}

unsigned int lpaggreg::OValuesN4::toJ(unsigned int index){return (index/k)%j;}

unsigned int lpaggreg::OValuesN4::toK(unsigned int index){return index%k;}

lpaggreg::OValuesN4::OValuesN4(unsigned int i, unsigned int j, unsigned int k, unsigned int osize):OValues(osize, i*j*k), i(i),j(j),k(k){values=vector< vector < vector <vector<double > > > >(i, vector < vector< vector<double> > >(j, vector< vector<double> >(k, vector<double>(osize, 0))));}

vector<double> lpaggreg::OValuesN4::operator[](unsigned int index) {return values[toI(index)][toJ(index)][toK(index)];}

double lpaggreg::OValuesN4::operator()(unsigned int o, unsigned int a, unsigned int b, unsigned int c) {return values[a][b][c][o];}

