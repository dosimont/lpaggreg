#ifndef DPARTITIONER_H
#define DPARTITIONER_H

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <list>
#include <tuple>
#include "dqualities.h"
#include "partitioner.h"
#include "dpartition.h"
#include "quality.h"
#include "tradeoff.h"

using namespace std;

namespace lpaggreg{

    class DPartitioner: public Partitioner
    {
    public:
        DPartitioner(dqualities qualities, HValuesMetaData metaData);
        DPartitioner(DQualities qualities);
        void computeBestPartitions(float threshold, float min=0.0, float max=1.0);
        shared_ptr<DPartition> computeBestPartition(float parameter);

        map<float, shared_ptr<DPartition> > getPartitions() const;

        list<tuple<float, int, int, int, int, lp_quality_type, lp_quality_type> > getPartitionsTuples() const;

    private:
        void addBestQualities(float threshold, shared_ptr<DPartition> bestPartitionMin, shared_ptr<DPartition> bestPartitionMax);
        dqualities qualities;
        map<float, shared_ptr<DPartition> > partitions;
        list< tuple<float, int, int, int, int, lp_quality_type, lp_quality_type> > partitionsTuples;
        HValuesMetaData metaData;
    };
}

#endif // DPARTITIONER_H
