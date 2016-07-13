#ifndef OQUALITIES_H
#define OQUALITIES_H

#include <vector>
#include "quality.h"
#include "ovalues.h"
#include "uppertriangularmatrix.h"
#include "complexity.h"

using namespace std;

namespace lpaggreg{

    class OQualities
    {
    public:
        OQualities(OValues* values);
        void normalize();
        void computeQualities();

        OValues *getValues() const;
        void setValues(OValues *value);

        double & operator() (unsigned int i, unsigned int j) const {return qualities[index];}
        double operator() (unsigned int i, unsigned int j) {return qualities[index];}

        unsigned int size();

    private:
        OValues* values;
        UpperTriangularMatrix<Quality<lp_quality_type>> qualities;
    };

}

#endif // OQUALITIES_H
