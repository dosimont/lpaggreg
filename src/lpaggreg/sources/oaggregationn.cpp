#include "oaggregationn.h"

lpaggreg::OAggregateN1::OAggregateN1(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN1> values): OAggregate(part), values(values)
{
    compute();
}

void lpaggreg::OAggregateN1::compute()
{
    sum=0;
    for (int o=part.getStart(); o<=part.getEnd();o++){
        sum+=(*values)(o);
    }
    mean=sum/part.getSize();
}

double lpaggreg::OAggregateN1::getMean() const
{
    return mean;
}

double lpaggreg::OAggregateN1::getSum() const
{
    return sum;
}

lpaggreg::OAggregateN2::OAggregateN2(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN2> values): OAggregate(part), values(values)
{
    compute();
}

void lpaggreg::OAggregateN2::compute()
{
    for (int i=0; i<values->getVsize(); i++){
        sum.push_back(0);
        mean.push_back(0);
        for (int o=part.getStart(); o<=part.getEnd();o++){
            sum[i]+=(*values)(i, o);
        }
        mean[i]=sum[i]/part.getSize();
    }
}

vector<double> lpaggreg::OAggregateN2::getMean() const
{
    return mean;
}

vector<double> lpaggreg::OAggregateN2::getSum() const
{
    return sum;
}

lpaggreg::OAggregateN3::OAggregateN3(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN3> values): OAggregate(part), values(values)
{
    compute();
}

void lpaggreg::OAggregateN3::compute()
{
    for (int i=0; i<values->getI(); i++){
        sum.push_back(vector<double>(0));
        mean.push_back(vector<double>(0));
        for (int j=0; j<values->getJ(); j++){
            sum[i].push_back(0);
            mean[i].push_back(0);
            for (int o=part.getStart(); o<=part.getEnd();o++){
                sum[i][j]+=(*values)(i, j, o);
            }
            mean[i][j]=sum[i][j]/part.getSize();
        }
    }
}

vector<vector<double> > lpaggreg::OAggregateN3::getMean() const
{
    return mean;
}

vector<vector<double> > lpaggreg::OAggregateN3::getSum() const
{
    return sum;
}

lpaggreg::OAggregateN4::OAggregateN4(lpaggreg::OPart part, shared_ptr<lpaggreg::OValuesN4> values): OAggregate(part), values(values)
{
    compute();
}

void lpaggreg::OAggregateN4::compute()
{
    for (int i=0; i<values->getI(); i++){
        sum.push_back(vector<vector<double> >(0));
        mean.push_back(vector<vector<double> >(0));
        for (int j=0; j<values->getJ(); j++){
            sum[i].push_back(vector<double>(0));
            mean[i].push_back(vector<double>(0));
            for (int k=0; k<values->getK(); k++){
                sum[i][j].push_back(0);
                mean[i][j].push_back(0);
                for (int o=part.getStart(); o<=part.getEnd();o++){
                    sum[i][j][k]+=(*values)(i, j, k, o);
                }
                mean[i][j][k]=sum[i][j][k]/part.getSize();
            }
        }
    }
}

vector<vector<vector<double> > > lpaggreg::OAggregateN4::getMean() const
{
    return mean;
}

vector<vector<vector<double> > > lpaggreg::OAggregateN4::getSum() const
{
    return sum;
}

lpaggreg::OAggregationN1::OAggregationN1(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN1> values):OAggregation(opartition), values(values)
{
    for (auto it: opartition->getParts()){
        aggregates.push_back(OAggregateN1(it, values));
    }
}

vector<lpaggreg::OAggregateN1> lpaggreg::OAggregationN1::getAggregates() const
{
    return aggregates;
}

lpaggreg::OAggregationN2::OAggregationN2(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN2> values):OAggregation(opartition), values(values)
{
    for (auto it: opartition->getParts()){
        aggregates.push_back(OAggregateN2(it, values));
    }
}

vector<lpaggreg::OAggregateN2> lpaggreg::OAggregationN2::getAggregates() const
{
    return aggregates;
}

lpaggreg::OAggregationN3::OAggregationN3(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN3> values):OAggregation(opartition), values(values)
{
    for (auto it: opartition->getParts()){
        aggregates.push_back(OAggregateN3(it, values));
    }
}

vector<lpaggreg::OAggregateN3> lpaggreg::OAggregationN3::getAggregates() const
{
    return aggregates;
}

lpaggreg::OAggregationN4::OAggregationN4(shared_ptr<lpaggreg::OPartition> opartition, shared_ptr<lpaggreg::OValuesN4> values):OAggregation(opartition), values(values)
{
    for (auto it: opartition->getParts()){
        aggregates.push_back(OAggregateN4(it, values));
    }
}

vector<lpaggreg::OAggregateN4> lpaggreg::OAggregationN4::getAggregates() const
{
    return aggregates;
}
