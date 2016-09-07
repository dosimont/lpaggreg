#ifndef DAGGREGATIONN_H
#define DAGGREGATIONN_H

#include "daggregation.h"
#include <memory>
#include "dvaluesn.h"
#include "dpartition.h"
#include "dqualities.h"

using namespace std;

namespace lpaggreg{

    class DAggregateN2: public DAggregate
    {
    public:
        DAggregateN2(DPart part, shared_ptr<DValuesN2> values);
        double getSum() const;
        double getMean() const;

    private:
        void compute();
        double subSum(int h, int o);
        shared_ptr<DValuesN2> values;
        double sum;
        double mean;
    };

    class DAggregateN3: public DAggregate
    {
    public:
        DAggregateN3(DPart part, shared_ptr<DValuesN3> values);
        vector<double> getSum() const;
        vector<double> getMean() const;

    private:
        void compute();
        double subSum(int h, int i, int o);
        shared_ptr<DValuesN3> values;
        vector<double> sum;
        vector<double> mean;
    };

    class DAggregateN4: public DAggregate
    {
    public:
        DAggregateN4(DPart part, shared_ptr<DValuesN4> values);
        vector<vector<double> > getSum() const;
        vector<vector<double> > getMean() const;

    private:
        void compute();
        double subSum(int h, int i, int j, int o);
        shared_ptr<DValuesN4> values;
        vector<vector<double> > sum;
        vector<vector<double> > mean;
    };

    class DAggregationN2: public DAggregation
    {
    public:
        DAggregationN2(shared_ptr<DPartition> DPartition, shared_ptr<DValuesN2> values);
        vector<DAggregateN2> getAggregates() const;

    private:
        shared_ptr<DValuesN2> values;
        vector<DAggregateN2> aggregates;
    };

    class DAggregationN3: public DAggregation
    {
    public:
        DAggregationN3(shared_ptr<DPartition> DPartition, shared_ptr<DValuesN3> values);
        vector<DAggregateN3> getAggregates() const;

    private:
        shared_ptr<DValuesN3> values;
        vector<DAggregateN3> aggregates;
    };

    class DAggregationN4: public DAggregation
    {
    public:
        DAggregationN4(shared_ptr<DPartition> DPartition, shared_ptr<DValuesN4> values);
        vector<DAggregateN4> getAggregates() const;

    private:
        shared_ptr<DValuesN4> values;
        vector<DAggregateN4> aggregates;
    };
}

#endif // DAGGREGATIONN_H
