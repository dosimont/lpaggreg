#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "oqualities.h"
#include "opartitioner.h"
#include "ovaluesn.h"

using namespace std;
using namespace lpaggreg;

int main()
{
    map<float, Quality> qualities;
    qualities[0.0]=Quality(0,0);
    qualities[0.09]=Quality(0.7760246484967517, 0.06904577403845964);
    qualities[0.38]=Quality(2.718728015324853, 1.224933956506133);
    qualities[0.70]=Quality(2.932312080076537, 1.711544109698188);

    cout<<"Initializing Ordered Set (2D)"<<endl;
    vector<double> sub_ordered_set1 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_ordered_set2 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector< vector<double> > ordered_set;
    ordered_set.push_back(sub_ordered_set1);
    ordered_set.push_back(sub_ordered_set2);

    cout<<"Converting to OValuesN2"<<endl;
    shared_ptr<OValuesN2> values = shared_ptr<OValuesN2>(new OValuesN2(ordered_set));

    if (values->getOsize()!=(ordered_set[0]).size()){
        cerr<<"OVAluesN2 osize is wrong: "<<values->getOsize()<<" instead of "<<(ordered_set[0]).size()<<endl;
        return 1;
    }
    if (values->getVsize()!=ordered_set.size()){
        cerr<<"OVAluesN2 vsize is wrong: "<<values->getVsize()<<" instead of "<<ordered_set.size()<<endl;
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
    }
    cout<<"Evaluating Best Partitions"<<endl;
    opartitioner.computeBestPartitions(0.001);
    if (opartitioner.getPList().size()!=qualities.size()){
        cerr<<"Partition number is wrong: "<<opartitioner.getPList().size()<<" instead of "<<qualities.size()<<endl;
        return 4;
    }
    return 0;
}
