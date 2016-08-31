#include "opartition.h"


lpaggreg::OPart::OPart(int start, int end):start(start), end(end)
{

}

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

int lpaggreg::OPart::getSize()
{
    return end-start+1;
}


lpaggreg::OPartition::OPartition(vector<int> cuts, shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > qualities, float parameter):parameter(parameter), cuts(cuts), qualities(qualities)
{
    computeParts();
    computeQuality();
}


vector<int> lpaggreg::OPartition::getCuts() const
{
    return cuts;
}


vector<lpaggreg::OPart> lpaggreg::OPartition::getParts() const
{
    return parts;
}


void lpaggreg::OPartition::computeParts()
{
    parts.clear();
    for (int i=0; i<cuts.size();i=cuts[i]+1){
        parts.push_back(OPart(i, cuts[i]));
    }
}


void lpaggreg::OPartition::computeQuality()
{
    quality=shared_ptr<Quality>(new Quality());
    for (OPart it: parts){
        *quality+=*(qualities->operator ()(it.getStart(),it.getEnd()));
    }
}

shared_ptr<lpaggreg::Quality> lpaggreg::OPartition::getQuality() const
{
    return quality;
}


float lpaggreg::OPartition::getParameter() const
{
    return parameter;
}


shared_ptr<lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality> > > lpaggreg::OPartition::getQualities() const
{
    return qualities;
}

bool lpaggreg::operator==(lpaggreg::OPart &opart1, lpaggreg::OPart &opart2)
{
    return (opart1.getStart()==opart2.getStart()&&opart1.getEnd()==opart2.getEnd());
}

bool lpaggreg::operator!=(lpaggreg::OPart &opart1, lpaggreg::OPart &opart2)
{
    return !(opart1==opart2);
}

#ifndef PARTITION_COMPARE_QUALITY

bool lpaggreg::operator==(lpaggreg::OPartition &opartition1, lpaggreg::OPartition &opartition2)
{
    if (opartition1.getParts().size()!=opartition2.getParts().size()){
        return false;
    }else{
        for (int i=0; i<opartition1.getParts().size(); i++){
            if (opartition1.getParts().operator [](i)!=opartition2.getParts().operator [](i)){
                return false;
            }
        }
        return true;
    }
}
#endif

#ifdef PARTITION_COMPARE_QUALITY

bool lpaggreg::operator==(lpaggreg::OPartition &opartition1, lpaggreg::OPartition &opartition2)
{
    return (opartition1.getQuality()==opartition2.getQuality());
}
#endif


bool lpaggreg::operator!=(lpaggreg::OPartition &opartition1, lpaggreg::OPartition &opartition2)
{
    return !(opartition1==opartition2);
}








