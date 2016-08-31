#ifndef OQUALITIES_H
#define OQUALITIES_H

#include <vector>
#include <memory>
#include "qualities.h"
#include "quality.h"
#include "ovaluesn.h"
#include "uppertriangularmatrix.h"
#include "complexity.h"

using namespace std;

namespace lpaggreg{

    class OQualities: Qualities
    {
    public:
        OQualities(shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > >qualities);
        OQualities(shared_ptr<OValues> values);

        void normalize();
        void computeQualities();

        unsigned int size();

        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > getQualities() const;

    private:
        shared_ptr<OValues> values;
        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > >qualities;
    };

}

#endif // OQUALITIES_H
