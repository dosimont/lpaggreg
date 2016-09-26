#ifndef HVALUESN_H
#define HVALUESN_H

#include "hvalues.h"
#include "lpglobal.h"

namespace lpaggreg{

    class HValuesN1: public HValues
    {
    private:
        vector<double> values;
    public:
        HValuesN1(vector<double> values, vector<int>parents);
        HValuesN1(unsigned int leaves, vector<int>parents);
        double operator()(unsigned int h);
        void operator()(unsigned int h, double val);
        double getValue(int h, int index);
    };

    class HValuesN2: public HValues
    {
    private:
        vector< vector<double> > values;
    public:
        HValuesN2(vector< vector<double> > values, vector<int>parents);
        HValuesN2(unsigned int leaves, unsigned int vsize, vector<int>parents);
        double operator()(unsigned int h, unsigned int a);
        void operator()(unsigned int h, unsigned int a, double val);
        double getValue(int h, int index);
    };

    class HValuesN3: public HValues
    {
    private:
        vector< vector< vector<double> > > values;
        unsigned int i;
        unsigned int j;
        unsigned int toI(unsigned int index);
        unsigned int toJ(unsigned int index);
    public:
        HValuesN3(vector< vector< vector<double> > > values, vector<int>parents);
        HValuesN3(unsigned int leaves, unsigned int i, unsigned int j, vector<int>parents);
        double operator()(unsigned int h, unsigned int a, unsigned int b);
        void operator()(unsigned int h, unsigned int a, unsigned int b, double val);
        double getValue(int h, int index);
        unsigned int getI() const;
        unsigned int getJ() const;
    };

    class HValuesN4: public HValues
    {
    private:
        vector< vector< vector < vector< double> > > > values;
        unsigned int i;
        unsigned int j;
        unsigned int k;
        unsigned int toI(unsigned int index);
        unsigned int toJ(unsigned int index);
        unsigned int toK(unsigned int index);
    public:
        HValuesN4(vector< vector< vector < vector< double> > > > values, vector<int>parents);
        HValuesN4(unsigned int leaves, unsigned int i, unsigned int j, unsigned int k, vector<int>parents);
        double operator()(unsigned int h, unsigned int a, unsigned int b, unsigned int c);
        void operator()(unsigned int h, unsigned int a, unsigned int b, unsigned int c, double val);
        unsigned int getI() const;
        unsigned int getJ() const;
        unsigned int getK() const;
        double getValue(int h, int index);
    };

}

#endif // HVALUESN_H
