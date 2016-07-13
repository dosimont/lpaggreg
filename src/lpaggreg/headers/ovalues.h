#ifndef OVALUES_H
#define OVALUES_H

#include <vector>

namespace lpaggreg{

    class OValues
    {
    protected:
        unsigned int osize;
        unsigned int vsize;
    public:
        OValues();
        virtual double & operator[] (int index) const=0;
        virtual double operator[] (int index)=0;
        unsigned int vsize(){return vsize();}
        unsigned int osize(){return osize();}
    };

    class OValuesN1: public OValues
    {
    private:
        vector<double> values;
    public:
        OValues1(unsigned int osize):osize(osize), vsize(1){values=vector<double>(osize, 0);}
        double & operator[] (unsigned int index) const {return values;}
        double operator[] (unsigned int index) {return values;}
        vector<double> &operator()(unsigned int o, unsigned int v) const{return values[v][o];}
        vector<double> operator()(unsigned int o, unsigned int v) {return values[v][o];}
    };

    class OValuesN2: public OValues
    {
    private:
        vector< vector<double> > values;
    public:
        OValues2(unsigned int vsize, unsigned int osize):osize(osize), vsize(vsize){values=vector< vector <double > >(vsize, vector<double>(osize, 0));}
        double & operator[] (unsigned int index) const {return values[index];}
        double operator[] (unsigned int index) {return values[index];}
        vector< vector<double> > &operator()(unsigned int o, unsigned int a, unsigned int b) const{return values[a][b][o];}
        vector< vector<double> > operator()(unsigned int o, unsigned int a, unsigned int b) {return values[a][b][o];}
    };

    class OValuesN3: public OValues
    {
    private:
        vector< vector< vector<double> > > values;
        unsigned int i;
        unsigned int j;
        unsigned int toI(unsigned int index){return index/j;}
        unsigned int toJ(unsigned int index){return index%j;}
    public:
        OValues3(unsigned int i, unsigned int j, unsigned int osize):osize(osize), vsize(i*j), i(i),j(j){values=vector< vector < vector<double > > >(i, vector< vector<double> >(j, vector<double>(osize, 0)));}
        double & operator[] (unsigned int index) const {return values[toI(index)][toJ(index)];}
        double operator[] (unsigned int index) {return values[toI(index)][toJ(index)];}
        vector< vector< vector<double> > > &operator()(unsigned int o, unsigned int a, unsigned int b, unsigned int c) const{return values[a][b][c][o];}
        vector< vector< vector<double> > > operator()(unsigned int o, unsigned int a, unsigned int b, unsigned int c) {return values[a][b][c][o];}
    };

    class OValuesN4: public OValues
    {
    private:
        vector< vector< vector<double> > > values;
        unsigned int i;
        unsigned int j;
        unsigned int k;
        unsigned int toI(unsigned int index){return index/(k*j);}
        unsigned int toJ(unsigned int index){return ((index/k)%j;}
        unsigned int toK(unsigned int index){return index%k;}
    public:
        OValues4(unsigned int i, unsigned int j, unsigned int k, unsigned int osize):osize(osize), vsize(i*j*k), i(i),j(j),k(k){values=vector< vector < vector <vector<double > > > >(i, vector < vector< vector<double> > >(j, vector< vector<double> >(k, vector<double>(osize, 0))));}
        double & operator[] (unsigned int index) const {return values[toI(index)][toJ(index)][toK(index)];}
        double operator[] (unsigned int index) {return values[toI(index)][toJ(index)][toK(index)];}
        vector< vector< vector<double> > > &operator()(unsigned int o, unsigned int a, unsigned int b, unsigned int c, unsigned int d) const{return values[a][b][c][d][o];}
        vector< vector< vector<double> > > operator()(unsigned int o, unsigned int a, unsigned int b, unsigned int c, unsigned int d) {return values[a][b][c][d][o];}
    };

}



#endif // OVALUES_H
