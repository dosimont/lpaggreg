#include "oaggregation.h"


lpaggreg::OAggregate::OAggregate(lpaggreg::OPart part): part(part)
{

}

lpaggreg::OPart lpaggreg::OAggregate::getPart() const
{
    return part;
}

lpaggreg::OAggregation::OAggregation(shared_ptr<lpaggreg::OPartition> opartition):opartition(opartition)
{

}
