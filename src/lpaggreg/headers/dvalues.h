#ifndef DVALUES_H
#define DVALUES_H

#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include "hvalues.h"

using namespace std;

namespace lpaggreg{

    class DValuesProxy;

    class DValues
    {
    protected:
        unsigned int vsize;
        unsigned int osize;
        HValuesMetaData metaData;
    public:
        DValues(unsigned int leaves, unsigned int vsize, unsigned osize, vector<int>parents);
        DValuesProxy operator[] (unsigned int h);
        unsigned int getOsize() const;
        unsigned int getVsize() const;
        virtual vector<double> getValue(int h, int index)=0;

        HValuesMetaData getMetaData() const;
    };

    class DValuesProxy
    {
    private:
        DValues* dvalues;
        int h;
    public:
        DValuesProxy(int h, DValues *dvalues);
        vector<double> operator[](unsigned int index);
    };
}

#endif // DVALUES_H
