#ifndef OPARTITIONER_H
#define OPARTITIONER_H

#include <vector>
#include <memory>
#include <map>
#include "partitioner.h"
#include "opartition.h"
#include "quality.h"
#include "tradeoff.h"
#include "uppertriangularmatrix.h"

using namespace std;

namespace lpaggreg{

    class OPartitioner : public Partitioner
    {
    public:
        OPartitioner(shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > qualities);
        void computeBestPartitions(float threshold, float min=0.0, float max=1.0);
        shared_ptr<OPartition> computeBestPartition(float parameter);
        void addBestQualities(float threshold, shared_ptr<OPartition> bestPartitionMin, shared_ptr<OPartition> bestPartitionMax);
    private:
        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > qualities;
        map<float, shared_ptr<OPartition> > partitions;
    };

}

#endif // OPARTITIONER_H
