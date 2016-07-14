#include "oqualities.h"

void lpaggreg::OQualities::normalize()
{
    shared_ptr<Quality<lp_quality_type> > max=(*qualities)(0, values->getOsize()-1);
    for (int i=0; i<qualities->getElements(); i++){
        (*(*qualities)[i])/=(*max);
    }
}

void lpaggreg::OQualities::computeQualities()
{
    unsigned osize=values->getOsize();
    unsigned vsize=values->getVsize();
    UpperTriangularMatrix<double> sum(osize);
    UpperTriangularMatrix<double> info(osize);
    qualities=shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > > >(new UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > >(osize));
    for (int k = 0; k < vsize; k++) {
        for (int i = osize-1; i >=0; i--) {
            sum(i,i,(*values)[k][i]);
            info(i,i,entropyReduction((*values)[k][i], 0));
            for (int j = i+1; j < osize-1; j++) {
                sum(i,j,sum(i+1,j)+sum(i,i));
                info(i,j,info(i+1,j)+info(i,i));
                (*qualities)(i,j)->addToGain(entropyReduction(sum(i,j), info(i,j)));
                (*qualities)(i,j)->addToLoss(divergence(j+1, sum(i,j), info(i,j)));
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

shared_ptr<lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality<lp_quality_type> > > > lpaggreg::OQualities::getQualities() const
{
    return qualities;
}
