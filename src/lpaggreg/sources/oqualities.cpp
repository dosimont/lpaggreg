#include "oqualities.h"

lpaggreg::OQualities::OQualities(shared_ptr<lpaggreg::OValues> values):values(values)
{

}

void lpaggreg::OQualities::normalize()
{
    shared_ptr<Quality> max=(*qualities)(0, values->getOsize()-1);
    for (int i=0; i<qualities->getElements(); i++){
        (*(*qualities)[i])/=(*max);
    }
}

void lpaggreg::OQualities::computeQualities()
{
    unsigned osize=values->getOsize();
    unsigned vsize=values->getVsize();
    UpperTriangularMatrix<lp_quality_type> sum(osize);
    UpperTriangularMatrix<lp_quality_type> info(osize);
    qualities=shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > >(new UpperTriangularMatrix<shared_ptr<Quality> >(osize));
    for (int k = 0; k < vsize; k++) {
        for (int i = osize-1; i >=0; i--) {
            sum(i,i,(*values)[k][i]);
            info(i,i,entropyReduction((*values)[k][i], 0));
            for (int j = i+1; j < osize; j++) {
                sum(i,j,sum(i+1,j)+sum(i,i));
                info(i,j,info(i+1,j)+info(i,i));
                (*qualities)(i,j)->addToGain(entropyReduction(sum(i,j), info(i,j)));
                (*qualities)(i,j)->addToLoss(divergence(j-i+1, sum(i,j), info(i,j)));
            }
        }
    }
}

unsigned int lpaggreg::OQualities::size()
{
    return qualities->getSize();
}

shared_ptr<lpaggreg::OValues> lpaggreg::OQualities::getValues() const
{
    return values;
}

shared_ptr<lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality> > > lpaggreg::OQualities::getQualities() const
{
    return qualities;
}
