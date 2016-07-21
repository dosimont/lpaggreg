#ifndef OPARTITION_H
#define OPARTITION_H

#include <vector>
#include <memory>
#include "quality.h"
#include "uppertriangularmatrix.h"
#include "lpglobal.h"

using namespace std;

namespace lpaggreg{

    class OPart
    {
    public:
        OPart();
        OPart(int start, int end);
        int getStart() const;
        void setStart(int value);

        int getEnd() const;
        void setEnd(int value);

        friend bool operator==(OPart &opart1, OPart &opart2);
        friend bool operator!=(OPart &opart1, OPart &opart2);

    private:
        int start;
        int end;
    };

    class OPartition
    {
    public:
        OPartition(vector<int> cuts, shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > qualities, float parameter);
        vector<int> getCuts() const;
        vector<OPart> getParts() const;
        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > getQualities() const;

        float getParameter() const;

    private:
        void computeParts();
        void computeQuality();
        float parameter;
        vector<int> cuts;
        vector<OPart> parts;
        shared_ptr<Quality> quality;
        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > qualities;
    };

    bool operator==(OPartition &opartition1, OPartition &opartition2);
    bool operator!=(OPartition &opartition1, OPartition &opartition2);
}

#endif // OPARTITION_H
