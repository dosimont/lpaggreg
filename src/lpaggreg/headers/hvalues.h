#ifndef HVALUES_H
#define HVALUES_H

#include <vector>
#include <list>

using namespace std;

namespace lpaggreg{

    class HValues
    {
    protected:
        unsigned int hsize;
        unsigned int vsize;
    public:
        HValues(unsigned int hsize, unsigned int vsize, vector<list<int> >tree);
        virtual vector<double> operator[] (unsigned int index)=0;
        unsigned int getVsize();
        unsigned int getHsize();
        vector<list<int> >tree;
    };
}


#endif // HVALUES_H
