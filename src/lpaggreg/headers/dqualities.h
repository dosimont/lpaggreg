#ifndef DQUALITIES_H
#define DQUALITIES_H

#include <vector>
#include <memory>
#include "qualities.h"
#include "oqualities.h"
#include "quality.h"
#include "dvaluesn.h"
#include "complexity.h"
#include "uppertriangularmatrix.h"

using namespace std;

typedef shared_ptr<vector< shared_ptr<lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality> > > > > dqualities;

namespace lpaggreg{

    class DQualities: Qualities
    {
    public:
        DQualities(dqualities qualities, HValuesMetaData metaData);
        DQualities(shared_ptr<DValues> values);

        void normalize();
        void computeQualities();

        unsigned int size();

        HValuesMetaData getMetaData() const;

        dqualities getQualities() const;

    private:
        shared_ptr<DValues> values;
        dqualities qualities;
        HValuesMetaData metaData;

    };

}

#endif // DQUALITIES_H
