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
        HValuesMetaData(unsigned int leaves, vector<int> parents);

        void setPath();

        unsigned int getHsize() const;

        vector<int> getParents() const;

        map<int, int> getSize() const;

        vector<int> getPath() const;

        int getRoot() const;

        int getLeaves() const;

    private:
        unsigned int hsize;
        vector<int>parents;
        map<int, int>size;
        vector<int> path;
        int root;
        int leaves;
    };

    class HValues
    {
    protected:
        unsigned int hsize;
        unsigned int vsize;
        vector<int>parents;
        map<int, int>size;
        vector<int> path;
        int root;
        int leaves;
        HValuesMetaData metaData;
    public:
        HValues(unsigned int hsize, unsigned int vsize, vector<int>parents);
        virtual HValuesProxy operator[] (unsigned int index)=0;
        unsigned int getVsize();
        virtual double getValue(int h, int index)=0;
        HValuesMetaData getMetaData() const;
    };

    class HValuesProxy
    {
    private:
        HValues* hvalues;
        int index;
    public:
        HValuesProxy(int index, HValues *hvalues);
        double operator[](unsigned int h);
    };
}


#endif // HVALUES_H
