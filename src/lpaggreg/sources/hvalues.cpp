#include "hvalues.h"

lpaggreg::HValues::HValues(unsigned int hsize, unsigned int vsize, vector<list<int> >tree):hsize(hsize), vsize(vsize), tree(tree)
{

}

unsigned int lpaggreg::HValues::getVsize(){return vsize;}

unsigned int lpaggreg::HValues::getHsize(){return hsize;}
