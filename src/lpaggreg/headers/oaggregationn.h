#ifndef OAGGREGATIONN_H
#define OAGGREGATIONN_H

#include "oaggregation.h"
#include <memory>
#include "ovaluesn.h"
#include "opartition.h"
#include "oqualities.h"

using namespace std;

namespace lpaggreg{

    class OAggregateN1: public OAggregate
    {
    public:
        OAggregateN1(OPart part, shared_ptr<OValuesN1> values);
        double getSum() const;
        double getMean() const;

    private:
        void compute();
        shared_ptr<OValuesN1> values;
        double sum;
        double mean;
    };

    class OAggregateN2: public OAggregate
    {
    public:
        OAggregateN2(OPart part, shared_ptr<OValuesN2> values);
        vector<double> getSum() const;

        vector<double> getMean() const;

    private:
        void compute();
        shared_ptr<OValuesN2> values;
        vector<double> sum;
        vector<double> mean;
    };

    class OAggregateN3: public OAggregate
    {
    public:
        OAggregateN3(OPart part, shared_ptr<OValuesN3> values);
        vector<vector<double> > getSum() const;

        vector<vector<double> > getMean() const;

    private:
        void compute();
        shared_ptr<OValuesN3> values;
        vector<vector<double> > sum;
        vector<vector<double> > mean;
    };

    class OAggregateN4: public OAggregate
    {
    public:
        OAggregateN4(OPart part, shared_ptr<OValuesN4> values);
        vector<vector<vector<double> > > getSum() const;

        vector<vector<vector<double> > > getMean() const;

    private:
        void compute();
        shared_ptr<OValuesN4> values;
        vector<vector<vector<double> > > sum;
        vector<vector<vector<double> > > mean;
    };

    class OAggregationN1: public OAggregation
    {
    public:
        OAggregationN1(shared_ptr<OPartition> opartition, shared_ptr<OValuesN1> values);
        vector<OAggregateN1> getAggregates() const;

    private:
        shared_ptr<OValuesN1> values;
        vector<OAggregateN1> aggregates;

    };

    class OAggregationN2: public OAggregation
    {
    public:
        OAggregationN2(shared_ptr<OPartition> opartition, shared_ptr<OValuesN2> values);
        vector<OAggregateN2> getAggregates() const;

    private:
        shared_ptr<OValuesN2> values;
        vector<OAggregateN2> aggregates;
    };

    class OAggregationN3: public OAggregation
    {
    public:
        OAggregationN3(shared_ptr<OPartition> opartition, shared_ptr<OValuesN3> values);
        vector<OAggregateN3> getAggregates() const;

    private:
        shared_ptr<OValuesN3> values;
        vector<OAggregateN3> aggregates;
    };

    class OAggregationN4: public OAggregation
    {
    public:
        OAggregationN4(shared_ptr<OPartition> opartition, shared_ptr<OValuesN4> values);
        vector<OAggregateN4> getAggregates() const;

    private:
        shared_ptr<OValuesN4> values;
        vector<OAggregateN4> aggregates;
    };
}


#endif // OAGGREGATIONN_H
