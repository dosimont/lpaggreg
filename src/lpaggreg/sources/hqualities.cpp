#include "hqualities.h"


lpaggreg::HQualities::HQualities(hqualities qualities, HValuesMetaData metaData):qualities(qualities), values(0), metaData(metaData)
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
    qualities=hqualities(new vector<shared_ptr<Quality> >(hsize));
    for (int h = 0; h < hsize; h++){
        (*qualities)[h]=shared_ptr<Quality>(new Quality());
    }
    for (int k=0; k < vsize; k++){
        int i=0;
        int h;
        vector<lp_quality_type> sum(hsize,0);
        vector<lp_quality_type> info(hsize,0);
        for (h = (metaData.getPath())[i]; i < metaData.getLeaveSize(); h = (metaData.getPath())[++i]){
            sum[h] = (*values)[h][k];
            sum[(metaData.getParents())[h]]+=sum[h];
            info[h] = entropyReduction(sum[h], 0);
            info[(metaData.getParents())[h]]+=info[h];
        }
        for (h = (metaData.getPath())[i]; i < hsize-1; h = (metaData.getPath())[++i]){
            sum[(metaData.getParents())[h]]+=sum[h];
            info[(metaData.getParents())[h]]+=info[h];
            (*qualities)[h]->addToGain(entropyReduction(sum[h], info[h]));
            (*qualities)[h]->addToLoss(divergence((metaData.getSize())[h],sum[h], info[h]));
        }
        (*qualities)[h]->addToGain(entropyReduction(sum[h], info[h]));
        (*qualities)[h]->addToLoss(divergence((metaData.getSize())[h],sum[h], info[h]));
    }
}

unsigned int lpaggreg::HQualities::size()
{
    return qualities->size();
}

hqualities lpaggreg::HQualities::getQualities() const
{
    return qualities;
}

lpaggreg::HValuesMetaData lpaggreg::HQualities::getMetaData() const
{
    return metaData;
}
