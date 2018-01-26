#ifndef HAGGREGATION_H
#define HAGGREGATION_H

#include <memory>
#include "hvaluesn.h"
#include "hpartition.h"

using namespace std;

namespace lpaggreg
{
    class HAggregate
    {
    public:
        HAggregate(HPart part);
        HPart getPart() const;
    protected:
        HPart part;
        virtual void compute()=0;
    };

    class HAggregation
    {
    public:
        HAggregation(shared_ptr<HPartition> hpartition);
    private:
        shared_ptr<HPartition> hpartition;
    };
}

#endif // HAGGREGATION_H
