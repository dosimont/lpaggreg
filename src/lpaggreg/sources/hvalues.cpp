#include "hvalues.h"

lpaggreg::HValues::HValues(unsigned int hsize, unsigned int vsize, vector<int> parents):hsize(hsize), vsize(vsize), parents(parents)
{
    setPath();
}

void lpaggreg::HValues::setPath()
{
    for (int h=0; h<hsize; h++){
        if(!(std::find(parents.begin(), parents.end(), h) != parents.end())) {
            path.push_back(h);
            size[h]=1;
        }
    }
    for (int i=0; parents[path[i]]!=-1; i++){
        if (size.count(parents[path[i]])) {
            size[parents[path[i]]]++;
        }else{
            path.push_back(parents[path[i]]);
            size[parents[path[i]]]=1;
        }
    }
}

unsigned int lpaggreg::HValues::getVsize(){return vsize;}

unsigned int lpaggreg::HValues::getHsize(){return hsize;}

lpaggreg::HValuesProxy::HValuesProxy(int index, lpaggreg::HValues *hvalues): hvalues(hvalues), index(index)
{

}

double lpaggreg::HValuesProxy::operator[](unsigned int h)
{
    return hvalues->getValue(h, index);
}
