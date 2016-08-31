#ifndef HQUALITIES_H
#define HQUALITIES_H

#include <vector>
#include <memory>
#include "qualities.h"
#include "quality.h"
#include "hvaluesn.h"
#include "complexity.h"

using namespace std;

namespace lpaggreg{

    class HQualities: Qualities
    {
    public:
        HQualities(shared_ptr<vector< shared_ptr<Quality> > > qualities);
        HQualities(shared_ptr<HValues> values);

        void normalize();
        void computeQualities();

        unsigned int size();

        shared_ptr<vector<shared_ptr<Quality> > > getQualities() const;

    private:
        shared_ptr<HValues> values;
        shared_ptr<vector< shared_ptr<Quality> > > qualities;

    };

}

#endif // HQUALITIES_H
