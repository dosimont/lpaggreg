#include "ovaluesn.h"

lpaggreg::OValuesN1::OValuesN1(vector<double> values):OValues(1, SIZE1), values(values)
{

}

lpaggreg::OValuesN1::OValuesN1(unsigned int osize):OValues(1, osize){
    values=vector<double>(osize, 0);
}

vector<double> lpaggreg::OValuesN1::operator[](unsigned int index) {
    return values;
}

double lpaggreg::OValuesN1::operator()(unsigned int o) {
    return values[o];
}

void lpaggreg::OValuesN1::operator()(unsigned int o, double val) {
    values[o]=val;
}

lpaggreg::OValuesN2::OValuesN2(vector<vector<double> > values):OValues(SIZE1, SIZE2), values(values)
{

}

lpaggreg::OValuesN2::OValuesN2(unsigned int vsize, unsigned int osize):OValues(vsize, osize){
    values=vector< vector <double > >(vsize, vector<double>(osize, 0));
}

vector<double> lpaggreg::OValuesN2::operator[](unsigned int index) {
    return values[index];
}

double lpaggreg::OValuesN2::operator()(unsigned int a, unsigned int o) {
    return values[a][o];
}

void lpaggreg::OValuesN2::operator()(unsigned int a, unsigned int o, double val) {
    values[a][o]=val;
}

unsigned int lpaggreg::OValuesN3::getI() const
{
    return i;
}

unsigned int lpaggreg::OValuesN3::getJ() const
{
    return j;
}

unsigned int lpaggreg::OValuesN3::toI(unsigned int index){
    return index/j;
}

unsigned int lpaggreg::OValuesN3::toJ(unsigned int index){
    return index%j;
}

lpaggreg::OValuesN3::OValuesN3(vector<vector<vector<double> > > values):
    OValues(SIZE1*SIZE2, SIZE3), i(SIZE1), j(SIZE2), values(values)
{

}

lpaggreg::OValuesN3::OValuesN3(unsigned int i, unsigned int j, unsigned int osize):OValues(i*j, osize), i(i),j(j){
    values=vector< vector < vector<double > > >(i, vector< vector<double> >(j, vector<double>(osize, 0)));
}

vector<double> lpaggreg::OValuesN3::operator[](unsigned int index) {
    return values[toI(index)][toJ(index)];
}

double lpaggreg::OValuesN3::operator()(unsigned int a, unsigned int b, unsigned int o) {
    return values[a][b][o];
}

void lpaggreg::OValuesN3::operator()(unsigned int a, unsigned int b, unsigned int o, double val) {
    values[a][b][o]=val;
}

unsigned int lpaggreg::OValuesN4::getI() const
{
    return i;
}

unsigned int lpaggreg::OValuesN4::getJ() const
{
    return j;
}

unsigned int lpaggreg::OValuesN4::getK() const
{
    return k;
}

unsigned int lpaggreg::OValuesN4::toI(unsigned int index){
    return index/(k*j);
}

unsigned int lpaggreg::OValuesN4::toJ(unsigned int index){
    return (index/k)%j;
}

unsigned int lpaggreg::OValuesN4::toK(unsigned int index){
    return index%k;
}

lpaggreg::OValuesN4::OValuesN4(vector<vector<vector<vector<double> > > > values):
    OValues(SIZE1*SIZE2*SIZE3, SIZE4), i(SIZE1), j(SIZE2), k(SIZE3), values(values)
{

}

lpaggreg::OValuesN4::OValuesN4(unsigned int i, unsigned int j, unsigned int k, unsigned int osize):OValues(i*j*k, osize), i(i),j(j),k(k){
    values=vector< vector < vector <vector<double > > > >(i, vector < vector< vector<double> > >(j, vector< vector<double> >(k, vector<double>(osize, 0))));
}

vector<double> lpaggreg::OValuesN4::operator[](unsigned int index) {
    return values[toI(index)][toJ(index)][toK(index)];
}

double lpaggreg::OValuesN4::operator()(unsigned int a, unsigned int b, unsigned int c, unsigned int o) {
    return values[a][b][c][o];
}

void lpaggreg::OValuesN4::operator()(unsigned int a, unsigned int b, unsigned int c, unsigned int o, double val) {
    values[a][b][c][o]=val;
}

