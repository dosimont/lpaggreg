#include "haggregation.h"


lpaggreg::HAggregate::HAggregate(lpaggreg::HPart part): part(part)
{

}

lpaggreg::HPart lpaggreg::HAggregate::getPart() const
{
    return part;
}

lpaggreg::HAggregation::HAggregation(shared_ptr<lpaggreg::HPartition> hpartition):hpartition(hpartition)
{

}
