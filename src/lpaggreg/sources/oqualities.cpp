#include "oqualities.h"

lpaggreg::OQualities::OQualities()
{

}

void lpaggreg::OQualities::normalize()
{
    Quality max=qualities(0, values->osize()-1);
    for (int i=0; i<qualities.getElements(); i++){
        qualities[i]/=max;
    }
}

void lpaggreg::OQualities::computeQualities()
{
    unsigned osize=values->osize();
    unsigned vsize=values->vsize();
    UpperTriangularMatrix<double> sum(osize);
    UpperTriangularMatrix<double> info(osize);
    qualities=UpperTriangularMatrix<Quality<lp_quality_type>>(osize);
    for (int k = 0; k < vsize; k++) {
        for (int i = osize-1; i >=0; i--) {
            sum(i,i)=values[k][i];
            info(i,i)=entropyReduction(values[k][i], 0);
            for (int j = i+1; j < osize-1; j++) {
                sum(i,j)=sum(i+1,j)+sum(i,i);
                info(i,j)=info(i+1,j)=info(i,i);
                qualities(i,j).addToGain(entropyReduction(sum(i,j), info(i,j)));
                qualities(i,j).addToLoss(divergence(j+1, sum(i,j), info(i,j)));
            }
        }
    }
}

lpaggreg::OValues *lpaggreg::OQualities::getValues() const
{
    return values;
}

void lpaggreg::OQualities::setValues(lpaggreg::OValues *value)
{
    values = value;
}

unsigned int lpaggreg::OQualities::size()
{
    return qualities.getSize();
}
