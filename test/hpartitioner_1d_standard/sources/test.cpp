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
    shared_ptr<HValuesN1> values = shared_ptr<HValuesN1>(new HValuesN1(hierarchical_set, parents));
    cout<<"Instantiating HQualities"<<endl;
    HQualities hqualities = HQualities(values);
    cout<<"Computing qualities"<<endl;
    hqualities.computeQualities();
    cout<<"Normalizing qualities"<<endl;
    hqualities.normalize();
    cout<<"Instantiating HPartitioner"<<endl;
    HPartitioner hpartitioner = HPartitioner(hqualities);
    float p=hpartitioner.getP(P_OPT);
    cout<<"Computing Best Partition for "<<p<<endl;
    shared_ptr<HPartition> partition=hpartitioner.computeBestPartition(p);
    //cout<<"Quality:"<<partition->getQuality()->getGain()<<endl;
    cout<<"Computing Best Partitions"<<endl;
    hpartitioner.computeBestPartitions(0.001);
    vector<float> vec=hpartitioner.getPList();
    for (auto i = vec.begin(); i != vec.end(); ++i){
        std::cout << *i << ' '<<endl;
    }
    return 0;
}
