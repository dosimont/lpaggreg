#ifndef DQUALITIES_H
#define DQUALITIES_H

#include <vector>
#include <memory>
#include "qualities.h"
#include "quality.h"
#include "dvaluesn.h"
#include "complexity.h"
#include "uppertriangularmatrix.h"

using namespace std;

namespace lpaggreg{

    class DQualities: Qualities
    {
    public:
        DQualities(shared_ptr<vector< shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > > > qualities, HValuesMetaData metaData);
        DQualities(shared_ptr<DValues> values);

        void normalize();
        void computeQualities();

        unsigned int size();

        HValuesMetaData getMetaData() const;

        shared_ptr<vector<shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > > > getQualities() const;

    private:
        shared_ptr<DValues> values;
        shared_ptr<vector< shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > > > qualities;
        HValuesMetaData metaData;

    };

}

#endif // DQUALITIES_H
