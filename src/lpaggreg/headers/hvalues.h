#ifndef HVALUES_H
#define HVALUES_H

#include <vector>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

namespace lpaggreg{

    class HValuesProxy;

    class HValues
    {
    protected:
        unsigned int hsize;
        unsigned int vsize;
        vector<int>parents;
        map<int, int>size;
        vector<int> path;
        void setPath();
        int index;
    public:
        HValues(unsigned int hsize, unsigned int vsize, vector<int>parents);
        virtual HValuesProxy operator[] (unsigned int index)=0;
        unsigned int getVsize();
        unsigned int getHsize();
        virtual double getValue(int h, int index)=0;
    };

    class HValuesProxy
    {
    private:
        HValues* hvalues;
        int index;
    public:
        HValuesProxy(int index, HValues *hvalues);
        double operator[](unsigned int h);
    };
}


#endif // HVALUES_H
