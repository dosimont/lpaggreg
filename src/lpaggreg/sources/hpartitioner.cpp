#include "hpartitioner.h"


lpaggreg::HPartitioner::HPartitioner(hqualities qualities, HValuesMetaData metaData):qualities(qualities), metaData(metaData)
{

}

lpaggreg::HPartitioner::HPartitioner(lpaggreg::HQualities qualities):qualities(qualities.getQualities()), metaData(qualities.getMetaData())
{

}

void lpaggreg::HPartitioner::computeBestPartitions(float threshold, float min, float max)
{
    pList.clear();
    partitions.clear();
    partitionsTuples.clear();
    qualityList.clear();
    shared_ptr<HPartition> bestPartitionMin;
    shared_ptr<HPartition> bestPartitionMax;
    bestPartitionMin=computeBestPartition(min);
    pList.push_back(min);
    partitions[min]=bestPartitionMin;
    bestPartitionMax=computeBestPartition(max);
    addBestQualities(threshold, bestPartitionMin, bestPartitionMax);
    pList.push_back(max);
    partitions[max]=bestPartitionMax;
    for (auto it = pList.end()-1; it!=pList.begin();it--){
        auto it2=it-1;
        if (*(partitions[*it])==*(partitions[*it2])){
            partitions.erase(partitions.find(*it));
            pList.erase(it);
        }
    }
    for (auto it : partitions){
        for (auto it2 : it.second->getParts()){
            tuple<float, int, int, lp_quality_type, lp_quality_type> t(it.first, it2.getH(), it2.getSize(), it2.getQuality()->getGain(), it2.getQuality()->getLoss());
            partitionsTuples.push_back(t);
        }
        qualityList[it.first]=it.second->getQuality();
    }
}

shared_ptr<lpaggreg::HPartition> lpaggreg::HPartitioner::computeBestPartition(float parameter)
{
    unsigned int hsize=metaData.getHsize();
    vector<shared_ptr<Tradeoff> > tradeoff= vector<shared_ptr<Tradeoff> >();
    vector<shared_ptr<Tradeoff> > tradeoffChildren= vector<shared_ptr<Tradeoff> >();
    vector<bool> aggregated;
    for (int h=0; h<hsize; h++){
        tradeoff.push_back(shared_ptr<Tradeoff>(new Tradeoff()));
        tradeoffChildren.push_back(shared_ptr<Tradeoff>(new Tradeoff()));
        aggregated.push_back(true);
    }
    int i=0;
    int h;
    for (h = (metaData.getPath())[i]; i < metaData.getLeaveSize(); h = (metaData.getPath())[++i]){
        (tradeoff[h])->set((*qualities)[h], parameter);
        (*tradeoffChildren[(metaData.getParents())[h]])+=*(tradeoff[h]);
    }
    for (h = (metaData.getPath())[i]; i < hsize-1; h = (metaData.getPath())[++i]){
        (tradeoff[h])->set((*qualities)[h], parameter);
        if ((*tradeoff[h])<(*tradeoffChildren[h])){
            aggregated[h]=false;
            (*tradeoff[h])=(*tradeoffChildren[h]);
        }
        (*tradeoffChildren[(metaData.getParents())[h]])+=*(tradeoff[h]);
    }
    (tradeoff[h])->set((*qualities)[h], parameter);
    if ((*tradeoff[h])<(*tradeoffChildren[h])){
        aggregated[h]=false;
        (*tradeoff[h])=(*tradeoffChildren[h]);
    }
    shared_ptr<HPartition> partition=shared_ptr<HPartition>(new HPartition(aggregated, qualities, parameter, metaData));
    return partition;
}

list<tuple<float, int, int, lp_quality_type, lp_quality_type> > lpaggreg::HPartitioner::getPartitionsTuples() const
{
    return partitionsTuples;
}

map<float, shared_ptr<lpaggreg::HPartition> > lpaggreg::HPartitioner::getPartitions() const
{
    return partitions;
}

void lpaggreg::HPartitioner::addBestQualities(float threshold, shared_ptr<HPartition> bestPartitionMin, shared_ptr<HPartition> bestPartitionMax)
{
    if ((*bestPartitionMin!=*bestPartitionMax)&&bestPartitionMax->getParameter()-bestPartitionMin->getParameter()>threshold){
        float parameter=bestPartitionMin->getParameter()+(bestPartitionMax->getParameter()-bestPartitionMin->getParameter())/2;
        shared_ptr<HPartition> bestPartitionMid;
        bestPartitionMid=computeBestPartition(parameter);
        addBestQualities(threshold, bestPartitionMin, bestPartitionMid);
        pList.push_back(parameter);
        partitions[parameter]=bestPartitionMid;
        addBestQualities(threshold, bestPartitionMid, bestPartitionMax);
    }
}
