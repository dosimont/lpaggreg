#ifndef OPARTITION_H
#define OPARTITION_H

#include <iostream>
#include <vector>
#include <memory>
#include "quality.h"
#include "oqualities.h"
#include "uppertriangularmatrix.h"
#include "lpglobal.h"
#include "partition.h"

using namespace std;

namespace lpaggreg{

    class OPart
    {
    public:
        OPart();
        OPart(int start, int end);
        int getStart() const;
        int getEnd() const;
        int getSize();

        friend bool operator==(OPart &opart1, OPart &opart2);
        friend bool operator!=(OPart &opart1, OPart &opart2);

    private:
        int start;
        int end;
    };

    class OPartition: public Partition
    {
    public:
        OPartition(vector<int> cuts, oqualities qualities, float parameter);
        vector<int> getCuts() const;
        vector<OPart> getParts() const;
        oqualities getQualities() const;

    private:
        void computeParts();
        void computeQuality();
        vector<int> cuts;
        vector<OPart> parts;
        oqualities qualities;
    };

    bool operator==(OPartition &opartition1, OPartition &opartition2);
    bool operator!=(OPartition &opartition1, OPartition &opartition2);
}

#endif // OPARTITION_H
