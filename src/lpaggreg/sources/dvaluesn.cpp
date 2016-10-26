#include "dvaluesn.h"

lpaggreg::DValuesN2::DValuesN2(vector<vector<double> > values, vector<int> parents):DValues(SIZE1, 1, SIZE2, parents), values(values)
{

}

lpaggreg::DValuesN2::DValuesN2(unsigned int leaves, unsigned int osize, vector<int> parents):DValues(leaves, 1, osize, parents)
{
    values=vector< vector <double > >(leaves, vector<double>(osize, 0));
}

double lpaggreg::DValuesN2::operator()(unsigned int h, unsigned int o)
{
    return values[h][o];
}

void lpaggreg::DValuesN2::operator()(unsigned int h, unsigned int o, double val)
{
    values[h][o]=val;
}

vector<double> lpaggreg::DValuesN2::getValue(int h, int index)
{
    return values[h];
}

lpaggreg::DValuesN3::DValuesN3(vector<vector<vector<double> > > values, vector<int> parents):DValues(SIZE1, SIZE2, SIZE3, parents), values(values)
{

}

lpaggreg::DValuesN3::DValuesN3(unsigned int leaves, unsigned int vsize, unsigned int osize, vector<int> parents):DValues(leaves, vsize, osize, parents)
{
    values=vector< vector < vector<double > > >(leaves, vector< vector<double> >(vsize, vector<double>(osize, 0)));
}

double lpaggreg::DValuesN3::operator()(unsigned int h, unsigned int a, unsigned int o)
{
    return values[h][a][o];
}

void lpaggreg::DValuesN3::operator()(unsigned int h, unsigned int a, unsigned int o, double val)
{
    values[h][a][o]=val;
}

vector<double> lpaggreg::DValuesN3::getValue(int h, int index)
{
    return values[h][index];
}

unsigned int lpaggreg::DValuesN4::toI(unsigned int index)
{
    return index/j;
}

unsigned int lpaggreg::DValuesN4::toJ(unsigned int index)
{
    return index%j;
}

lpaggreg::DValuesN4::DValuesN4(vector<vector<vector<vector<double> > > > values, vector<int> parents):DValues(SIZE1, SIZE2*SIZE3, SIZE4, parents), values(values), i(SIZE2), j(SIZE3)
{

}

lpaggreg::DValuesN4::DValuesN4(unsigned int leaves, unsigned int i, unsigned int j, unsigned int osize, vector<int> parents):DValues(leaves, i*j, osize, parents), i(i), j(j)
{
    values=vector< vector < vector <vector<double > > > >(leaves, vector < vector< vector<double> > >(i, vector< vector<double> >(j, vector<double>(osize, 0))));
}

double lpaggreg::DValuesN4::operator()(unsigned int h, unsigned int a, unsigned int b, unsigned int o)
{
    return values[h][a][b][o];
}

void lpaggreg::DValuesN4::operator()(unsigned int h, unsigned int a, unsigned int b, unsigned int o, double val)
{
    values[h][a][b][o]=val;
}

unsigned int lpaggreg::DValuesN4::getI() const
{
    return i;
}

unsigned int lpaggreg::DValuesN4::getJ() const
{
    return j;
}

vector<double> lpaggreg::DValuesN4::getValue(int h, int index)
{
    return values[h][toI(index)][toJ(index)];
}
