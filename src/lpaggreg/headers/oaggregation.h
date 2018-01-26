#ifndef OAGGREGATION_H
#define OAGGREGATION_H

#include <memory>
#include "ovaluesn.h"
#include "opartition.h"

using namespace std;

namespace lpaggreg{

    class OAggregate
    {
    public:
        OAggregate(OPart part);
        OPart getPart() const;
    protected:
        OPart part;
        virtual void compute()=0;
    };

    class OAggregation
    {
    public:
        OAggregation(shared_ptr<OPartition> opartition);
    private:
        shared_ptr<OPartition> opartition;
    };

}

#endif // OAGGREGATION_H
