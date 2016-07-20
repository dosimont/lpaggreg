#ifndef PARTITIONER_H
#define PARTITIONER_H

#include <vector>
#include <memory>
#include "lpglobal.h"
#include "quality.h"

using namespace std;

namespace lpaggreg{

    class Partitioner
    {
    public:
        Partitioner();
        virtual void computeBestPartitions(float threshold, float min=0.0, float max=1.0)=0;
        vector<float> getPList() const;

    protected:
        vector<float> pList;
    };

}

#endif // PARTITIONER_H
