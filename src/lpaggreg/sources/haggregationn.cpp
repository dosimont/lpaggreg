#include "haggregationn.h"

lpaggreg::HAggregateN1::HAggregateN1(lpaggreg::HPart part, shared_ptr<lpaggreg::HValuesN1> values): HAggregate(part), values(values)
{
    compute();
}

void lpaggreg::HAggregateN1::compute()
{
    sum=0;
    sum=subSum(values->getMetaData().getRoot());
    mean=sum/part.getSize();
}

double lpaggreg::HAggregateN1::subSum(int h)
{
    if (h<values->getMetaData().getLeaveSize()){
        return (*values)(h);
    }
    double sum_t=0;
    for (int h: (values->getMetaData().getChildren())[part.getH()]){
        sum_t+=subSum(h);
    }
    return sum_t;
}

double lpaggreg::HAggregateN1::getMean() const
{
    return mean;
}

double lpaggreg::HAggregateN1::getSum() const
{
    return sum;
}

lpaggreg::HAggregateN2::HAggregateN2(lpaggreg::HPart part, shared_ptr<lpaggreg::HValuesN2> values): HAggregate(part), values(values)
{
    compute();
}

void lpaggreg::HAggregateN2::compute()
{
    for (int i=0; i<values->getVsize(); i++){
        sum.push_back(subSum(values->getMetaData().getRoot(), i));
        mean.push_back(sum[i]/part.getSize());
    }
}

double lpaggreg::HAggregateN2::subSum(int h, int i)
{
    if (h<values->getMetaData().getLeaveSize()){
        return (*values)(h, i);
    }
    double sum_t=0;
    for (int h: (values->getMetaData().getChildren())[part.getH()]){
        sum_t+=subSum(h, i);
    }
    return sum_t;
}

vector<double> lpaggreg::HAggregateN2::getMean() const
{
    return mean;
}

vector<double> lpaggreg::HAggregateN2::getSum() const
{
    return sum;
}

lpaggreg::HAggregateN3::HAggregateN3(lpaggreg::HPart part, shared_ptr<lpaggreg::HValuesN3> values): HAggregate(part), values(values)
{
    compute();
}

void lpaggreg::HAggregateN3::compute()
{
    for (int i=0; i<values->getI(); i++){
        sum.push_back(vector<double>());
        mean.push_back(vector<double>());
        for (int j=0; j<values->getJ(); j++){
            sum[i].push_back(subSum(values->getMetaData().getRoot(), i, j));
            mean[i].push_back(sum[i][j]/part.getSize());
        }
    }
}

double lpaggreg::HAggregateN3::subSum(int h, int i, int j)
{
    if (h<values->getMetaData().getLeaveSize()){
        return (*values)(h, i, j);
    }
    double sum_t=0;
    for (int h: (values->getMetaData().getChildren())[part.getH()]){
        sum_t+=subSum(h, i, j);
    }
    return sum_t;
}

vector<vector<double> > lpaggreg::HAggregateN3::getMean() const
{
    return mean;
}

vector<vector<double> > lpaggreg::HAggregateN3::getSum() const
{
    return sum;
}

lpaggreg::HAggregateN4::HAggregateN4(lpaggreg::HPart part, shared_ptr<lpaggreg::HValuesN4> values): HAggregate(part), values(values)
{
    compute();
}

void lpaggreg::HAggregateN4::compute()
{
    for (int i=0; i<values->getI(); i++){
        sum.push_back(vector<vector<double> >());
        mean.push_back(vector<vector<double> >());
        for (int j=0; j<values->getJ(); j++){
            sum[i].push_back(vector<double>());
            mean[i].push_back(vector<double>());
            for (int k=0; k<values->getK(); k++){
                sum[i][j].push_back(subSum(values->getMetaData().getRoot(), i, j, k));
                mean[i][j].push_back(sum[i][j][k]/part.getSize());
            }
        }
    }
}

double lpaggreg::HAggregateN4::subSum(int h, int i, int j, int k)
{
    if (h<values->getMetaData().getLeaveSize()){
        return (*values)(h, i, j, k);
    }
    double sum_t=0;
    for (int h: (values->getMetaData().getChildren())[part.getH()]){
        sum_t+=subSum(h, i, j, k);
    }
    return sum_t;
}

vector<vector<vector<double> > > lpaggreg::HAggregateN4::getMean() const
{
    return mean;
}

vector<vector<vector<double> > > lpaggreg::HAggregateN4::getSum() const
{
    return sum;
}

lpaggreg::HAggregationN1::HAggregationN1(shared_ptr<lpaggreg::HPartition> hpartition, shared_ptr<lpaggreg::HValuesN1> values):HAggregation(hpartition), values(values)
{
    for (auto it: hpartition->getParts()){
        aggregates.push_back(HAggregateN1(it, values));
    }
}

vector<lpaggreg::HAggregateN1> lpaggreg::HAggregationN1::getAggregates() const
{
    return aggregates;
}

lpaggreg::HAggregationN2::HAggregationN2(shared_ptr<lpaggreg::HPartition> hpartition, shared_ptr<lpaggreg::HValuesN2> values):HAggregation(hpartition), values(values)
{
    for (auto it: hpartition->getParts()){
        aggregates.push_back(HAggregateN2(it, values));
    }
}

vector<lpaggreg::HAggregateN2> lpaggreg::HAggregationN2::getAggregates() const
{
    return aggregates;
}

lpaggreg::HAggregationN3::HAggregationN3(shared_ptr<lpaggreg::HPartition> hpartition, shared_ptr<lpaggreg::HValuesN3> values):HAggregation(hpartition), values(values)
{
    for (auto it: hpartition->getParts()){
        aggregates.push_back(HAggregateN3(it, values));
    }
}

vector<lpaggreg::HAggregateN3> lpaggreg::HAggregationN3::getAggregates() const
{
    return aggregates;
}

lpaggreg::HAggregationN4::HAggregationN4(shared_ptr<lpaggreg::HPartition> hpartition, shared_ptr<lpaggreg::HValuesN4> values):HAggregation(hpartition), values(values)
{
    for (auto it: hpartition->getParts()){
        aggregates.push_back(HAggregateN4(it, values));
    }
}

vector<lpaggreg::HAggregateN4> lpaggreg::HAggregationN4::getAggregates() const
{
    return aggregates;
}
