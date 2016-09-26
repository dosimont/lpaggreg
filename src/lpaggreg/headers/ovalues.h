#ifndef OVALUES_H
#define OVALUES_H

#include <vector>

using namespace std;

namespace lpaggreg{

    class OValues
    {
    protected:
        unsigned int osize;
        unsigned int vsize;
    public:
        OValues(unsigned int vsize, unsigned int osize);
        virtual vector<double> operator[] (unsigned int index)=0;
        unsigned int getVsize();
        unsigned int getOsize();
    };
}

#endif // OVALUES_H
