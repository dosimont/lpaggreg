#ifndef OQUALITIES_H
#define OQUALITIES_H

#include <vector>
#include <memory>
#include "quality.h"
#include "ovaluesn.h"
#include "uppertriangularmatrix.h"
#include "complexity.h"

using namespace std;

namespace lpaggreg{

    class OQualities
    {
    public:
        OQualities(shared_ptr<OValues> values);
        OQualities(vector<double> original_values);
        OQualities(vector<vector<double> > original_values);
        OQualities(vector<vector<vector<double> > > original_values);
        OQualities(vector<vector<vector<vector<double> > > >original_values);

        void normalize();
        void computeQualities();

        unsigned int size();

        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > > getQualities() const;

        shared_ptr<OValues> getValues() const;

    private:
        shared_ptr<OValues> values;
        shared_ptr<UpperTriangularMatrix<shared_ptr<Quality> > >qualities;
    };

}

#endif // OQUALITIES_H
