#ifndef OPARTITIONER_H
#define OPARTITIONER_H

#include "partitioner.h"
#include "quality.h"
#include "tradeoff.h"
#include "uppertriangularmatrix.h"

using namespace std;

namespace lpaggreg{

    class OPartitioner : public Partitioner
    {
    public:
        OPartitioner();
        OPartitioner(UpperTriangularMatrix<Quality<lp_quality_type> >* qualities);
        void computeBestPartitions(float threshold);
        vector<int> computeBestCuts(float parameter);
    private:
        UpperTriangularMatrix<Quality<lp_quality_type> >* qualities;
    };

}

#endif // OPARTITIONER_H
