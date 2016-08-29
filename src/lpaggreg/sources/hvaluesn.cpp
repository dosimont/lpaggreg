#include "hvaluesn.h"


lpaggreg::HValuesN2Proxy::HValuesN2Proxy(int a, lpaggreg::HValuesN2 hvalues):a(a), hvalues(hvalues)
{

}

double lpaggreg::HValuesN2Proxy::operator[](unsigned int h)
{
    return (hvalues.values.operator [](h))[a];
}
