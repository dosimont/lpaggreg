#include "daggregation.h"

lpaggreg::DAggregate::DAggregate(lpaggreg::DPart part): part(part)
{

}

lpaggreg::DPart lpaggreg::DAggregate::getPart() const
{
    return part;
}

lpaggreg::DAggregation::DAggregation(shared_ptr<lpaggreg::DPartition> dpartition):dpartition(dpartition)
{

}
