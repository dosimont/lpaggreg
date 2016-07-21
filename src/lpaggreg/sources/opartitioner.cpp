#include "opartitioner.h"

lpaggreg::OPartitioner::OPartitioner(shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > >):qualities(qualities)
{

}

void lpaggreg::OPartitioner::computeBestPartitions(float threshold, float min, float max)
{
    shared_ptr<OPartition> bestPartitionMin;
    shared_ptr<OPartition> bestPartitionMax;
    bestPartitionMin=computeBestPartition(min);
    pList.push_back(min);
    partitions[min]=bestPartitionMin;
    bestPartitionMax=computeBestPartition(max);
    addBestQualities(threshold, bestPartitionMin, bestPartitionMax);
    pList.push_back(max);
    partitions[max]=bestPartitionMax;
}

shared_ptr<lpaggreg::OPartition> lpaggreg::OPartitioner::computeBestPartition(float parameter)
{
    int size=qualities->getSize();
    vector<int> cut(size, size-1);
    vector<shared_ptr<Tradeoff> > tradeoff= vector<shared_ptr<Tradeoff> >(size, shared_ptr<Tradeoff>(new Tradeoff()));
    shared_ptr<Tradeoff> tradeoff_t=shared_ptr<Tradeoff>(new Tradeoff());
    for (int i=size-1;i>=0;i--){
        (tradeoff[i])->set(qualities->operator()(i,size-1), parameter);
        for (int cut_t=i; cut_t<size-2; cut_t++){
            tradeoff_t->set(qualities->operator()(i,cut_t), parameter);
            *tradeoff_t+=*tradeoff[cut_t+1];
            if (*tradeoff_t>*tradeoff[i]){
                cut[i]=cut_t;
                tradeoff[i]=tradeoff_t;
            }
        }
    }
    shared_ptr<OPartition> partition=shared_ptr<OPartition>(new OPartition<lp_quality_type>(cut, qualities, parameter));
    return partition;
}

void lpaggreg::OPartitioner::addBestQualities(float threshold, shared_ptr<OPartition> bestPartitionMin, shared_ptr<OPartition> bestPartitionMax)
{
    if (bestPartitionMin!=bestPartitionMax||bestPartitionMax->getParameter()-bestPartitionMin->getParameter()<=threshold){
        float parameter=bestPartitionMin->getParameter()+(bestPartitionMax->getParameter()-bestPartitionMin->getParameter())/2;
        shared_ptr<OPartition> bestPartitionMid;
        bestPartitionMid=computeBestPartition(parameter);
        if (bestPartitionMid!=bestPartitionMin&&bestPartitionMid!=bestPartitionMax){
            addBestQualities(threshold, bestPartitionMin, bestPartitionMid);
            pList.push_back(parameter);
            partitions[parameter]=bestPartitionMid;
            addBestQualities(threshold, bestPartitionMid, bestPartitionMax);
        }
    }
}


