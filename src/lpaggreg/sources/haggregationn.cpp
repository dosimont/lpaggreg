#include "haggregationn.h"

lpaggreg::HAggregateN1::HAggregateN1(lpaggreg::HPart part, shared_ptr<lpaggreg::HValuesN1> values): HAggregate(part), values(values)
{
    compute();
}

void lpaggreg::HAggregateN1::compute()
{
    sum=0;
    for (int h: (values->getMetaData().getLeaves())[part.getH()]){
        sum+=(*values)(h);
    }
    mean=sum/part.getSize();
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
        sum[i]=0;
        for (int h: (values->getMetaData().getLeaves())[part.getH()]){
            sum[i]+=(*values)(h, i);
        }
        mean[i]=sum[i]/part.getSize();
    }
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
        for (int j=0; j<values->getJ(); j++){
            sum[i][j]=0;
        for (int h: (values->getMetaData().getLeaves())[part.getH()]){
                sum[i][j]+=(*values)(h, i, j);
            }
            mean[i][j]=sum[i][j]/part.getSize();
        }
    }
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
        for (int j=0; j<values->getJ(); j++){
            for (int k=0; k<values->getK(); k++){
                sum[i][j][k]=0;
                for (int h: (values->getMetaData().getLeaves())[part.getH()]){
                    sum[i][j][k]+=(*values)(h, i, j, k);
                }
                mean[i][j][k]=sum[i][j][k]/part.getSize();
            }
        }
    }
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
