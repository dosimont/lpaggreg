#ifndef HPARTITION_H
#define HPARTITION_H


#include <vector>
#include <memory>
#include <set>
#include "quality.h"
#include "hvalues.h"
#include "lpglobal.h"

using namespace std;

namespace lpaggreg{

    class HPart
    {
    public:
        HPart();
        HPart(int h, int size);

        friend bool operator==(HPart &hpart1, HPart &hpart2);
        friend bool operator!=(HPart &hpart1, HPart &hpart2);

        int getH() const;
        int getSize() const;

    private:
        int h;
        int size;
    };

    class HPartition
    {
    public:
        HPartition(vector<bool> aggregated, shared_ptr<vector<shared_ptr<Quality> > > qualities, float parameter, HValuesMetaData metaData);


        vector<bool> getAggregated() const;

        vector<HPart> getParts() const;

        shared_ptr<Quality> getQuality() const;

        shared_ptr<vector<shared_ptr<Quality> > > getQualities() const;

        HValuesMetaData getMetaData() const;

        float getParameter() const;

    private:
        void computeParts();
        void computeQuality();
        float parameter;
        vector<bool> aggregated;
        vector<HPart> parts;
        shared_ptr<Quality> quality;
        shared_ptr<vector<shared_ptr<Quality> > > qualities;
        HValuesMetaData metaData;
    };

    bool operator==(HPartition &opartition1, HPartition &opartition2);
    bool operator!=(HPartition &opartition1, HPartition &opartition2);
}

#endif // HPARTITION_H
