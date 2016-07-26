#include "oaggregationn.h"

lpaggreg::OAggregate1::OAggregate1(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN1> values): OAggregate(part), values(values)
{
    compute();
}

void lpaggreg::OAggregate1::compute()
{
    sum=0;
    for (int o=part.getStart(); o<=part.getEnd();o++){
        sum+=(*values)(o);
    }
    mean=sum/part.getSize();
}

double lpaggreg::OAggregate1::getMean() const
{
    return mean;
}

double lpaggreg::OAggregate1::getSum() const
{
    return sum;
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

vector<double> lpaggreg::OAggregate2::getMean() const
{
    return mean;
}

vector<double> lpaggreg::OAggregate2::getSum() const
{
    return sum;
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

vector<vector<double> > lpaggreg::OAggregate3::getMean() const
{
    return mean;
}

vector<vector<double> > lpaggreg::OAggregate3::getSum() const
{
    return sum;
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

vector<vector<vector<double> > > lpaggreg::OAggregate4::getMean() const
{
    return mean;
}

vector<vector<vector<double> > > lpaggreg::OAggregate4::getSum() const
{
    return sum;
}

lpaggreg::OAggregation1::OAggregation1(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN1> values):OAggregation(opartition), values(values)
{
    for (auto it: opartition->getParts()){
        aggregates.push_back(OAggregate1(it, values));
    }
}

lpaggreg::OAggregation1::OAggregation1(shared_ptr<lpaggreg::OPartition> opartition, OQualities qualities):OAggregation1(opartition,dynamic_pointer_cast<lpaggreg::OValuesN1>(qualities.getValues()))
{

}

vector<lpaggreg::OAggregate1> lpaggreg::OAggregation1::getAggregates() const
{
    return aggregates;
}

lpaggreg::OAggregation2::OAggregation2(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN2> values):OAggregation(opartition), values(values)
{
    for (auto it: opartition->getParts()){
        aggregates.push_back(OAggregate2(it, values));
    }
}

lpaggreg::OAggregation2::OAggregation2(shared_ptr<lpaggreg::OPartition> opartition, OQualities qualities):OAggregation2(opartition,dynamic_pointer_cast<lpaggreg::OValuesN2>(qualities.getValues()))
{

}

vector<lpaggreg::OAggregate2> lpaggreg::OAggregation2::getAggregates() const
{
    return aggregates;
}

lpaggreg::OAggregation3::OAggregation3(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN3> values):OAggregation(opartition), values(values)
{
    for (auto it: opartition->getParts()){
        aggregates.push_back(OAggregate3(it, values));
    }
}

lpaggreg::OAggregation3::OAggregation3(shared_ptr<lpaggreg::OPartition> opartition, OQualities qualities):OAggregation3(opartition,dynamic_pointer_cast<lpaggreg::OValuesN3>(qualities.getValues()))
{

}

vector<lpaggreg::OAggregate3> lpaggreg::OAggregation3::getAggregates() const
{
    return aggregates;
}

lpaggreg::OAggregation4::OAggregation4(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN4> values):OAggregation(opartition), values(values)
{
    for (auto it: opartition->getParts()){
        aggregates.push_back(OAggregate4(it, values));
    }
}

lpaggreg::OAggregation4::OAggregation4(shared_ptr<lpaggreg::OPartition> opartition, OQualities qualities):OAggregation4(opartition,dynamic_pointer_cast<lpaggreg::OValuesN4>(qualities.getValues()))
{

}

vector<lpaggreg::OAggregate4> lpaggreg::OAggregation4::getAggregates() const
{
    return aggregates;
}
