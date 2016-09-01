#include "dqualities.h"

lpaggreg::DQualities::DQualities(shared_ptr<vector< shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > > > qualities, HValuesMetaData metaData):qualities(qualities), values(0), metaData(metaData)
{

}

lpaggreg::DQualities::DQualities(shared_ptr<lpaggreg::DValues> values):values(values), metaData(values->getMetaData())
{

}

void lpaggreg::DQualities::normalize()
{
    //TODO
    /*shared_ptr<Quality> max=(*qualities)[metaData.getRoot()];
    for (auto quality : *qualities){
        *quality/=*max;
    }*/
}

void lpaggreg::DQualities::computeQualities()
{
    if (values==0){
        return;
    }
    //TODO
    /*unsigned hsize=metaData.getHsize();
    unsigned vsize=values->getVsize();
    qualities=shared_ptr<vector<shared_ptr<Quality> > >(new vector<shared_ptr<Quality> >(hsize));
    for (int h = 0; h < hsize; h++){
        (*qualities)[h]=shared_ptr<Quality>(new Quality());
    }
    for (int v=0; v < vsize; v++){
        int i=0;
        int h;
        vector<lp_quality_type> sum(hsize,0);
        vector<lp_quality_type> info(hsize,0);
        for (h = metaData.getPath().operator [](i); i < metaData.getLeaveSize(); h = metaData.getPath().operator [](++i)){
            sum[h] = (*values)[h][v];
            sum[(metaData.getParents())[h]]+=sum[h];
            info[h] = entropyReduction(sum[h], 0);
            info[(metaData.getParents())[h]]+=info[h];
        }
        for (h = metaData.getPath().operator [](i); i < hsize-1; h = metaData.getPath().operator [](++i)){
            sum[(metaData.getParents())[h]]+=sum[h];
            info[(metaData.getParents())[h]]+=info[h];
            (*qualities)[h]->addToGain(entropyReduction(sum[h], info[h]));
            (*qualities)[h]->addToLoss(divergence((metaData.getSize())[h],sum[h], info[h]));
        }
        (*qualities)[h]->addToGain(entropyReduction(sum[h], info[h]));
        (*qualities)[h]->addToLoss(divergence((metaData.getSize())[h],sum[h], info[h]));
    }*/
}

unsigned int lpaggreg::DQualities::size()
{
    return qualities->size();
}

lpaggreg::HValuesMetaData lpaggreg::DQualities::getMetaData() const
{
    return metaData;
}

shared_ptr<vector<shared_ptr<lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality> > > > > lpaggreg::DQualities::getQualities() const
{
    return qualities;
}
