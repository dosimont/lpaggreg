#include "tradeoff.h"


template<typename T>
T lpaggreg::Tradeoff<T>::getValue() const
{
    return value;
}

template<typename T>
void lpaggreg::Tradeoff<T>::computePIC(T p)
{
    value=(p*quality.getGain())+((p-1)*quality.getLoss());
}

template<typename T>
Quality<T> lpaggreg::Tradeoff::getQuality() const
{
    return quality;
}

lpaggreg::Tradeoff<T>::Tradeoff(Tradeoff<T> &tradeoff):value(tradeoff.getValue()), quality(tradeoff.getQuality())
{

}

template<typename T>
lpaggreg::Tradeoff<T>::Tradeoff(lpaggreg::T value, Quality<lpaggreg::T> quality):value(value), quality(quality)
{
}

template<typename T>
lpaggreg::Tradeoff<T>::Tradeoff(Quality<lpaggreg::T> quality, T p):quality(quality)
{
    computePIC(p);
}

template<typename T>
lpaggreg::Tradeoff<T>::Tradeoff(Quality<lpaggreg::T> quality):quality(quality)
{
    value=0;
}

template<typename T>
void lpaggreg::Tradeoff<T>::operator+=(lpaggreg::Tradeoff<T> &tradeoff)
{
    quality+=tradeoff.quality;
    value+=tradeoff.value;
}

template<typename T>
void lpaggreg::Tradeoff<T>::operator-=(lpaggreg::Tradeoff<T> &tradeoff)
{
    quality-=tradeoff.quality;
    value-=tradeoff.value;
}

template<typename T>
void lpaggreg::Tradeoff<T>::operator*=(lpaggreg::Tradeoff<T> &tradeoff)
{
    quality*=tradeoff.quality;
    value*=tradeoff.value;
}

template<typename T>
void lpaggreg::Tradeoff<T>::operator/=(lpaggreg::Tradeoff<T> &tradeoff)
{
    quality/=tradeoff.quality;
    value/=tradeoff.value;
}

template<typename U>
lpaggreg::tradeoff<U> operator+(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return lpaggreg::tradeoff<U>(tradeoff1.value+tradeoff2.value, tradeoff1.quality+tradeoff2.quality);
}

template<typename U>
lpaggreg::tradeoff<U> operator-(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return lpaggreg::tradeoff<U>(tradeoff1.value-tradeoff2.value, tradeoff1.quality-tradeoff2.quality);
}

template<typename U>
lpaggreg::tradeoff<U> operator*(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return lpaggreg::tradeoff<U>(tradeoff1.value*tradeoff2.value, tradeoff1.quality*tradeoff2.quality);
}

template<typename U>
lpaggreg::tradeoff<U> operator/(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return lpaggreg::tradeoff<U>(tradeoff1.value/tradeoff2.value, tradeoff1.quality/tradeoff2.quality);
}

template<typename U>
bool operator==(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return tradeoff1.value==tradeoff2.value;

}

template<typename U>
bool operator!=(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return !(tradeoff1.value==tradeoff2.value);
}

template<typename U>
bool operator>(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return (tradeoff1.value>tradeoff2.value||(tradeoff1.value==tradeoff2.value)&&
            (tradeoff1.quality.getGain()>tradeoff2.quality.getGain()||
            (tradeoff1.quality.getGain()==tradeoff2.quality.getGain()&&
             tradeoff1.quality.getLoss()<tradeoff2.quality.getLoss()));
}

template<typename U>
bool operator<=(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return !(tradeoff1>tradeoff2);
}

template<typename U>
bool operator<(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return !(tradeoff1>tradeoff2||tradeoff1==tradeoff2);
}

template<typename U>
bool operator>=(lpaggreg::tradeoff<U> &tradeoff1, lpaggreg::tradeoff<U> &tradeoff2)
{
    return !(tradeoff1<tradeoff2);
}

template class lpaggreg::Tradeoff<lp_quality_type>;
