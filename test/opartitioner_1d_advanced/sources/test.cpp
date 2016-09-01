#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "oqualities.h"
#include "opartitioner.h"
#include "ovaluesn.h"
#include "oaggregationn.h"

using namespace std;
using namespace lpaggreg;

int main()
{
    map<float, Quality> qualities;
    qualities[0.0]=Quality(0,0);
    qualities[0.09]=Quality(0.388012324248376, 0.0345228870192298);
    qualities[0.38]=Quality(1.35936400766243, 0.612466978253066);
    qualities[0.70]=Quality(1.46615604003827, 0.855772054849094);

    cout<<"Initializing Ordered Set (1D)"<<endl;
    vector<double> ordered_set = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};

    cout<<"Converting to OValuesN1"<<endl;
    shared_ptr<OValuesN1> values = shared_ptr<OValuesN1>(new OValuesN1(ordered_set));  
    if (values->getOsize()!=ordered_set.size()){
        cerr<<"OVAluesN1 osize is wrong: "<<values->getOsize()<<" instead of "<<ordered_set.size()<<endl;
        return 1;
    }
    if (values->getVsize()!=1){
        cerr<<"OVAluesN1 vsize is wrong: "<<values->getVsize()<<" instead of "<<1<<endl;
        return 1;
    }

    cout<<"Instantiating OQualities"<<endl;
    OQualities oqualities = OQualities(values);

    cout<<"Computing qualities"<<endl;
    oqualities.computeQualities();
    int size=oqualities.getQualities()->getSize();
    if (size!=values->getOsize()){
        cerr<<"Qualities size is wrong: "<<size<<" instead of "<<values->getOsize()<<endl;
        return 2;
    }

    cout<<"Instantiating OPartitioner"<<endl;
    OPartitioner opartitioner = OPartitioner(oqualities);

    cout<<"Evaluating Best Partition for several values of p"<<endl;
    for (auto it: qualities){
        shared_ptr<lpaggreg::OPartition> opartition=opartitioner.computeBestPartition(it.first);
        if (*(opartition->getQuality())!=qualities[it.first]){
            cerr<<"Invalid partition: p="<<it.first<<", qualities="<<*(opartition->getQuality())<<endl;
            return 3;
        }
        OAggregationN1 oaggregation=OAggregationN1(opartition, values);
        for (OAggregateN1 it: oaggregation.getAggregates()){
            cout<<it.getPart().getStart()<<"-"<<it.getPart().getEnd()<<": "<<it.getSum()<<", "<<it.getMean()<<endl;
        }

    }
    cout<<"Evaluating Best Partitions"<<endl;
    opartitioner.computeBestPartitions(0.001);
    if (opartitioner.getPList().size()!=qualities.size()){
        cerr<<"Partition number is wrong: "<<opartitioner.getPList().size()<<" instead of "<<qualities.size()<<endl;
        return 4;
    }
    return 0;
}
