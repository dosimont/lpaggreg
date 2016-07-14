#include "tradeoff.h"


template<typename T>
T lpaggreg::Tradeoff<T>::getValue() const
{
    return value;
}

template<typename T>
void lpaggreg::Tradeoff<T>::computePIC(float p)
{
    value=(p*quality->getGain())+((p-1)*quality->getLoss());
}

template<typename T>
void lpaggreg::Tradeoff<T>::set(shared_ptr<lpaggreg::Quality<T> > quality, float p)
{
    this->quality=quality;
    computePIC(p);
}

template<typename T>
shared_ptr<lpaggreg::Quality<T> > lpaggreg::Tradeoff<T>::getQuality() const
{
    return quality;
}

template<typename T>
lpaggreg::Tradeoff<T>::Tradeoff()
{

}

template<typename T>
lpaggreg::Tradeoff<T>::Tradeoff(Tradeoff<T> &tradeoff):value(tradeoff.getValue()), quality(tradeoff.getQuality())
{

}

template<typename T>
lpaggreg::Tradeoff<T>::Tradeoff(T value, shared_ptr<lpaggreg::Quality<T> > quality):value(value), quality(quality)
{
}

template<typename T>
lpaggreg::Tradeoff<T>::Tradeoff(shared_ptr<lpaggreg::Quality<T> > quality,float p):quality(quality)
{
    computePIC(p);
}

template<typename T>
lpaggreg::Tradeoff<T>::Tradeoff(shared_ptr<lpaggreg::Quality<T> > quality):quality(quality)
{
    value=0;
}

template<typename T>
void lpaggreg::Tradeoff<T>::operator+=(lpaggreg::Tradeoff<T> &tradeoff)
{
    *quality+=*(tradeoff.quality);
    value+=tradeoff.value;
}

template<typename T>
void lpaggreg::Tradeoff<T>::operator-=(lpaggreg::Tradeoff<T> &tradeoff)
{
    *quality-=*(tradeoff.quality);
    value-=tradeoff.value;
}

template<typename T>
void lpaggreg::Tradeoff<T>::operator*=(lpaggreg::Tradeoff<T> &tradeoff)
{
    *quality*=*(tradeoff.quality);
    value*=tradeoff.value;
}

template<typename T>
void lpaggreg::Tradeoff<T>::operator/=(lpaggreg::Tradeoff<T> &tradeoff)
{
    *quality/=*(tradeoff.quality);
    value/=tradeoff.value;
}

template<typename T>
lpaggreg::Tradeoff<T> operator+(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return lpaggreg::Tradeoff<T>(tradeoff1.getValue()+tradeoff2.getValue(), tradeoff1.getQuality()+tradeoff2.getQuality());
}

template<typename T>
lpaggreg::Tradeoff<T> operator-(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return lpaggreg::Tradeoff<T>(tradeoff1.getValue()-tradeoff2.getValue(), tradeoff1.getQuality()-tradeoff2.getQuality());
}

template<typename T>
lpaggreg::Tradeoff<T> operator*(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return lpaggreg::Tradeoff<T>(tradeoff1.getValue()*tradeoff2.getValue(), tradeoff1.getQuality()*tradeoff2.getQuality());
}

template<typename T>
lpaggreg::Tradeoff<T> operator/(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return lpaggreg::Tradeoff<T>(tradeoff1.getValue()/tradeoff2.getValue(), tradeoff1.getQuality()/tradeoff2.getQuality());
}

template<typename T>
bool operator==(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return tradeoff1.getValue()==tradeoff2.getValue();

}

template<typename T>
bool operator!=(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return !(tradeoff1.getValue()==tradeoff2.getValue());
}

template<typename T>
bool operator>(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return (tradeoff1.getValue()>tradeoff2.getValue()||(tradeoff1.getValue()==tradeoff2.getValue())&&
            (tradeoff1.getQuality().getGain()>tradeoff2.getQuality().getGain()||
            (tradeoff1.getQuality().getGain()==tradeoff2.getQuality().getGain()&&
             tradeoff1.getQuality().getLoss()<tradeoff2.getQuality().getLoss())));
}

template<typename T>
bool operator<=(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return !(tradeoff1>tradeoff2);
}

template<typename T>
bool operator<(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return !(tradeoff1>tradeoff2||tradeoff1==tradeoff2);
}

template<typename T>
bool operator>=(lpaggreg::Tradeoff<T> &tradeoff1, lpaggreg::Tradeoff<T> &tradeoff2)
{
    return !(tradeoff1<tradeoff2);
}

template class lpaggreg::Tradeoff<lp_quality_type>;
