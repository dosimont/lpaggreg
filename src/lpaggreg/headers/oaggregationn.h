#ifndef OAGGREGATIONN_H
#define OAGGREGATIONN_H

#include "oaggregation.h"

#include <memory>
#include "ovaluesn.h"
#include "opartition.h"
#include "oqualities.h"

using namespace std;

namespace lpaggreg{

    class OAggregate1: public OAggregate
    {
    public:
        OAggregate1(OPart part, shared_ptr<OValuesN1> values);
        double getSum() const;

        double getMean() const;

    private:
        void compute();
        shared_ptr<OValuesN1> values;
        double sum;
        double mean;
    };

    class OAggregate2: public OAggregate
    {
    public:
        OAggregate2(OPart part, shared_ptr<OValuesN2> values);
        vector<double> getSum() const;

        vector<double> getMean() const;

    private:
        void compute();
        shared_ptr<OValuesN2> values;
        vector<double> sum;
        vector<double> mean;
    };

    class OAggregate3: public OAggregate
    {
    public:
        OAggregate3(OPart part, shared_ptr<OValuesN3> values);
        vector<vector<double> > getSum() const;

        vector<vector<double> > getMean() const;

    private:
        void compute();
        shared_ptr<OValuesN3> values;
        vector<vector<double> > sum;
        vector<vector<double> > mean;
    };

    class OAggregate4: public OAggregate
    {
    public:
        OAggregate4(OPart part, shared_ptr<OValuesN4> values);
        vector<vector<vector<double> > > getSum() const;

        vector<vector<vector<double> > > getMean() const;

    private:
        void compute();
        shared_ptr<OValuesN4> values;
        vector<vector<vector<double> > > sum;
        vector<vector<vector<double> > > mean;
    };

    class OAggregation1: public OAggregation
    {
    public:
        OAggregation1(shared_ptr<OPartition> opartition, shared_ptr<OValuesN1> values);
        OAggregation1(shared_ptr<OPartition> opartition, OQualities qualities);
        vector<OAggregate1> getAggregates() const;

    private:
        shared_ptr<OValuesN1> values;
        vector<OAggregate1> aggregates;

    };

    class OAggregation2: public OAggregation
    {
    public:
        OAggregation2(shared_ptr<OPartition> opartition, shared_ptr<OValuesN2> values);
        OAggregation2(shared_ptr<OPartition> opartition, OQualities qualities);
        vector<OAggregate2> getAggregates() const;

    private:
        shared_ptr<OValuesN2> values;
        vector<OAggregate2> aggregates;
    };

    class OAggregation3: public OAggregation
    {
    public:
        OAggregation3(shared_ptr<OPartition> opartition, shared_ptr<OValuesN3> values);
        OAggregation3(shared_ptr<OPartition> opartition, OQualities qualities);
        vector<OAggregate3> getAggregates() const;

    private:
        shared_ptr<OValuesN3> values;
        vector<OAggregate3> aggregates;
    };

    class OAggregation4: public OAggregation
    {
    public:
        OAggregation4(shared_ptr<OPartition> opartition, shared_ptr<OValuesN4> values);
        OAggregation4(shared_ptr<OPartition> opartition, OQualities qualities);
        vector<OAggregate4> getAggregates() const;

    private:
        shared_ptr<OValuesN4> values;
        vector<OAggregate4> aggregates;
    };
}


#endif // OAGGREGATIONN_H
