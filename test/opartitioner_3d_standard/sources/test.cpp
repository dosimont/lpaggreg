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
    cout<<"Initializing Ordered Set (3D)"<<endl;
    vector<double> sub_sub_ordered_set1_1 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_ordered_set1_2 = {5.0/100.0, 20.0/100.0, 20.0/100.0, 25.0/100.0, 30.0/100.0};
    vector<double> sub_sub_ordered_set2_1 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_ordered_set2_2 = {5.0/100.0, 20.0/100.0, 20.0/100.0, 25.0/100.0, 30.0/100.0};
    vector< vector<double> > sub_ordered_set1;
    vector< vector<double> > sub_ordered_set2;
    sub_ordered_set1.push_back(sub_sub_ordered_set1_1);
    sub_ordered_set1.push_back(sub_sub_ordered_set1_2);
    sub_ordered_set2.push_back(sub_sub_ordered_set2_1);
    sub_ordered_set2.push_back(sub_sub_ordered_set2_2);
    vector< vector <vector<double> > > ordered_set;
    ordered_set.push_back(sub_ordered_set1);
    ordered_set.push_back(sub_ordered_set2);
    cout<<"Converting to OValuesN3"<<endl;
    shared_ptr<OValuesN3> values = shared_ptr<OValuesN3>(new OValuesN3(ordered_set));
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
