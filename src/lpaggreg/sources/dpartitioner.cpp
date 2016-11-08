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
    partitionsTuples.clear();
    qualityList.clear();
    shared_ptr<DPartition> bestPartitionMin;
    shared_ptr<DPartition> bestPartitionMax;
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
            tuple<float, int, int, int, int, lp_quality_type, lp_quality_type> t(it.first, it2.getH(), it2.getSize(), it2.getStart(), it2.getEnd(), it2.getQuality()->getGain(), it2.getQuality()->getLoss());
            partitionsTuples.push_back(t);
        }
        qualityList[it.first]=it.second->getQuality();
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
    int k=0;
    int h;
    for (h = (metaData.getPath())[k]; k < hsize; h = (metaData.getPath())[++k]){
        for (int i=osize-1;i>=0;i--){
            for (int j=i; j<=osize-1; j++){
                (*(cuts[h]))(i, j, j);
                ((*(tradeoff[h]))(i, j))->set((*((*qualities)[h]))(i, j), parameter);
                if (k>=metaData.getLeaveSize()){
                    if (*((*(tradeoffChildren[h]))(i, j))>*((*(tradeoff[h]))(i, j))){
                        (*(cuts[h]))(i, j, -1);
                        *((*(tradeoff[h]))(i, j))=*((*(tradeoffChildren[h]))(i, j));
                    }
                }
                for (int cut_t=i; cut_t<j; cut_t++){
                    shared_ptr<Tradeoff> tradeoff_t=shared_ptr<Tradeoff>(new Tradeoff());
                    ((*(tradeoff[h]))(i, cut_t))->set((*((*qualities)[h]))(i, cut_t), parameter);
                     *tradeoff_t+=*((*(tradeoff[h]))(i, cut_t));
                     *tradeoff_t+=*((*(tradeoff[h]))(cut_t+1, j));
                    if (*tradeoff_t>*((*(tradeoff[h]))(i, j))){
                        (*(cuts[h]))(i, j, cut_t);
                        *((*(tradeoff[h]))(i, j))=*tradeoff_t;
                    }
                }
                if (k<hsize-1){
                    *((*(tradeoffChildren[(metaData.getParents())[h]]))(i, j))+=*((*(tradeoff[h]))(i, j));
                }
            }
        }
        if (h==metaData.getRoot()){
            break;
        }
    }
    shared_ptr<DPartition> partition= shared_ptr<DPartition>(new DPartition(cuts, qualities, parameter, metaData));
    return partition;
}


list<tuple<float, int, int, int, int, lp_quality_type, lp_quality_type> > lpaggreg::DPartitioner::getPartitionsTuples() const
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
