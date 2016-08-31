#include "hqualities.h"


lpaggreg::HQualities::HQualities(shared_ptr<vector<shared_ptr<lpaggreg::Quality> > > qualities, HValuesMetaData metaData):qualities(qualities), values(0), metaData(metaData)
{

}

lpaggreg::HQualities::HQualities(shared_ptr<lpaggreg::HValues> values):values(values), metaData(values->getMetaData())
{

}

void lpaggreg::HQualities::normalize()
{
    shared_ptr<Quality> max=(*qualities)[metaData.getRoot()];
    for (auto quality : *qualities){
        *quality/=*max;
    }
}

void lpaggreg::HQualities::computeQualities()
{
    if (values==0){
        return;
    }
    unsigned hsize=metaData.getHsize();
    unsigned vsize=values->getVsize();
    qualities=shared_ptr<vector<shared_ptr<Quality> > >(new vector<shared_ptr<Quality> >(hsize));
    for (int h = 0; h < hsize; h++){
        (*qualities)[h]=shared_ptr<Quality>(new Quality());
    }
    for (int v=0; v < vsize; v++){
        int i=0;
        vector<lp_quality_type> sum(hsize,0);
        vector<lp_quality_type> info(hsize,0);
        for (int h = metaData.getPath().operator [](i); i < metaData.getLeaves(); h = metaData.getPath().operator [](i++)){
            sum[h] = (*values)[h][v];
            sum[(metaData.getParents())[h]]+=sum[h];
            info[h] = entropyReduction(sum[h], 0);
            info[(metaData.getParents())[h]]+=sum[h];
        }
        for (int h = metaData.getPath().operator [](i); i < hsize; h = metaData.getPath().operator [](i++)){
            sum[(metaData.getParents())[h]]+=sum[h];
            info[(metaData.getParents())[h]]+=sum[h];
            (*qualities)[h]->addToGain(entropyReduction(sum[h], info[h]));
            (*qualities)[h]->addToLoss(divergence((metaData.getSize())[h],sum[h], info[h]));
        }
    }
}

unsigned int lpaggreg::HQualities::size()
{
    return qualities->size();
}

shared_ptr<vector<shared_ptr<lpaggreg::Quality> > > lpaggreg::HQualities::getQualities() const
{
    return qualities;
}

lpaggreg::HValuesMetaData lpaggreg::HQualities::getMetaData() const
{
    return metaData;
}
