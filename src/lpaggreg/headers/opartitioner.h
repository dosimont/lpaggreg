#ifndef OPARTITIONER_H
#define OPARTITIONER_H

#include <vector>
#include <memory>
#include <map>
#include <list>
#include <tuple>
#include "oqualities.h"
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
        OPartitioner(oqualities qualities);
        OPartitioner(OQualities qualities);
        void computeBestPartitions(float threshold, float min=0.0, float max=1.0);
        shared_ptr<OPartition> computeBestPartition(float parameter);    
        map<float, shared_ptr<OPartition> > getPartitions() const;
        list<tuple<float, int, int, lp_quality_type, lp_quality_type> > getPartitionsTuples() const;
    private:
        void addBestQualities(float threshold, shared_ptr<OPartition> bestPartitionMin, shared_ptr<OPartition> bestPartitionMax);
        oqualities qualities;
        map<float, shared_ptr<OPartition> > partitions;
        list< tuple<float, int, int, lp_quality_type, lp_quality_type> > partitionsTuples;
    };

}

#endif // OPARTITIONER_H
