#include "hpartition.h"


lpaggreg::HPart::HPart(int h, int size, shared_ptr<Quality> quality):h(h), size(size), quality(quality)
{

}

int lpaggreg::HPart::getH() const
{
    return h;
}

int lpaggreg::HPart::getSize() const
{
    return size;
}

shared_ptr<lpaggreg::Quality> lpaggreg::HPart::getQuality() const
{
    return quality;
}

bool lpaggreg::operator==(lpaggreg::HPart &hpart1, lpaggreg::HPart &hpart2)
{
    return (hpart1.getSize()==hpart2.getSize()&&hpart1.getH()==hpart2.getH());
}

bool lpaggreg::operator!=(lpaggreg::HPart &hpart1, lpaggreg::HPart &hpart2)
{
    return !(hpart1==hpart2);
}

#ifndef PARTITION_COMPARE_QUALITY

bool lpaggreg::operator==(lpaggreg::HPartition &hpartition1, lpaggreg::HPartition &hpartition2)
{
    if (hpartition1.getParts().size()!=hpartition2.getParts().size()){
        return false;
    }else{
        for (int i=0; i<hpartition1.getParts().size(); i++){
            if ((hpartition1.getParts())[i]!=(hpartition2.getParts())[i]){
                return false;
            }
        }
        return true;
    }
}
#endif

#ifdef PARTITION_COMPARE_QUALITY

bool lpaggreg::operator==(lpaggreg::HPartition &hpartition1, lpaggreg::HPartition &hpartition2)
{
    return (hpartition1.getQuality()==hpartition2.getQuality());
}
#endif


bool lpaggreg::operator!=(lpaggreg::HPartition &hpartition1, lpaggreg::HPartition &hpartition2)
{
    return !(hpartition1==hpartition2);
}

lpaggreg::HPartition::HPartition(vector<bool> aggregated, shared_ptr<vector<shared_ptr<lpaggreg::Quality> > > qualities, float parameter, lpaggreg::HValuesMetaData metaData):
    Partition(parameter), aggregated(aggregated), qualities(qualities), metaData(metaData)
{
    computeParts();
    computeQuality();
}

void lpaggreg::HPartition::computeParts()
{
    parts.clear();
    computeSubPart(metaData.getRoot());
}

void lpaggreg::HPartition::computeSubPart(int h){
    if(aggregated[h]){
        parts.push_back(HPart(h,(metaData.getSize())[h],(*qualities)[h]));
    }else{
        for (int i=0; i<metaData.getChildren().operator [](h).size(); i++){
            int child=metaData.getChildren().operator [](h).operator [](i);
            computeSubPart(child);
        }
    }
}


void lpaggreg::HPartition::computeQuality()
{
    quality=shared_ptr<Quality>(new Quality());
    for (HPart it: parts){
        *quality+=*(it.getQuality());
    }
}


lpaggreg::HValuesMetaData lpaggreg::HPartition::getMetaData() const
{
    return metaData;
}

shared_ptr<vector<shared_ptr<lpaggreg::Quality> > > lpaggreg::HPartition::getQualities() const
{
    return qualities;
}

vector<lpaggreg::HPart> lpaggreg::HPartition::getParts() const
{
    return parts;
}

vector<bool> lpaggreg::HPartition::getAggregated() const
{
    return aggregated;
}
