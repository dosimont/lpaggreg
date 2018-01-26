#ifndef DAGGREGATION_H
#define DAGGREGATION_H

#include <memory>
#include "dvaluesn.h"
#include "dpartition.h"

using namespace std;

namespace lpaggreg{

    class DAggregate
    {
    public:
        DAggregate(DPart part);
        DPart getPart() const;
    protected:
        DPart part;
        virtual void compute()=0;
    };

    class DAggregation
    {
    public:
        DAggregation(shared_ptr<DPartition> dpartition);
    private:
        shared_ptr<DPartition> dpartition;
    };
}

#endif // DAGGREGATION_H
