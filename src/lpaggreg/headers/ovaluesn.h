#ifndef OVALUESN_H
#define OVALUESN_H

#include "ovalues.h"
#include "lpglobal.h"

namespace lpaggreg{

    class OValuesN1: public OValues
    {
    private:
        vector<double> values;
    public:
        OValuesN1(vector<double> values);
        OValuesN1(unsigned int osize);
        vector<double> operator[] (unsigned int index);
        double operator()(unsigned int o);
        void operator()(unsigned int o, double val);
    };

    class OValuesN2: public OValues
    {
    private:
        vector< vector<double> > values;
    public:
        OValuesN2(vector< vector<double> > values);
        OValuesN2(unsigned int vsize, unsigned int osize);
        vector<double> operator[] (unsigned int index);
        double operator()(unsigned int a, unsigned int o);
        void operator()(unsigned int a, unsigned int o, double val);
    };

    class OValuesN3: public OValues
    {
    private:
        vector< vector< vector<double> > > values;
        unsigned int i;
        unsigned int j;
        unsigned int toI(unsigned int index);
        unsigned int toJ(unsigned int index);
    public:
        OValuesN3(vector< vector< vector<double> > > values);
        OValuesN3(unsigned int i, unsigned int j, unsigned int osize);
        vector<double> operator[] (unsigned int index);
        double operator()(unsigned int a, unsigned int b, unsigned int o);
        void operator()(unsigned int a, unsigned int b, unsigned int o, double val);
        unsigned int getI() const;
        unsigned int getJ() const;
    };

    class OValuesN4: public OValues
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
        OValuesN4(vector< vector< vector < vector< double> > > > values);
        OValuesN4(unsigned int i, unsigned int j, unsigned int k, unsigned int osize);
        vector<double> operator[] (unsigned int index);
        double operator()(unsigned int a, unsigned int b, unsigned int c, unsigned int o);
        void operator()(unsigned int a, unsigned int b, unsigned int c, unsigned int o, double val);
        unsigned int getI() const;
        unsigned int getJ() const;
        unsigned int getK() const;
    };

}

#endif // OVALUESN_H
