#ifndef OPARTITIONER_H
#define OPARTITIONER_H

#include "partitioner.h"
#include "quality.h"
#include "tradeoff.h"

namespace lpaggreg{

    class OPartitioner : public Partitioner
    {
    public:
        OPartitioner();
        OPartitioner(vector<vector<Quality<lp_quality_type> > >* qualities);
        void computeBestPartitions(float threshold);
        void computeBestCuts(float parameter);
    private:
        vector<vector<Quality<lp_quality_type> > >* qualities;
    };

}

#endif // OPARTITIONER_H
