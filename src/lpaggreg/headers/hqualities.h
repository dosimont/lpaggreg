#ifndef HQUALITIES_H
#define HQUALITIES_H

#include <vector>
#include <memory>
#include "qualities.h"
#include "quality.h"
#include "hvaluesn.h"
#include "complexity.h"

using namespace std;

typedef shared_ptr<vector< shared_ptr<lpaggreg::Quality> > > hqualities;

namespace lpaggreg{

    class HQualities: Qualities
    {
    public:
        HQualities(hqualities qualities, HValuesMetaData metaData);
        HQualities(shared_ptr<HValues> values);

        void normalize();
        void computeQualities();

        unsigned int size();

        hqualities getQualities() const;

        HValuesMetaData getMetaData() const;

    private:
        shared_ptr<HValues> values;
        hqualities qualities;
        HValuesMetaData metaData;

    };

}

#endif // HQUALITIES_H
