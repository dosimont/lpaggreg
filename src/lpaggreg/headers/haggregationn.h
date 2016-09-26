#ifndef HAGGREGATIONN_H
#define HAGGREGATIONN_H

#include "haggregation.h"
#include <memory>
#include "hvaluesn.h"
#include "hpartition.h"
#include "hqualities.h"

using namespace std;

namespace lpaggreg{

    class HAggregateN1: public HAggregate
    {
    public:
        HAggregateN1(HPart part, shared_ptr<HValuesN1> values);
        double getSum() const;
        double getMean() const;

    private:
        void compute();
        double subSum(int h);
        shared_ptr<HValuesN1> values;
        double sum;
        double mean;
    };

    class HAggregateN2: public HAggregate
    {
    public:
        HAggregateN2(HPart part, shared_ptr<HValuesN2> values);
        vector<double> getSum() const;
        vector<double> getMean() const;

    private:
        void compute();
        double subSum(int h, int i);
        shared_ptr<HValuesN2> values;
        vector<double> sum;
        vector<double> mean;
    };

    class HAggregateN3: public HAggregate
    {
    public:
        HAggregateN3(HPart part, shared_ptr<HValuesN3> values);
        vector<vector<double> > getSum() const;
        vector<vector<double> > getMean() const;

    private:
        void compute();
        double subSum(int h, int i, int j);
        shared_ptr<HValuesN3> values;
        vector<vector<double> > sum;
        vector<vector<double> > mean;
    };

    class HAggregateN4: public HAggregate
    {
    public:
        HAggregateN4(HPart part, shared_ptr<HValuesN4> values);
        vector<vector<vector<double> > > getSum() const;
        vector<vector<vector<double> > > getMean() const;

    private:
        void compute();
        double subSum(int h, int i, int j, int k);
        shared_ptr<HValuesN4> values;
        vector<vector<vector<double> > > sum;
        vector<vector<vector<double> > > mean;
    };

    class HAggregationN1: public HAggregation
    {
    public:
        HAggregationN1(shared_ptr<HPartition> hpartition, shared_ptr<HValuesN1> values);
        vector<HAggregateN1> getAggregates() const;

    private:
        shared_ptr<HValuesN1> values;
        vector<HAggregateN1> aggregates;

    };

    class HAggregationN2: public HAggregation
    {
    public:
        HAggregationN2(shared_ptr<HPartition> hpartition, shared_ptr<HValuesN2> values);
        vector<HAggregateN2> getAggregates() const;

    private:
        shared_ptr<HValuesN2> values;
        vector<HAggregateN2> aggregates;
    };

    class HAggregationN3: public HAggregation
    {
    public:
        HAggregationN3(shared_ptr<HPartition> hpartition, shared_ptr<HValuesN3> values);
        vector<HAggregateN3> getAggregates() const;

    private:
        shared_ptr<HValuesN3> values;
        vector<HAggregateN3> aggregates;
    };

    class HAggregationN4: public HAggregation
    {
    public:
        HAggregationN4(shared_ptr<HPartition> hpartition, shared_ptr<HValuesN4> values);
        vector<HAggregateN4> getAggregates() const;

    private:
        shared_ptr<HValuesN4> values;
        vector<HAggregateN4> aggregates;
    };
}



#endif // HAGGREGATIONN_H
