#include "hvalues.h"

lpaggreg::HValues::HValues(unsigned int hsize, unsigned int vsize, vector<int> parents): vsize(vsize), metaData(HValuesMetaData(hsize, parents))
{
    metaData.setPath();

}

void lpaggreg::HValuesMetaData::setPath()
{
    leaves=0;
    for (int h=0; h<hsize; h++){
        if(!(std::find(parents.begin(), parents.end(), h) != parents.end())) {
            path.push_back(h);
            size[h]=1;
            leaves++;
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
    root=path[path.size()-1];
}

lpaggreg::HValuesMetaData lpaggreg::HValues::getMetaData() const
{
    return metaData;
}

unsigned int lpaggreg::HValues::getVsize(){return vsize;}


lpaggreg::HValuesProxy::HValuesProxy(int index, lpaggreg::HValues *hvalues): hvalues(hvalues), index(index)
{

}

double lpaggreg::HValuesProxy::operator[](unsigned int h)
{
    return hvalues->getValue(h, index);
}

unsigned int lpaggreg::HValuesMetaData::getHsize() const
{
    return hsize;
}

vector<int> lpaggreg::HValuesMetaData::getParents() const
{
    return parents;
}

map<int, int> lpaggreg::HValuesMetaData::getSize() const
{
    return size;
}

vector<int> lpaggreg::HValuesMetaData::getPath() const
{
    return path;
}

int lpaggreg::HValuesMetaData::getRoot() const
{
    return root;
}

int lpaggreg::HValuesMetaData::getLeaves() const
{
    return leaves;
}

lpaggreg::HValuesMetaData::HValuesMetaData(unsigned int hsize, vector<int> parents)
    : hsize(hsize), parents(parents)
{

}
