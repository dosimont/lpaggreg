#ifndef PARTITION_H
#define PARTITION_H


#include <vector>
#include <memory>
#include <set>
#include "quality.h"
#include "lpglobal.h"

using namespace std;

namespace lpaggreg{

    class Partition
    {
    public:
        Partition(float parameter);
        float getParameter() const;
        shared_ptr<Quality> getQuality() const;

    protected:
        float parameter;
        shared_ptr<Quality> quality;
    };
}

#endif // PARTITION_H
