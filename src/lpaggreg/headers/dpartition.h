#ifndef DPARTITION_H
#define DPARTITION_H

#include <vector>
#include <memory>
#include <set>
#include "quality.h"
#include "hvalues.h"
#include "lpglobal.h"
#include "dqualities.h"
#include "partition.h"

using namespace std;

namespace lpaggreg{

    class DPart
    {
    public:
        DPart(int h, int hsize, int start, int end);

        friend bool operator==(DPart &dpart1, DPart &dpart2);
        friend bool operator!=(DPart &dpart1, DPart &dpart2);

        int getH() const;

        int getHSize() const;

        int getOSize();

        int getSize();

        int getStart() const;

        int getEnd() const;

    private:
        int h;
        int hsize;
        int start;
        int end;
    };

    class DPartition: public Partition
    {
    public:
        DPartition(vector<shared_ptr<UpperTriangularMatrix<int> > > cuts, dqualities qualities, float parameter, HValuesMetaData metaData);


        vector<vector<DPart> > getParts() const;

        dqualities getQualities() const;

        HValuesMetaData getMetaData() const;

        vector<shared_ptr<UpperTriangularMatrix<int> > > getCuts() const;

    private:
        void computeParts();
        void computeQuality();
        float parameter;
        vector<shared_ptr<UpperTriangularMatrix<int> > > cuts;
        vector<vector<DPart> > parts;
        dqualities qualities;
        HValuesMetaData metaData;
    };

    bool operator==(DPartition &dpartition1, DPartition &dpartition2);
    bool operator!=(DPartition &dpartition1, DPartition &dpartition2);
}

#endif // DPARTITION_H
