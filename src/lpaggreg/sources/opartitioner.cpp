#include "opartitioner.h"


lpaggreg::OPartitioner::OPartitioner(shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > > >):qualities(qualities)
{

}

void lpaggreg::OPartitioner::computeBestPartitions(float threshold)
{

}

vector<int> lpaggreg::OPartitioner::computeBestCuts(float parameter)
{
    int size=qualities->getSize();
    vector<int> cut(size, size-1);
    vector<shared_ptr<Tradeoff<lp_quality_type> > > tradeoff= vector<shared_ptr<Tradeoff<lp_quality_type> > >(size, shared_ptr<Tradeoff<lp_quality_type> >(new Tradeoff<lp_quality_type>()));
    shared_ptr<Tradeoff<lp_quality_type> > tradeoff_t=shared_ptr<Tradeoff<lp_quality_type> >(new Tradeoff<lp_quality_type>());
    for (int i=size-1;i>=0;i--){
        (tradeoff[i])->set(qualities->operator()(i,size-1), parameter);
        for (int cut_t=i; cut_t<size-2; cut_t++){
            tradeoff_t->set(qualities->operator()(i,cut_t), parameter);
            *tradeoff_t+=*tradeoff[cut_t+1];
            if (*tradeoff_t>*tradeoff[i]){
                cut[i]=cut_t;
                tradeoff[i]=tradeoff_t;
            }
        }
    }
    return cut;
}
