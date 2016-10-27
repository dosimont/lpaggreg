#include <iostream>
#include <vector>
#include <memory>
#include "dqualities.h"
#include "dpartitioner.h"
#include "dvaluesn.h"

using namespace std;
using namespace lpaggreg;

#define P 0.5

int main()
{
    cout<<"Initializing D Set (2D)"<<endl;
    vector<double> hierarchical_subset1 = {50.0/355.0, 100.0/355.0, 0.1, 200.0/355.0, 5.0/355.0};
    vector<double> hierarchical_subset2 = {50.0/355.0, 100.0/355.0, 0.1, 200.0/355.0, 5.0/355.0};
    vector< vector<double> > hierarchical_set;
    hierarchical_set.push_back(hierarchical_subset1);
    hierarchical_set.push_back(hierarchical_subset2);
    vector<int> parents = {2,2,-1};
    cout<<"Converting to DValuesN2"<<endl;
    shared_ptr<DValuesN2> values = shared_ptr<DValuesN2>(new DValuesN2(hierarchical_set, parents));
    //
    int osize=values->getOsize();
    int vsize=values->getVsize();
    int leaves=values->getMetaData().getLeaveSize();
    int hsize=values->getMetaData().getHsize();
    cout<<osize<<" "<<vsize<<" "<<leaves<<" "<<hsize<<endl;
    //
    cout<<"Instantiating DQualities"<<endl;
    DQualities dqualities = DQualities(values);
    cout<<"Computing qualities"<<endl;
    dqualities.computeQualities();
    cout<<dqualities.size()<<endl;
    cout<<dqualities.getQualities()->size()<<endl;
    cout<<(dqualities.getQualities()->operator [](0))->getSize()<<endl;
    cout<<(dqualities.getQualities()->operator [](0))->getElements()<<endl;
    cout<<"Normalizing qualities"<<endl;
    //dqualities.normalize();
    cout<<"Instantiating DPartitioner"<<endl;
    DPartitioner dpartitioner = DPartitioner(dqualities);
    float p=0;
    cout<<"Computing Best Partition for "<<p<<endl;
    shared_ptr<DPartition> partition=dpartitioner.computeBestPartition(p);
    p=1;
    cout<<"Computing Best Partition for "<<p<<endl;
    partition=dpartitioner.computeBestPartition(p);
    p=P;
    cout<<"Computing Best Partition for "<<p<<endl;
    partition=dpartitioner.computeBestPartition(p);
    //cout<<"Quality:"<<partition->getQuality()->getGain()<<endl;
    cout<<"Computing Best Partitions"<<endl;
    dpartitioner.computeBestPartitions(0.001);
    vector<float> vec=dpartitioner.getPList();
    for (auto i = vec.begin(); i != vec.end(); ++i){
        std::cout << *i << ' '<<endl;
    }
    return 0;
}
