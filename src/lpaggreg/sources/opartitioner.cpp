#include "opartitioner.h"

lpaggreg::OPartitioner::OPartitioner(oqualities qualities):qualities(qualities)
{

}

lpaggreg::OPartitioner::OPartitioner(lpaggreg::OQualities qualities):qualities(qualities.getQualities())
{

}

void lpaggreg::OPartitioner::computeBestPartitions(float threshold, float min, float max)
{
    pList.clear();
    partitions.clear();
    partitionsTuples.clear();
    qualityList.clear();
    shared_ptr<OPartition> bestPartitionMin;
    shared_ptr<OPartition> bestPartitionMax;
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
            tuple<float, int, int, lp_quality_type, lp_quality_type> t(it.first, it2.getStart(), it2.getEnd(), it2.getQuality()->getGain(), it2.getQuality()->getLoss());
            partitionsTuples.push_back(t);
        }
        qualityList[it.first]=it.second->getQuality();
    }
}

shared_ptr<lpaggreg::OPartition> lpaggreg::OPartitioner::computeBestPartition(float parameter)
{
    int size=qualities->getSize();
    vector<int> cut(size, size-1);
    vector<shared_ptr<Tradeoff> > tradeoff= vector<shared_ptr<Tradeoff> >();
    for (int i=0; i<size; i++){
        tradeoff.push_back(shared_ptr<Tradeoff>(new Tradeoff()));
    }
    shared_ptr<Tradeoff> tradeoff_t=shared_ptr<Tradeoff>(new Tradeoff());
    for (int i=size-1;i>=0;i--){
        (tradeoff[i])->set(qualities->operator()(i,size-1), parameter);
        for (int cut_t=i; cut_t<size-1; cut_t++){
            tradeoff_t->set(qualities->operator()(i,cut_t), parameter);
            *tradeoff_t+=*(tradeoff[cut_t+1]);
            if (*tradeoff_t>*(tradeoff[i])){
                cut[i]=cut_t;
                *(tradeoff[i])=*(tradeoff_t);
            }
        }
    }
    shared_ptr<OPartition> partition=shared_ptr<OPartition>(new OPartition(cut, qualities, parameter));
    return partition;
}

void lpaggreg::OPartitioner::addBestQualities(float threshold, shared_ptr<OPartition> bestPartitionMin, shared_ptr<OPartition> bestPartitionMax)
{
    if ((*bestPartitionMin!=*bestPartitionMax)&&bestPartitionMax->getParameter()-bestPartitionMin->getParameter()>threshold){
        float parameter=bestPartitionMin->getParameter()+(bestPartitionMax->getParameter()-bestPartitionMin->getParameter())/2;
        shared_ptr<OPartition> bestPartitionMid;
        bestPartitionMid=computeBestPartition(parameter);
        addBestQualities(threshold, bestPartitionMin, bestPartitionMid);
        pList.push_back(parameter);
        partitions[parameter]=bestPartitionMid;
        addBestQualities(threshold, bestPartitionMid, bestPartitionMax);
    }
}

list<tuple<float, int, int, lp_quality_type, lp_quality_type> > lpaggreg::OPartitioner::getPartitionsTuples() const
{
    return partitionsTuples;
}

map<float, shared_ptr<lpaggreg::OPartition> > lpaggreg::OPartitioner::getPartitions() const
{
    return partitions;
}


