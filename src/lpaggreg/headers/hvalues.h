#ifndef HVALUES_H
#define HVALUES_H

#include <vector>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

namespace lpaggreg{

    class HValuesProxy;

    class HValuesMetaData
    {
    public:
        friend class HValues;
        HValuesMetaData(unsigned int leaveSize, vector<int> parents);

        void setPath();

        unsigned int getHsize() const;

        vector<int> getParents() const;

        map<int, int> getSize() const;

        vector<int> getPath() const;

        int getRoot() const;

        int getLeaveSize() const;

        vector<vector<int> > getChildren() const;

    private:
        unsigned int hsize;
        vector<int>parents;
        vector<vector<int> >children;
        map<int, int>size;
        vector<int> path;
        int root;
        int leaveSize;
    };

    class HValues
    {
    protected:
        unsigned int vsize;
        HValuesMetaData metaData;
    public:
        HValues(unsigned int leaves, unsigned int vsize, vector<int>parents);
        HValuesProxy operator[] (unsigned int h);
        unsigned int getVsize();
        virtual double getValue(int h, int index)=0;
        HValuesMetaData getMetaData() const;
    };

    class HValuesProxy
    {
    private:
        HValues* hvalues;
        int h;
    public:
        HValuesProxy(int h, HValues *hvalues);
        double operator[](unsigned int index);
    };
}


#endif // HVALUES_H
