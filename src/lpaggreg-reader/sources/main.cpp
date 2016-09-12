#include <iostream>
#include <vector>
#include <memory>
#include "oqualities.h"
#include "opartitioner.h"
#include "ovaluesn.h"

using namespace std;
using namespace lpaggreg;

#define SEP ", "

int main()
{
    vector<double> pa0 = {1, 1, 1, 1, 1};
    vector<double> pb1 = {1, 1, 1, 1, 1};
    vector<double> pc2 = {0.67, 0.5, 0, 0, 0.33};
    vector<double> pd2 = {0, 0, 1, 1, 0.67};
    vector<double> pd3 = {0, 0, 0.5, 1, 0.33};
    vector<double> pe3 = {0.67, 0, 0, 0, 0};
    vector< vector<double> > micromodel;
    micromodel.push_back(pa0);
    micromodel.push_back(pb1);
    micromodel.push_back(pc2);
    micromodel.push_back(pd2);
    micromodel.push_back(pd3);
    micromodel.push_back(pe3);
    shared_ptr<OValuesN2> values = shared_ptr<OValuesN2>(new OValuesN2(micromodel));
    OQualities oqualities = OQualities(values);
    oqualities.computeQualities();
    oqualities.normalize();
    OPartitioner opartitioner = OPartitioner(oqualities);
    opartitioner.computeBestPartitions(0.001);
    list<tuple<float, int, int> > tuples=opartitioner.getPartitionsTuples();
    for (auto tuple: tuples){
        cout<<get<0>(tuple)<<SEP<<get<1>(tuple)<<SEP<<get<2>(tuple)<<endl;
    }
    return 0;
}
