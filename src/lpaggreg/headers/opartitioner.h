#ifndef OPARTITIONER_H
#define OPARTITIONER_H

#include "partitioner.h"
#include "quality.h"

namespace lpaggreg{

    class OPartitioner : public Partitioner
    {
    public:
        OPartitioner();
        OPartitioner(vector<vector<Quality> >* qualities);
        void computeBestPartitions(float threshold);
        void computeBestCuts(float parameter);
    private:
        vector<vector<Quality> >* qualities;
    };

}

#endif // OPARTITIONER_H
