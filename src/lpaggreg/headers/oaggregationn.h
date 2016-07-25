#ifndef OAGGREGATIONN_H
#define OAGGREGATIONN_H

#include "oaggregation.h"

#include <memory>
#include <ovaluesn.h>
#include <opartition.h>

using namespace std;

namespace lpaggreg{

    class OAggregate1: public OAggregate
    {
    public:
        OAggregate1(OPart part, shared_ptr<OValuesN1> values);
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
    private:
        shared_ptr<OValuesN1> values;

    };

    class OAggregation2: public OAggregation
    {
    public:
        OAggregation2(shared_ptr<OPartition> opartition, shared_ptr<OValuesN2> values);
    private:
        shared_ptr<OValuesN2> values;
    };

    class OAggregation3: public OAggregation
    {
    public:
        OAggregation3(shared_ptr<OPartition> opartition, shared_ptr<OValuesN3> values);
    private:
        shared_ptr<OValuesN3> values;
    };

    class OAggregation4: public OAggregation
    {
    public:
        OAggregation4(shared_ptr<OPartition> opartition, shared_ptr<OValuesN4> values);
    private:
        shared_ptr<OValuesN4> values;
    };
}


#endif // OAGGREGATIONN_H
