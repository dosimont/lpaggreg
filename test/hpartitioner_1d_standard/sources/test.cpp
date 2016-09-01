#include <iostream>
#include <vector>
#include <memory>
#include "hqualities.h"
#include "hpartitioner.h"
#include "hvaluesn.h"

using namespace std;
using namespace lpaggreg;

#define P 0.5

int main()
{
    cout<<"Initializing Hierarchical Set (1D)"<<endl;
    vector<double> hierarchical_set = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<int> parents = {5, 5, 6, 6, 6, 7, 7, -1};
    cout<<"Converting to HValuesN1"<<endl;
    shared_ptr<HValuesN1> values = shared_ptr<HValuesN1>(new HValuesN1(hierarchical_set), parents);
    cout<<"Instantiating HQualities"<<endl;
    HQualities hqualities = HQualities(values);
    cout<<"Computing qualities"<<endl;
    hqualities.computeQualities();
    cout<<"Normalizing qualities"<<endl;
    hqualities.normalize();
    cout<<"Instantiating OPartitioner"<<endl;
    HPartitioner hpartitioner = HPartitioner(oqualities, values->getMetaData());
    float p=P;
    cout<<"Computing Best Partition for "<<p<<endl;
    hpartitioner.computeBestPartition(p);
    cout<<"Computing Best Partitions"<<endl;
    hpartitioner.computeBestPartitions(0.001);
    return 0;
}
