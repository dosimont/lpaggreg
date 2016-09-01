#include "ovalues.h"

lpaggreg::OValues::OValues(unsigned int vsize, unsigned int osize):osize(osize), vsize(vsize)
{

}

unsigned int lpaggreg::OValues::getVsize(){return vsize;}

unsigned int lpaggreg::OValues::getOsize(){return osize;}
