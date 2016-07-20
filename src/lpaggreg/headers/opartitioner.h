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
        OPartitioner(shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > > > qualities);
        void computeBestPartitions(float threshold, float min=0.0, float max=1.0);
        shared_ptr<OPartition <lp_quality_type> > computeBestPartition(float parameter);
        void addBestQualities(float threshold, shared_ptr<OPartition <lp_quality_type> > bestPartitionMin, shared_ptr<OPartition <lp_quality_type> > bestPartitionMax);
    private:
        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > > > qualities;
        map<float, shared_ptr<OPartition <lp_quality_type> > > partitions;
    };

}

#endif // OPARTITIONER_H
