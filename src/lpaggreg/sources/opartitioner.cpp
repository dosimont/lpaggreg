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

void lpaggreg::OPartitioner::computeBestCuts(float parameter)
{
    int size=qualities->size();
    vector<int> cut;
    vector<Tradeoff<lp_quality_type> > tradeoff;
    for (int i=0; i<size; i++){
        cut.push_back(size-1);
        tradeoff.push_back(Tradeoff());
    }
    for (int i=size-1;i>=0;i--){
        tradeoff[i]=Tradeoff(qualities[i][size-1], parameter);
        for (int cut_t=i; cut_t<size-2; cut_t++){
            Tradeoff tradeoff_t=Tradeoff(qualities[i][cut_t], parameter);
            tradeoff_t+=tradeoff[cut_t+1];
            if (tradeoff_t>tradeoff[i]){
                cut[i]=cut_t;
                tradeoff[i]=tradeoff_t;
            }
        }
    }
}
