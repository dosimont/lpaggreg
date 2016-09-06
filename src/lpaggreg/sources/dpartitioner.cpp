#include "dpartitioner.h"

lpaggreg::DPartitioner::DPartitioner(dqualities qualities, HValuesMetaData metaData):qualities(qualities), metaData(metaData)
{

}

lpaggreg::DPartitioner::DPartitioner(lpaggreg::DQualities qualities):qualities(qualities.getQualities()), metaData(qualities.getMetaData())
{

}

void lpaggreg::DPartitioner::computeBestPartitions(float threshold, float min, float max)
{
    pList.clear();
    partitions.clear();
    shared_ptr<DPartition> bestPartitionMin;
    shared_ptr<DPartition> bestPartitionMax;
    bestPartitionMin=computeBestPartition(min);
    pList.push_back(min);
    partitions[min]=bestPartitionMin;
    bestPartitionMax=computeBestPartition(max);
    addBestQualities(threshold, bestPartitionMin, bestPartitionMax);
    pList.push_back(max);
    partitions[max]=bestPartitionMax;
    for (auto it = pList.end(); it!=pList.begin();it--){
        auto it2=it-1;
        if (*(partitions[*it])==*(partitions[*it2])){
            partitions.erase(partitions.find(*it));
            pList.erase(it);
        }
    }
    for (auto it : partitions){
        for (auto it2 : it.second->getParts()){
            for (auto it3 : it2){
                tuple<float, int, int, int, int> t(it.first, it3.getH(), it3.getSize(), it3.getStart(), it3.getEnd());
                partitionsTuples.push_back(t);
            }
        }
    }
}


shared_ptr<lpaggreg::DPartition> lpaggreg::DPartitioner::computeBestPartition(float parameter)
{
    unsigned int hsize=metaData.getHsize();
    vector<shared_ptr<UpperTriangularMatrix<int> > > cuts = vector<shared_ptr<UpperTriangularMatrix<int> > >();
    vector<shared_ptr<UpperTriangularMatrix< shared_ptr<Tradeoff> > > > tradeoff = vector<shared_ptr<UpperTriangularMatrix< shared_ptr<Tradeoff> > > >();
    vector<shared_ptr<UpperTriangularMatrix< shared_ptr<Tradeoff> > > > tradeoffChildren= vector<shared_ptr<UpperTriangularMatrix< shared_ptr<Tradeoff> > > >();
    int osize=((*qualities)[0])->getSize();
    for (int h=0; h<hsize; h++){
        tradeoff.push_back(shared_ptr<UpperTriangularMatrix< shared_ptr<Tradeoff> > >(new UpperTriangularMatrix< shared_ptr<Tradeoff> >(osize)));
        tradeoffChildren.push_back(shared_ptr<UpperTriangularMatrix< shared_ptr<Tradeoff> > >(new UpperTriangularMatrix< shared_ptr<Tradeoff> >(osize)));
        cuts.push_back(shared_ptr<UpperTriangularMatrix<int> >(new UpperTriangularMatrix<int>(osize, osize-1)));
    }
/*
    int i=0;
    int h;
    for (h = (metaData.getPath())[i]; i < metaData.getLeaveSize(); h = (metaData.getPath())[++i]){
        (tradeoff[h])->set((*qualities)[h], parameter);
        (*tradeoffChildren[(metaData.getParents())[h]])+=*(tradeoff[h]);
        shared_ptr<Tradeoff> tradeoff_t=shared_ptr<Tradeoff>(new Tradeoff());
        for (int i=size-1;i>=0;i--){
            *(tradeoff[h])(i,j)->set(qualities->operator()(i,size-1), parameter);
            for (int cut_t=i; cut_t<size-1; cut_t++){
                tradeoff_t->set(qualities->operator()(i,cut_t), parameter);
                *tradeoff_t+=*(tradeoff[cut_t+1]);
                if (*tradeoff_t>*(tradeoff[i])){
                    cut[i]=cut_t;
                    *(tradeoff[i])=*(tradeoff_t);
                }
            }
        }
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
    return partition;*/
    return shared_ptr<DPartition>(new DPartition(cuts, qualities, parameter, metaData));
}


list<tuple<float, int, int, int, int> > lpaggreg::DPartitioner::getPartitionsTuples() const
{
    return partitionsTuples;
}

map<float, shared_ptr<lpaggreg::DPartition> > lpaggreg::DPartitioner::getPartitions() const
{
    return partitions;
}

void lpaggreg::DPartitioner::addBestQualities(float threshold, shared_ptr<DPartition> bestPartitionMin, shared_ptr<DPartition> bestPartitionMax)
{
    if ((*bestPartitionMin!=*bestPartitionMax)&&bestPartitionMax->getParameter()-bestPartitionMin->getParameter()>threshold){
        float parameter=bestPartitionMin->getParameter()+(bestPartitionMax->getParameter()-bestPartitionMin->getParameter())/2;
        shared_ptr<DPartition> bestPartitionMid;
        bestPartitionMid=computeBestPartition(parameter);
        addBestQualities(threshold, bestPartitionMin, bestPartitionMid);
        pList.push_back(parameter);
        partitions[parameter]=bestPartitionMid;
        addBestQualities(threshold, bestPartitionMid, bestPartitionMax);
    }
}
