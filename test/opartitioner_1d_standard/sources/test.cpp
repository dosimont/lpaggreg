#include <iostream>
#include <vector>
#include <memory>
#include "oqualities.h"
#include "opartitioner.h"
#include "ovaluesn.h"

using namespace std;
using namespace lpaggreg;

#define P 0.5

int main()
{
    cout<<"Initializing Ordered Set (1D)"<<endl;
    vector<double> ordered_set = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    cout<<"Converting to OValuesN1"<<endl;
    shared_ptr<OValuesN1> values = shared_ptr<OValuesN1>(new OValuesN1(ordered_set));
    cout<<"Instantiating OQualities"<<endl;
    OQualities oqualities = OQualities(values);
    cout<<"Computing qualities"<<endl;
    oqualities.computeQualities();
    cout<<"Normalizing qualities"<<endl;
    oqualities.normalize();
    cout<<"Instantiating OPartitioner"<<endl;
    OPartitioner opartitioner = OPartitioner(oqualities);
    float p=P;
    cout<<"Computing Best Partition for "<<p<<endl;
    opartitioner.computeBestPartition(p);
    cout<<"Computing Best Partitions"<<endl;
    opartitioner.computeBestPartitions(0.001);
    return 0;
}
