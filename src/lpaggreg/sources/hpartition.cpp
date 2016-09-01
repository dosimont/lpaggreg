#include "hpartition.h"


lpaggreg::HPart::HPart(int h, int size):h(h), size(size)
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
            if (hpartition1.getParts().operator [](i)!=hpartition2.getParts().operator [](i)){
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
    aggregated(aggregated), qualities(qualities), parameter(parameter), metaData(metaData)
{
    computeParts();
    computeQuality();
}

void lpaggreg::HPartition::computeParts()
{
    set<int> involved;
    parts.clear();
    if (aggregated[metaData.getRoot()]){
        parts.push_back(HPart(metaData.getRoot(), (metaData.getSize()[metaData.getRoot()])));
        return;
    }
    int i=metaData.getHsize()-2;
    for (int h = metaData.getPath().operator [](i); i >= 0; h = metaData.getPath().operator [](--i)){
        if (!(involved.find((metaData.getParents())[h]) != involved.end())){
            if(aggregated[h]){
                parts.push_back(HPart(h,(metaData.getSize())[h]));
                involved.insert(h);
            }
        }else{
            involved.insert(h);
        }
    }
}


void lpaggreg::HPartition::computeQuality()
{
    quality=shared_ptr<Quality>(new Quality());
    for (HPart it: parts){
        *quality+=*qualities->operator [](it.getH());
    }
}

float lpaggreg::HPartition::getParameter() const
{
    return parameter;
}


lpaggreg::HValuesMetaData lpaggreg::HPartition::getMetaData() const
{
    return metaData;
}

shared_ptr<vector<shared_ptr<lpaggreg::Quality> > > lpaggreg::HPartition::getQualities() const
{
    return qualities;
}

shared_ptr<lpaggreg::Quality> lpaggreg::HPartition::getQuality() const
{
    return quality;
}

vector<lpaggreg::HPart> lpaggreg::HPartition::getParts() const
{
    return parts;
}

vector<bool> lpaggreg::HPartition::getAggregated() const
{
    return aggregated;
}
