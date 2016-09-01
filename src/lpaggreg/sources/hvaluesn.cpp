#include "hvaluesn.h"


double lpaggreg::HValuesN1::getValue(int h, int index)
{
    return values[h];
}

double lpaggreg::HValuesN2::getValue(int h, int index)
{
    return values[h][index];
}

double lpaggreg::HValuesN3::getValue(int h, int index)
{
    return values[h][toI(index)][toJ(index)];
}

double lpaggreg::HValuesN4::getValue(int h, int index)
{
    return values[h][toI(index)][toJ(index)][toK(index)];
}

lpaggreg::HValuesN1::HValuesN1(vector<double> values, vector<int>parents):HValues(SIZE1, 1, parents), values(values)
{

}

lpaggreg::HValuesN1::HValuesN1(unsigned int leaves, vector<int>parents):HValues(leaves, 1, parents){
    values=vector<double>(leaves, 0);
}

double lpaggreg::HValuesN1::operator()(unsigned int h) {
    return values[h];
}

void lpaggreg::HValuesN1::operator()(unsigned int h, double val) {
    values[h]=val;
}

lpaggreg::HValuesN2::HValuesN2(vector<vector<double> > values, vector<int>parents):HValues(SIZE1, SIZE2, parents), values(values)
{

}

lpaggreg::HValuesN2::HValuesN2(unsigned int leaves, unsigned int vsize, vector<int>parents):HValues(leaves, vsize, parents){
    values=vector< vector <double > >(leaves, vector<double>(vsize, 0));
}

double lpaggreg::HValuesN2::operator()(unsigned int h, unsigned int a) {
    return values[h][a];
}

void lpaggreg::HValuesN2::operator()(unsigned int h, unsigned int a, double val) {
    values[h][a]=val;
}

unsigned int lpaggreg::HValuesN3::getI() const
{
    return i;
}

unsigned int lpaggreg::HValuesN3::getJ() const
{
    return j;
}

unsigned int lpaggreg::HValuesN3::toI(unsigned int index){
    return index/j;
}

unsigned int lpaggreg::HValuesN3::toJ(unsigned int index){
    return index%j;
}

lpaggreg::HValuesN3::HValuesN3(vector<vector<vector<double> > > values, vector<int> parents):
    HValues(SIZE1, SIZE2*SIZE3, parents), i(SIZE2), j(SIZE3), values(values)
{

}

lpaggreg::HValuesN3::HValuesN3(unsigned int leaves, unsigned int i, unsigned int j, vector<int>parents):HValues(leaves, i*j, parents), i(i),j(j){
    values=vector< vector < vector<double > > >(leaves, vector< vector<double> >(i, vector<double>(j, 0)));
}

double lpaggreg::HValuesN3::operator()(unsigned int h, unsigned int a, unsigned int b) {
    return values[h][a][b];
}

void lpaggreg::HValuesN3::operator()(unsigned int h, unsigned int a, unsigned int b, double val) {
    values[h][a][b]=val;
}

unsigned int lpaggreg::HValuesN4::getI() const
{
    return i;
}

unsigned int lpaggreg::HValuesN4::getJ() const
{
    return j;
}

unsigned int lpaggreg::HValuesN4::getK() const
{
    return k;
}

unsigned int lpaggreg::HValuesN4::toI(unsigned int index){
    return index/(k*j);
}

unsigned int lpaggreg::HValuesN4::toJ(unsigned int index){
    return (index/k)%j;
}

unsigned int lpaggreg::HValuesN4::toK(unsigned int index){
    return index%k;
}

lpaggreg::HValuesN4::HValuesN4(vector<vector<vector<vector<double> > > > values, vector<int> parents):
    HValues(SIZE1, SIZE2*SIZE3*SIZE4, parents), i(SIZE2), j(SIZE3), k(SIZE4), values(values)
{

}

lpaggreg::HValuesN4::HValuesN4(unsigned int leaves, unsigned int i, unsigned int j, unsigned int k, vector<int> parents):HValues(leaves, i*j*k, parents), i(i),j(j),k(k){
    values=vector< vector < vector <vector<double > > > >(leaves, vector < vector< vector<double> > >(i, vector< vector<double> >(j, vector<double>(k, 0))));
}

double lpaggreg::HValuesN4::operator()(unsigned int h, unsigned int a, unsigned int b, unsigned int c) {
    return values[h][a][b][c];
}

void lpaggreg::HValuesN4::operator()(unsigned int h, unsigned int a, unsigned int b, unsigned int c, double val) {
    values[h][a][b][c]=val;
}


