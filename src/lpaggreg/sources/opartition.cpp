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


lpaggreg::OPartition::OPartition()
{

}

vector<int> lpaggreg::OPartition::getCuts() const
{
    return cuts;
}

void lpaggreg::OPartition::setCuts(const vector<int> &value)
{
    cuts = value;
}

vector<OPart> lpaggreg::OPartition::getParts() const
{
    return parts;
}

void lpaggreg::OPartition::setParts(const vector<OPart> &value)
{
    parts = value;
}

shared_ptr<lpaggreg::Quality<lp_quality_type> > lpaggreg::OPartition::getQuality() const
{
    return quality;
}

void lpaggreg::OPartition::setQuality(const shared_ptr<Quality<lp_quality_type> > &value)
{
    quality = value;
}

void lpaggreg::OPartition::computeParts()
{
    for (int i=0; i<cuts.size();i=cuts[i]+1){
        parts.push_back(OPart(i, cuts[i]));
    }
}
