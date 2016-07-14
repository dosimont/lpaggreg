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
        OValues(unsigned int osize, unsigned int vsize);
        //virtual vector<double> & operator[] (int index) const=0;
        virtual vector<double> operator[] (int index)=0;
        unsigned int getVsize();
        unsigned int getOsize();
    };


}

#endif // OVALUES_H
