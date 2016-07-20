#include "opartition.h"


int lpaggreg::OPart::getStart() const
{
    return start;
}

void lpaggreg::OPart::setStart(int value)
{
    start = value;
}

int lpaggreg::OPart::getEnd() const
{
    return end;
}

void lpaggreg::OPart::setEnd(int value)
{
    end = value;
}

template<typename T>
vector<int> lpaggreg::OPartition<T>::getCuts() const
{
    return cuts;
}

template<typename T>
void lpaggreg::OPartition<T>::setCuts(const vector<int> &value)
{
    cuts = value;
}

template<typename T>
vector<lpaggreg::OPart> lpaggreg::OPartition<T>::getParts() const
{
    return parts;
}

template<typename T>
shared_ptr<lpaggreg::Quality<lp_quality_type> > lpaggreg::OPartition<T>::getQuality() const
{
    return quality;
}

template<typename T>
void lpaggreg::OPartition<T>::setQuality(const shared_ptr<Quality<lp_quality_type> > &value)
{
    quality = value;
}

template<typename T>
void lpaggreg::OPartition<T>::computeParts()
{
    for (int i=0; i<cuts.size();i=cuts[i]+1){
        parts.push_back(OPart(i, cuts[i]));
    }
}
