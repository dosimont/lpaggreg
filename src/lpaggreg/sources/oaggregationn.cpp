#include "oaggregationn.h"

lpaggreg::OAggregate1::OAggregate1(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN1> values): OAggregate(part), values(values)
{

}

void lpaggreg::OAggregate1::compute()
{
    sum=0;
    for (int o=part.getStart(); o<=part.getEnd();o++){
        sum+=(*values)(o);
    }
    mean=sum/part.getSize();
}

lpaggreg::OAggregate2::OAggregate2(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN2> values): OAggregate(part), values(values)
{
    compute();
}

void lpaggreg::OAggregate2::compute()
{
    for (int i=0; i<values->getVsize(); i++){
        sum[i]=0;
        for (int o=part.getStart(); o<=part.getEnd();o++){
            sum[i]+=(*values)(o, i);
        }
        mean[i]=sum[i]/part.getSize();
    }
}

lpaggreg::OAggregate3::OAggregate3(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN3> values): OAggregate(part), values(values)
{
    compute();
}

void lpaggreg::OAggregate3::compute()
{
    for (int i=0; i<values->getI(); i++){
        for (int j=0; j<values->getJ(); j++){
            sum[i][j]=0;
            for (int o=part.getStart(); o<=part.getEnd();o++){
                sum[i][j]+=(*values)(o, i, j);
            }
            mean[i][j]=sum[i][j]/part.getSize();
        }
    }
}

lpaggreg::OAggregate4::OAggregate4(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN4> values): OAggregate(part), values(values)
{
    compute();
}

void lpaggreg::OAggregate4::compute()
{
    for (int i=0; i<values->getI(); i++){
        for (int j=0; j<values->getJ(); j++){
            for (int k=0; k<values->getK(); k++){
                sum[i][j][k]=0;
                for (int o=part.getStart(); o<=part.getEnd();o++){
                    sum[i][j][k]+=(*values)(o, i, j, k);
                }
                mean[i][j][k]=sum[i][j][k]/part.getSize();
            }
        }
    }
}

lpaggreg::OAggregation1::OAggregation1(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN1> values):OAggregation(opartition)
{

}

lpaggreg::OAggregation2::OAggregation2(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN2> values):OAggregation(opartition)
{

}

lpaggreg::OAggregation3::OAggregation3(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN3> values):OAggregation(opartition)
{

}

lpaggreg::OAggregation4::OAggregation4(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN4> values):OAggregation(opartition)
{

}
