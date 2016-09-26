#include "hvalues.h"

lpaggreg::HValues::HValues(unsigned int leaves, unsigned int vsize, vector<int> parents): vsize(vsize), metaData(HValuesMetaData(leaves, parents))
{

}

lpaggreg::HValuesProxy lpaggreg::HValues::operator[](unsigned int h)
{
    return HValuesProxy(h,this);
}

void lpaggreg::HValuesMetaData::setPath()
{
    for (int h=0; h<leaveSize; h++){
        path.push_back(h);
        children.push_back(vector<int>());
        size[h]=1;
    }
    for (int h=leaveSize; h<hsize; h++){
        children.push_back(vector<int>());
    }
    for (int i=0; parents[path[i]]!=-1; i++){
        if (size.count(parents[path[i]])) {
            size[parents[path[i]]]+=size[path[i]];
        }else{
            path.push_back(parents[path[i]]);
            size[parents[path[i]]]=size[path[i]];
        }
        children[parents[path[i]]].push_back(path[i]);
    }
    root=path[path.size()-1];
}

lpaggreg::HValuesMetaData lpaggreg::HValues::getMetaData() const
{
    return metaData;
}

unsigned int lpaggreg::HValues::getVsize(){return vsize;}


lpaggreg::HValuesProxy::HValuesProxy(int h, lpaggreg::HValues *hvalues): hvalues(hvalues), h(h)
{

}

double lpaggreg::HValuesProxy::operator[](unsigned int index)
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

int lpaggreg::HValuesMetaData::getLeaveSize() const
{
    return leaveSize;
}

vector<vector<int> > lpaggreg::HValuesMetaData::getChildren() const
{
    return children;
}

lpaggreg::HValuesMetaData::HValuesMetaData(unsigned int leaveSize, vector<int> parents)
    : hsize(parents.size()), parents(parents), leaveSize(leaveSize)
{
    setPath();
}
