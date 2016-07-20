#include "opartition.h"


int lpaggreg::OPart::getStart() const
{
    return start;
}

void lpaggreg::OPart::setStart(int value)
{
    start = value;
}

int lpaggreg::OPart::getEnd() const
{
    return end;
}

void lpaggreg::OPart::setEnd(int value)
{
    end = value;
}

template<typename T>
lpaggreg::OPartition<T>::OPartition(vector<int> cuts, shared_ptr<UpperTriangularMatrix<shared_ptr<Quality<T> > > > qualities, float parameter):parameter(parameter), cuts(cuts), qualities(qualities)
{
    computeParts();
    computeQuality();
}

template<typename T>
vector<int> lpaggreg::OPartition<T>::getCuts() const
{
    return cuts;
}

template<typename T>
vector<lpaggreg::OPart> lpaggreg::OPartition<T>::getParts() const
{
    return parts;
}

template<typename T>
void lpaggreg::OPartition<T>::computeParts()
{
    for (int i=0; i<cuts.size();i=cuts[i]+1){
        parts.push_back(OPart(i, cuts[i]));
    }
}

template<typename T>
void lpaggreg::OPartition<T>::computeQuality()
{
    quality=shared_ptr<Quality<T> >(new Quality<T>());
    for (OPart it: parts){
        quality+=qualities(it.getStart(),it.getEnd());
    }
}

template<typename T>
float lpaggreg::OPartition<T>::getParameter() const
{
    return parameter;
}

template<typename T>
shared_ptr<lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality<T> > > > lpaggreg::OPartition<T>::getQualities() const
{
    return qualities;
}

bool lpaggreg::operator==(lpaggreg::OPart &opart1, lpaggreg::OPart &opart2)
{
    return (opart1.getStart()==opart2.getStart()&&opart1.getEnd()==opart2.getEnd());
}

bool lpaggreg::operator!=(lpaggreg::OPart &opart1, lpaggreg::OPart &opart2)
{
    return !(opart1==opart2);
}

#ifndef PARTITION_COMPARE_QUALITY
template<typename T>
bool operator==(lpaggreg::OPartition<T> &opartition1, lpaggreg::OPartition<T> &opartition2)
{
    if (opartition1.getParts().size()!=opartition2.getParts().size()){
        return false;
    }else{
        for (int i=0; i<opartition1.getParts().size(); i++){
            if (opartition1.getParts().operator [](i)!=opartition2.getParts().operator [](i)){
                return false;
            }
        }
        return true;
    }
}
#endif

#ifdef PARTITION_COMPARE_QUALITY
template<typename T>
bool operator==(lpaggreg::OPartition<T> &opartition1, lpaggreg::OPartition<T> &opartition2)
{
    return (opartition1.getQuality()==opartition2.getQuality());
}
#endif

template<typename T>
bool operator!=(lpaggreg::OPartition<T> &opartition1, lpaggreg::OPartition<T> &opartition2)
{
    return !(opartition1==opartition2);
}








