#include "daggregationn.h"


lpaggreg::DAggregateN2::DAggregateN2(lpaggreg::DPart part, shared_ptr<lpaggreg::DValuesN2> values): DAggregate(part), values(values)
{
    compute();
}

void lpaggreg::DAggregateN2::compute()
{
    sum=0;
    for (int o=part.getStart(); o<=part.getEnd();o++){
        sum+=subSum(values->getMetaData().getRoot(), o);
    }
    mean=sum/part.getSize();
}

double lpaggreg::DAggregateN2::subSum(int h, int o)
{
    if (h<values->getMetaData().getLeaveSize()){
        return (*values)(h, o);
    }
    double sum_t=0;
    for (int h: (values->getMetaData().getChildren())[part.getH()]){
        sum_t+=subSum(h, o);
    }
    return sum_t;
}

double lpaggreg::DAggregateN2::getMean() const
{
    return mean;
}

double lpaggreg::DAggregateN2::getSum() const
{
    return sum;
}

lpaggreg::DAggregateN3::DAggregateN3(lpaggreg::DPart part, shared_ptr<lpaggreg::DValuesN3> values): DAggregate(part), values(values)
{
    compute();
}

void lpaggreg::DAggregateN3::compute()
{
    for (int i=0; i<values->getVsize(); i++){
        sum.push_back(0);
        mean.push_back(0);
        for (int o=part.getStart(); o<=part.getEnd();o++){
            sum[i]+=subSum(values->getMetaData().getRoot(), i, o);
        }
        mean[i]=sum[i]/part.getSize();
    }
}

double lpaggreg::DAggregateN3::subSum(int h, int i, int o)
{
    if (h<values->getMetaData().getLeaveSize()){
        return (*values)(h, i, o);
    }
    double sum_t=0;
    for (int h: (values->getMetaData().getChildren())[part.getH()]){
        sum_t+=subSum(h, i, o);
    }
    return sum_t;
}

vector<double> lpaggreg::DAggregateN3::getMean() const
{
    return mean;
}

vector<double> lpaggreg::DAggregateN3::getSum() const
{
    return sum;
}

lpaggreg::DAggregateN4::DAggregateN4(lpaggreg::DPart part, shared_ptr<lpaggreg::DValuesN4> values): DAggregate(part), values(values)
{
    compute();
}

void lpaggreg::DAggregateN4::compute()
{
    for (int i=0; i<values->getI(); i++){
        sum.push_back(vector<double>());
        mean.push_back(vector<double>());
        for (int j=0; j<values->getJ(); j++){
            sum[i].push_back(0);
            mean[i].push_back(0);
            for (int o=part.getStart(); o<=part.getEnd();o++){
                sum[i][j]+=subSum(values->getMetaData().getRoot(), i, j, o);
            }
            mean[i][j]=sum[i][j]/part.getSize();
        }
    }
}

double lpaggreg::DAggregateN4::subSum(int h, int i, int j, int o)
{
    if (h<values->getMetaData().getLeaveSize()){
        return (*values)(h, i, j, o);
    }
    double sum_t=0;
    for (int h: (values->getMetaData().getChildren())[part.getH()]){
        sum_t+=subSum(h, i, j, o);
    }
    return sum_t;
}

vector<vector<double> > lpaggreg::DAggregateN4::getMean() const
{
    return mean;
}

vector<vector<double> > lpaggreg::DAggregateN4::getSum() const
{
    return sum;
}

lpaggreg::DAggregationN2::DAggregationN2(shared_ptr<lpaggreg::DPartition> DPartition, shared_ptr<lpaggreg::DValuesN2> values):DAggregation(DPartition), values(values)
{
    for (auto it: DPartition->getParts()){
        aggregates.push_back(DAggregateN2(it, values));
    }
}

vector<lpaggreg::DAggregateN2> lpaggreg::DAggregationN2::getAggregates() const
{
    return aggregates;
}

lpaggreg::DAggregationN3::DAggregationN3(shared_ptr<lpaggreg::DPartition> DPartition, shared_ptr<lpaggreg::DValuesN3> values):DAggregation(DPartition), values(values)
{
    for (auto it: DPartition->getParts()){
        aggregates.push_back(DAggregateN3(it, values));
    }
}

vector<lpaggreg::DAggregateN3> lpaggreg::DAggregationN3::getAggregates() const
{
    return aggregates;
}

lpaggreg::DAggregationN4::DAggregationN4(shared_ptr<lpaggreg::DPartition> DPartition, shared_ptr<lpaggreg::DValuesN4> values):DAggregation(DPartition), values(values)
{
    for (auto it: DPartition->getParts()){
        aggregates.push_back(DAggregateN4(it, values));
    }
}

vector<lpaggreg::DAggregateN4> lpaggreg::DAggregationN4::getAggregates() const
{
    return aggregates;
}
