#include "opartition.h"


lpaggreg::OPart::OPart(int start, int end):start(start), end(end)
{

}

int lpaggreg::OPart::getStart() const
{
    return start;
}

int lpaggreg::OPart::getEnd() const
{
    return end;
}

int lpaggreg::OPart::getSize()
{
    return end-start+1;
}


lpaggreg::OPartition::OPartition(vector<int> cuts, oqualities qualities, float parameter): Partition(parameter), cuts(cuts), qualities(qualities)
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


oqualities lpaggreg::OPartition::getQualities() const
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
            if ((opartition1.getParts())[i]!=(opartition2.getParts())[i]){
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








