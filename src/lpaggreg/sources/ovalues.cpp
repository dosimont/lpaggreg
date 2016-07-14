#include "ovalues.h"

lpaggreg::OValues::OValues(unsigned int osize, unsigned int vsize):osize(osize), vsize(vsize)
{

}

unsigned int lpaggreg::OValues::getVsize(){return vsize;}

unsigned int lpaggreg::OValues::getOsize(){return osize;}
