#ifndef PARTITIONER_H
#define PARTITIONER_H

#include <vector>
#include "lpglobal.h"
#include "quality.h"

using namespace std;

namespace lpaggreg{

    class Partitioner
    {
    public:
        Partitioner();
        vector<float> *getPList() const;
        virtual void computeBestPartitions(float threshold)=0;

    private:
        vector<float>* pList;
    };

}

#endif // PARTITIONER_H
