#include "dqualities.h"

lpaggreg::DQualities::DQualities(dqualities qualities, HValuesMetaData metaData):qualities(qualities), values(0), metaData(metaData)
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
    unsigned hsize=metaData.getHsize();
    unsigned osize=values->getOsize();
    unsigned vsize=values->getVsize();
    qualities=dqualities(new vector<shared_ptr<UpperTriangularMatrix<shared_ptr<lpaggreg::Quality> > > >(hsize));
    for (int h = 0; h < hsize; h++){
        (*qualities)[h]=oqualities(new UpperTriangularMatrix<shared_ptr<lpaggreg::Quality> >(osize));
    }
    for (int k=0; k < vsize; k++){
        int i=0;
        int h;
        vector<UpperTriangularMatrix<lp_quality_type> > sum;
        vector<UpperTriangularMatrix<lp_quality_type> > info;
        for (h=0; h<hsize; h++){
            sum.push_back(UpperTriangularMatrix<lp_quality_type>(osize));
            sum.push_back(UpperTriangularMatrix<lp_quality_type>(osize));
        }
        for (h = metaData.getPath().operator [](i); i < metaData.getLeaveSize(); h = metaData.getPath().operator [](++i)){
            for (int i = osize-1; i >=0; i--) {
                (sum[h])(i,i,(*values)[h][k][i]);
                (info[h])(i,i,entropyReduction((*values)[h][k][i], 0));
                (sum[(metaData.getParents())[h]])(i,i,(sum[(metaData.getParents())[h]])(i,i)+(sum[h])(i,i));
                (info[(metaData.getParents())[h]])(i,i,(info[(metaData.getParents())[h]])(i,i)+(info[h])(i,i));
                for (int j = i+1; j < osize; j++) {
                    (sum[h])(i,j,(sum[h])(i+1,j)+(sum[h])(i,i));
                    (info[h])(i,j,(info[h])(i+1,j)+(info[h])(i,i));
                    (*(*qualities)[h])(i,j)->addToGain(entropyReduction((sum[h])(i,j), (info[h])(i,j)));
                    (*(*qualities)[h])(i,j)->addToLoss(divergence(j-i+1, (sum[h])(i,j), (info[h])(i,j)));
                    (sum[(metaData.getParents())[h]])(i,j,(sum[(metaData.getParents())[h]])(i,j)+(sum[h])(i,j));
                    (info[(metaData.getParents())[h]])(i,j,(info[(metaData.getParents())[h]])(i,j)+(info[h])(i,j));
                }
            }
        }
        for (h = metaData.getPath().operator [](i); i < hsize-1; h = metaData.getPath().operator [](++i)){
            for (int i = osize-1; i >=0; i--) {
                for (int j = i; j < osize; j++) {
                    (*(*qualities)[h])(i,j)->addToGain(entropyReduction((sum[h])(i,j), (info[h])(i,j)));
                    (*(*qualities)[h])(i,j)->addToLoss(divergence((j-i+1)*(metaData.getSize())[h], (sum[h])(i,j), (info[h])(i,j)));
                    (sum[(metaData.getParents())[h]])(i,j,(sum[(metaData.getParents())[h]])(i,j)+(sum[h])(i,j));
                    (info[(metaData.getParents())[h]])(i,j,(info[(metaData.getParents())[h]])(i,j)+(info[h])(i,j));
                }
            }
        }
        for (int i = osize-1; i >=0; i--) {
            for (int j = i; j < osize; j++) {
                (*(*qualities)[h])(i,j)->addToGain(entropyReduction((sum[h])(i,j), (info[h])(i,j)));
                (*(*qualities)[h])(i,j)->addToLoss(divergence((j-i+1)*(metaData.getSize())[h], (sum[h])(i,j), (info[h])(i,j)));
            }
        }
    }
}

unsigned int lpaggreg::DQualities::size()
{
    return qualities->size();
}

lpaggreg::HValuesMetaData lpaggreg::DQualities::getMetaData() const
{
    return metaData;
}

dqualities lpaggreg::DQualities::getQualities() const
{
    return qualities;
}
