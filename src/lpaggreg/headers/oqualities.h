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

typedef shared_ptr<lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality> > > oqualities;

namespace lpaggreg{

    class OQualities: Qualities
    {
    public:
        OQualities(oqualities qualities);
        OQualities(shared_ptr<OValues> values);

        void normalize();
        void computeQualities();

        unsigned int size();

        oqualities getQualities() const;

    private:
        shared_ptr<OValues> values;
        oqualities qualities;
    };

}

#endif // OQUALITIES_H
