#include "partitioner.h"

lpaggreg::Partitioner::Partitioner()
{

}

vector<float> lpaggreg::Partitioner::getPList() const
{
    return pList;
}

float lpaggreg::Partitioner::getP(int strategy)
{
    switch(strategy){
    case P_MIN:
        return 0;
    case P_MAX:
        return pList[pList.size()-1];
    case P_OPT:
        return computePOpt();
    }
    return 0;
}

float lpaggreg::Partitioner::computeAUC()
{
    float auc=0.0;
    for (int i=0; i<pList.size()-1; i++){
        auc+=((qualityList[pList[i+1]])->getGain()-(qualityList[pList[i]])->getGain())*((qualityList[pList[i+1]])->getLoss()+(qualityList[pList[i]])->getLoss())/2;
    }
    return 1.0-auc;
}

map<float, shared_ptr<lpaggreg::Quality> > lpaggreg::Partitioner::getQualityList() const
{
    return qualityList;
}

float lpaggreg::Partitioner::computePOpt()
{
    float popt;
    lp_quality_type score=RAND_MAX;
    for (float p: pList){
        lp_quality_type gain=(qualityList[p])->getGain();
        lp_quality_type loss=(qualityList[p])->getLoss();
        lp_quality_type currentScore=(gain-1)*(gain-1)+loss*loss;
        if (currentScore<=score){
            score=currentScore;
            popt=p;
        }
    }
    return popt;
}


