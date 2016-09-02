#include "partition.h"


float lpaggreg::Partition::getParameter() const
{
    return parameter;
}

shared_ptr<lpaggreg::Quality> lpaggreg::Partition::getQuality() const
{
    return quality;
}

lpaggreg::Partition::Partition(float parameter):parameter(parameter)
{

}
