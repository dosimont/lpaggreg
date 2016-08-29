#ifndef HVALUESN_H
#define HVALUESN_H

#include "hvalues.h"

namespace lpaggreg{

    class HValuesN1: public HValues
    {
    private:
        vector<double> values;
    public:
        HValuesN1(vector<double> values);
        HValuesN1(unsigned int hsize);
        vector<double> operator[] (unsigned int index);
        double operator()(unsigned int h);
        void operator()(unsigned int h, double val);
    };

    class HValuesN2: public HValues
    {
    friend class HValuesN2Proxy;
    private:
        vector< vector<double> > values;
    public:
        HValuesN2(vector< vector<double> > values);
        HValuesN2(unsigned int vsize, unsigned int osize);
        HValuesN2Proxy operator[] (unsigned int index);
        double operator()(unsigned int h, unsigned int a);
        void operator()(unsigned int h, unsigned int a, double val);
    };

    class HValuesN2Proxy
    {
    private:
        int index;
        HValuesN2 hvalues;
    public:
        HValuesN2Proxy(int index, HValuesN2 hvalues);
        double operator[](unsigned int h);
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
        HValuesN3(vector< vector< vector<double> > > values);
        HValuesN3(unsigned int i, unsigned int j, unsigned int osize);
        vector<double> operator[] (unsigned int index);
        double operator()(unsigned int h, unsigned int a, unsigned int b);
        void operator()(unsigned int h, unsigned int a, unsigned int b, double val);
        unsigned int getI() const;
        unsigned int getJ() const;
    };

    class HValuesN3Proxy
    {
    private:
        int index;
        HValuesN3 hvalues;
    public:
        HValuesN3Proxy(int index, HValuesN3 hvalues);
        double operator[](unsigned int h);
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
        HValuesN4(vector< vector< vector < vector< double> > > > values);
        HValuesN4(unsigned int i, unsigned int j, unsigned int k, unsigned int osize);
        vector<double> operator[] (unsigned int index);
        double operator()(unsigned int h, unsigned int a, unsigned int b, unsigned int c);
        void operator()(unsigned int h, unsigned int a, unsigned int b, unsigned int c, double val);
        unsigned int getI() const;
        unsigned int getJ() const;
        unsigned int getK() const;
    };

}

#endif // HVALUESN_H
