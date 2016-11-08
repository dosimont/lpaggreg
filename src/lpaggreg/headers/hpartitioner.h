#ifndef HPARTITIONER_H
#define HPARTITIONER_H

#include <vector>
#include <memory>
#include <map>
#include <list>
#include <tuple>
#include "hqualities.h"
#include "partitioner.h"
#include "hpartition.h"
#include "quality.h"
#include "tradeoff.h"

using namespace std;

namespace lpaggreg{

    class HPartitioner: public Partitioner
    {
    public:
        HPartitioner(hqualities qualities, HValuesMetaData metaData);
        HPartitioner(HQualities qualities);
        void computeBestPartitions(float threshold, float min=0.0, float max=1.0);
        shared_ptr<HPartition> computeBestPartition(float parameter);

        map<float, shared_ptr<HPartition> > getPartitions() const;

        list<tuple<float, int, int, lp_quality_type, lp_quality_type> > getPartitionsTuples() const;

    private:
        void addBestQualities(float threshold, shared_ptr<HPartition> bestPartitionMin, shared_ptr<HPartition> bestPartitionMax);
        hqualities qualities;
        map<float, shared_ptr<HPartition> > partitions;
        list< tuple<float, int, int, lp_quality_type, lp_quality_type> > partitionsTuples;
        HValuesMetaData metaData;
    };
}

#endif // HPARTITIONER_H
