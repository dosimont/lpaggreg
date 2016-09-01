#include "dvalues.h"


lpaggreg::HValuesMetaData lpaggreg::DValues::getMetaData() const
{
    return metaData;
}

lpaggreg::DValuesProxy lpaggreg::DValues::operator[](unsigned int h)
{
    return DValuesProxy(h,this);
}

unsigned int lpaggreg::DValues::getOsize() const
{
    return osize;
}


unsigned int lpaggreg::DValues::getVsize() const
{
    return vsize;
}

lpaggreg::DValues::DValues(unsigned int leaves, unsigned int vsize, unsigned int osize, vector<int> parents): osize(osize), vsize(vsize), metaData(HValuesMetaData(leaves, parents))
{

}

lpaggreg::DValuesProxy::DValuesProxy(int h, lpaggreg::DValues *dvalues): dvalues(dvalues), h(h)
{

}

vector<double> lpaggreg::DValuesProxy::operator[](unsigned int index)
{
    return dvalues->getValue(h, index);
}
