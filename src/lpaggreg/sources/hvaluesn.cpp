#include "hvaluesn.h"


lpaggreg::HValuesN2Proxy::HValuesN2Proxy(int index, lpaggreg::HValuesN2 hvalues):index(index), hvalues(hvalues)
{

}

lpaggreg::HValuesN3Proxy::HValuesN3Proxy(int index, lpaggreg::HValuesN3 hvalues):index(index), hvalues(hvalues)
{

}

lpaggreg::HValuesN3Proxy::HValuesN4Proxy(int index, lpaggreg::HValuesN4 hvalues):index(index), hvalues(hvalues)
{

}

double lpaggreg::HValuesN2Proxy::operator[](unsigned int h)
{
    return (hvalues.values.operator [](h))[index];
}

double lpaggreg::HValuesN3Proxy::operator[](unsigned int h)
{
    return (hvalues.values.operator [](h))[hvalues.toI(index)][hvalues.toJ(index)];
}

double lpaggreg::HValuesN4Proxy::operator[](unsigned int h)
{
    return (hvalues.values.operator [](h))[hvalues.toI(index)][hvalues.toJ(index)][hvalues.toK(index)];
}
