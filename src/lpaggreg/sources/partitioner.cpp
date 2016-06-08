#include "partitioner.h"

lpaggreg::Partitioner::Partitioner():pList(new vector<float>())
{

}

vector<float> *lpaggreg::Partitioner::getPList() const
{
    return pList;
}


