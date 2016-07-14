#ifndef OQUALITIES_H
#define OQUALITIES_H

#include <vector>
#include <memory>
#include "quality.h"
#include "ovalues.h"
#include "uppertriangularmatrix.h"
#include "complexity.h"

using namespace std;

namespace lpaggreg{

    class OQualities
    {
    public:
        OQualities(shared_ptr<OValues> values);
        void normalize();
        void computeQualities();

        //double & operator() (unsigned int i, unsigned int j) const {return qualities->operator()(i, j);}
        //double operator() (unsigned int i, unsigned int j) {return qualities->operator()(i, j);}

        unsigned int size();

        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > > > getQualities() const;

        shared_ptr<OValues> getValues() const;

    private:
        shared_ptr<OValues> values;
        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<lp_quality_type> > > >qualities;
    };

}

#endif // OQUALITIES_H
