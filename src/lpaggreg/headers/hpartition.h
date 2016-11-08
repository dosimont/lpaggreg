#ifndef HPARTITION_H
#define HPARTITION_H


#include <vector>
#include <memory>
#include <set>
#include "quality.h"
#include "hqualities.h"
#include "hvalues.h"
#include "lpglobal.h"
#include "partition.h"

using namespace std;

namespace lpaggreg{

    class HPart
    {
    public:
        HPart(int h, int size, shared_ptr<Quality> quality);

        friend bool operator==(HPart &hpart1, HPart &hpart2);
        friend bool operator!=(HPart &hpart1, HPart &hpart2);

        int getH() const;
        int getSize() const;

        shared_ptr<Quality> getQuality() const;

    private:
        int h;
        int size;
        shared_ptr<Quality> quality;
    };

    class HPartition: public Partition
    {
    public:
        HPartition(vector<bool> aggregated, hqualities qualities, float parameter, HValuesMetaData metaData);
        vector<bool> getAggregated() const;
        vector<HPart> getParts() const;
        hqualities getQualities() const;
        HValuesMetaData getMetaData() const;

    private:
        void computeParts();
        void computeQuality();
        vector<bool> aggregated;
        vector<HPart> parts;
        hqualities qualities;
        HValuesMetaData metaData;
        void computeSubPart(int h);
    };

    bool operator==(HPartition &hpartition1, HPartition &hpartition2);
    bool operator!=(HPartition &hpartition1, HPartition &hpartition2);
}

#endif // HPARTITION_H
