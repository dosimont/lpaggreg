#ifndef OPARTITION_H
#define OPARTITION_H

#include <vector>
#include <memory>
#include "quality.h"

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

    private:
        int start;
        int end;
    };

    template<typename T>
    class OPartition
    {
    public:
        OPartition(vector<int> cuts, shared_ptr<Quality<lp_quality_type> > quality);
        vector<int> getCuts() const;
        void setCuts(const vector<int> &value);

        vector<OPart> getParts() const;

        shared_ptr<Quality<lp_quality_type> > getQuality() const;
        void setQuality(const shared_ptr<Quality<lp_quality_type> > &value);

    private:
        void computeParts();

        vector<int> cuts;
        vector<OPart> parts;
        shared_ptr<Quality<lp_quality_type> > quality;
    };

}

#endif // OPARTITION_H
