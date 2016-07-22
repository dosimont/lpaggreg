#include <iostream>
#include <vector>
#include <memory>
#include "oqualities.h"
#include "opartitioner.h"
#include "ovaluesn.h"
#include "test_opartitionglobal.h"

using namespace std;
using namespace lpaggreg;

int main()
{
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
    cout<<"Instanciating OQualities"<<endl;
    OQualities oqualities = OQualities(values);
    cout<<"Computing qualities"<<endl;
    oqualities.computeQualities();
    int size=oqualities.getQualities()->getSize();
    if (size!=values->getOsize()){
        cerr<<"Qualities size is wrong: "<<size<<" instead of "<<values->getOsize()<<endl;
        return 1;
    }else{
        cout<<"Qualities size: "<<size<<endl;
    }
    cout<<"Normalizing qualities"<<endl;
    //oqualities.normalize();
    size=oqualities.getQualities()->getSize();
    if (size!=values->getOsize()){
        cerr<<"Qualities size is wrong: "<<size<<" instead of "<<values->getOsize()<<endl;
        return 1;
    }else{
        cout<<"Qualities size: "<<size<<endl;
    }
    for (int i=0;i<size;i++){
        for (int j=i;j<size;j++){
            cout<<i<<","<<j<<"="<<oqualities.getQualities()->operator ()(i,j)->getGain()<<"-"<<oqualities.getQualities()->operator ()(i,j)->getLoss()<<endl;
        }
    }
    for (int i=0;i<oqualities.getQualities()->getElements();i++){
        cout<<i<<"="<<oqualities.getQualities()->operator [](i)->getGain()<<"-"<<oqualities.getQualities()->operator [](i)->getLoss()<<endl;
    }
    cout<<"Instanciating OPartitioner"<<endl;
    OPartitioner opartitioner = OPartitioner(oqualities);
    float p=1.0;
    cout<<"Computing Best Partition for "<<p<<endl;
    shared_ptr<lpaggreg::OPartition> opartition=opartitioner.computeBestPartition(p);
    cout<<"Quality: "<<opartition->getQuality()->getGain()<<";"<<opartition->getQuality()->getLoss()<<endl;
    for (int it: opartition->getCuts()){
        cout<<it<<"; ";
    }
    cout<<endl;
    for (OPart it: opartition->getParts()){
        cout<<it.getStart()<<"-"<<it.getEnd()<<"; ";
    }
    cout<<endl;
    cout<<"Computing Best Partitions"<<endl;
    //opartitioner.computeBestPartitions(0.01);
    return 0;
}
