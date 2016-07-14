#ifndef OPARTITIONER_H
#define OPARTITIONER_H

#include <vector>
#include <memory>
#include "partitioner.h"
#include "quality.h"
#include "tradeoff.h"
#include "uppertriangularmatrix.h"

using namespace std;

namespace lpaggreg{

    class OPartitioner : public Partitioner
    {
    public:
        OPartitioner(shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > > > qualities);
        void computeBestPartitions(float threshold);
        vector<int> computeBestCuts(float parameter);
    private:
        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > > > qualities;
    };

}

#endif // OPARTITIONER_H
