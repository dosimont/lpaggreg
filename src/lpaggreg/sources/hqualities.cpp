#include "hqualities.h"


shared_ptr<vector<shared_ptr<lpaggreg::Quality> > > lpaggreg::HQualities::getQualities() const
{
    return qualities;
}
