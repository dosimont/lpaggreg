#ifndef PARTITIONER_H
#define PARTITIONER_H

#include <vector>
#include <map>
#include <memory>
#include "lpglobal.h"
#include "quality.h"

using namespace std;

namespace lpaggreg{

    class Partitioner
    {
    public:
        Partitioner();
        virtual void computeBestPartitions(float threshold, float min=0.0, float max=1.0)=0;
        vector<float> getPList() const;
        float getP(int strategy);
        float computeAUC();

        map<float, shared_ptr<Quality> > getQualityList() const;

    protected:
        vector<float> pList;
        map<float, shared_ptr<Quality> > qualityList;

    private:
        float computePOpt();


    };

}

#endif // PARTITIONER_H
