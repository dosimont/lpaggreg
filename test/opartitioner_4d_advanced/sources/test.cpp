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
    qualities[0.09]=Quality(3.104098593987007, 0.2761830961538386);
    qualities[0.38]=Quality(10.87491206129941, 4.899735826024531);
    qualities[0.70]=Quality(11.72924832030615, 6.846176438792751);

    cout<<"Initializing Ordered Set (4D)"<<endl;
    vector<double> sub_sub_sub_ordered_set1_1_1 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_sub_ordered_set1_1_2 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_sub_ordered_set1_2_1 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_sub_ordered_set1_2_2 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_sub_ordered_set2_1_1 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_sub_ordered_set2_1_2 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_sub_ordered_set2_2_1 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector<double> sub_sub_sub_ordered_set2_2_2 = {50.0/355.0, 100.0/355.0, 0.0, 200.0/355.0, 5.0/355.0};
    vector< vector<double> > sub_sub_ordered_set1_1;
    vector< vector<double> > sub_sub_ordered_set1_2;
    vector< vector<double> > sub_sub_ordered_set2_1;
    vector< vector<double> > sub_sub_ordered_set2_2;
    sub_sub_ordered_set1_1.push_back(sub_sub_sub_ordered_set1_1_1);
    sub_sub_ordered_set1_1.push_back(sub_sub_sub_ordered_set1_1_2);
    sub_sub_ordered_set1_2.push_back(sub_sub_sub_ordered_set1_2_1);
    sub_sub_ordered_set1_2.push_back(sub_sub_sub_ordered_set1_2_2);
    sub_sub_ordered_set2_1.push_back(sub_sub_sub_ordered_set2_1_1);
    sub_sub_ordered_set2_1.push_back(sub_sub_sub_ordered_set2_1_2);
    sub_sub_ordered_set2_2.push_back(sub_sub_sub_ordered_set2_2_1);
    sub_sub_ordered_set2_2.push_back(sub_sub_sub_ordered_set2_2_2);
    vector< vector< vector<double> > > sub_ordered_set1;
    vector< vector< vector<double> > > sub_ordered_set2;
    sub_ordered_set1.push_back(sub_sub_ordered_set1_1);
    sub_ordered_set1.push_back(sub_sub_ordered_set1_2);
    sub_ordered_set2.push_back(sub_sub_ordered_set2_1);
    sub_ordered_set2.push_back(sub_sub_ordered_set2_2);
    vector< vector < vector< vector<double> > > > ordered_set;
    ordered_set.push_back(sub_ordered_set1);
    ordered_set.push_back(sub_ordered_set2);

    cout<<"Converting to OValuesN4"<<endl;
    shared_ptr<OValuesN4> values = shared_ptr<OValuesN4>(new OValuesN4(ordered_set));

    if (values->getOsize()!=(ordered_set[0][0][0]).size()){
        cerr<<"OVAluesN4 osize is wrong: "<<values->getOsize()<<" instead of "<<(ordered_set[0][0][0]).size()<<endl;
        return 1;
    }
    if (values->getVsize()!=ordered_set.size()*(ordered_set[0]).size()*(ordered_set[0][0]).size()){
        cerr<<"OVAluesN4 vsize is wrong: "<<values->getVsize()<<" instead of "<<ordered_set.size()*(ordered_set[0]).size()*(ordered_set[0][0]).size()<<endl;
        return 1;
    }

    cout<<"Instanciating OQualities"<<endl;
    OQualities oqualities = OQualities(values);

    cout<<"Computing qualities"<<endl;
    oqualities.computeQualities();
    int size=oqualities.getQualities()->getSize();
    if (size!=values->getOsize()){
        cerr<<"Qualities size is wrong: "<<size<<" instead of "<<values->getOsize()<<endl;
        return 2;
    }

    cout<<"Instanciating OPartitioner"<<endl;
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
