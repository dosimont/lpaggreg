#ifndef DVALUESN_H
#define DVALUESN_H

#include "dvalues.h"
#include "lpglobal.h"

namespace lpaggreg{

    class DValuesN2: public DValues
    {
    private:
        vector< vector<double> > values;
    public:
        DValuesN2(vector< vector<double> > values, vector<int>parents);
        DValuesN2(unsigned int leaves, unsigned int osize, vector<int>parents);
        double operator()(unsigned int h, unsigned int o);
        void operator()(unsigned int h, unsigned int o, double val);
        vector<double> getValue(int h, int index);
    };

    class DValuesN3: public DValues
    {
    private:
        vector< vector< vector<double> > > values;
    public:
        DValuesN3(vector< vector< vector<double> > > values, vector<int>parents);
        DValuesN3(unsigned int leaves, unsigned int vsize, unsigned int osize, vector<int>parents);
        double operator()(unsigned int h, unsigned int a, unsigned int o);
        void operator()(unsigned int h, unsigned int a, unsigned int o, double val);
        vector<double> getValue(int h, int index);
    };

    class DValuesN4: public DValues
    {
    private:
        vector< vector< vector < vector< double> > > > values;
        unsigned int i;
        unsigned int j;
        unsigned int toI(unsigned int index);
        unsigned int toJ(unsigned int index);
    public:
        DValuesN4(vector< vector< vector < vector< double> > > > values, vector<int>parents);
        DValuesN4(unsigned int leaves, unsigned int i, unsigned int j, unsigned int osize, vector<int>parents);
        double operator()(unsigned int h, unsigned int a, unsigned int b,  unsigned int o);
        void operator()(unsigned int h, unsigned int a, unsigned int b,  unsigned int o, double val);
        unsigned int getI() const;
        unsigned int getJ() const;
        vector<double> getValue(int h, int index);
    };

}

#endif // DVALUESN_H
