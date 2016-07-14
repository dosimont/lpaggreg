#ifndef OVALUESN_H
#define OVALUESN_H

#include "ovalues.h"

namespace lpaggreg{

    class OValuesN1: public OValues
    {
    private:
        vector<double> values;
    public:
        OValuesN1(unsigned int osize);
        //vector<double> & operator[] (unsigned int index) const;
        vector<double> operator[] (unsigned int index);
        //double &operator()(unsigned int o) const;
        double operator()(unsigned int o);
    };

    class OValuesN2: public OValues
    {
    private:
        vector< vector<double> > values;
    public:
        OValuesN2(unsigned int vsize, unsigned int osize);
        //vector<double> & operator[] (unsigned int index) const;
        vector<double> operator[] (unsigned int index);
        //double &operator()(unsigned int o, unsigned int a) const;
        double operator()(unsigned int o, unsigned int a);
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
        OValuesN3(unsigned int i, unsigned int j, unsigned int osize);
        //vector<double> & operator[] (unsigned int index) const;
        vector<double> operator[] (unsigned int index);
        //double &operator()(unsigned int o, unsigned int a, unsigned int b) const;
        double operator()(unsigned int o, unsigned int a, unsigned int b);
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
        OValuesN4(unsigned int i, unsigned int j, unsigned int k, unsigned int osize);
        //vector<double> & operator[] (unsigned int index) const;
        vector<double> operator[] (unsigned int index);
        //double &operator()(unsigned int o, unsigned int a, unsigned int b, unsigned int c) const;
        double operator()(unsigned int o, unsigned int a, unsigned int b, unsigned int c);
    };

}

#endif // OVALUESN_H
