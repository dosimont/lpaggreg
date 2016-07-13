#include "opartitioner.h"

lpaggreg::OPartitioner::OPartitioner()
{

}

lpaggreg::OPartitioner::OPartitioner(vector<vector<lpaggreg::Quality<long double>> >* qualities):Partitioner(Partitioner()), qualities(qualities)
{

}

void lpaggreg::OPartitioner::computeBestPartitions(float threshold)
{

}

vector<int> lpaggreg::OPartitioner::computeBestCuts(float parameter)
{
    int size=qualities->getSize();
    vector<int> cut(size, size-1);
    vector<Tradeoff<lp_quality_type> > tradeoff(size,Tradeoff<lp_quality_type>());
    for (int i=size-1;i>=0;i--){
        tradeoff[i]=Tradeoff(qualities(i,size-1), parameter);
        for (int cut_t=i; cut_t<size-2; cut_t++){
            Tradeoff tradeoff_t=Tradeoff(qualities(i,cut_t), parameter);
            tradeoff_t+=tradeoff[cut_t+1];
            if (tradeoff_t>tradeoff[i]){
                cut[i]=cut_t;
                tradeoff[i]=tradeoff_t;
            }
        }
    }
    return cut;
}
