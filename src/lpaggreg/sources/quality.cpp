#include "quality.h"

template<typename T>
lpaggreg::Quality<T>::Quality():gain(0),loss(0)
{

}

template<typename T>
lpaggreg::Quality<T>::Quality(T gain, T loss):gain(gain),loss(loss)
{

}

template<typename T>
lpaggreg::Quality<T>::Quality(Quality &quality):gain(quality.getGain()), loss(quality.getLoss())
{

}

template<typename T>
T lpaggreg::Quality<T>::getGain() const
{
    return gain;
}

template<typename T>
void lpaggreg::Quality<T>::setGain(T gain)
{
    this->gain=gain;
}

template<typename T>
T lpaggreg::Quality<T>::getLoss() const
{
    return loss;
}

template<typename T>
void lpaggreg::Quality<T>::setLoss(T loss)
{
    this->loss=loss;
}

template<typename T>
void lpaggreg::Quality<T>::addToGain(T gain)
{
    this->gain+=gain;
}

template<typename T>
void lpaggreg::Quality<T>::addToLoss(T loss)
{
    this->loss+=loss;
}

template<typename T>
void lpaggreg::Quality<T>::operator+=(lpaggreg::Quality<T> &quality)
{
    gain+=quality.gain;
    loss+=quality.loss;
}

template<typename T>
void lpaggreg::Quality<T>::operator-=(lpaggreg::Quality<T> &quality)
{
    gain-=quality.gain;
    loss-=quality.loss;
}

template<typename T>
void lpaggreg::Quality<T>::operator*=(lpaggreg::Quality<T> &quality)
{
    gain*=quality.gain;
    loss*=quality.loss;
}

template<typename T>
void lpaggreg::Quality<T>::operator/=(lpaggreg::Quality<T> &quality)
{
    gain/=quality.gain;
    loss/=quality.loss;
}

template<typename U>
lpaggreg::Quality<U> operator+(lpaggreg::Quality<U> &quality1, lpaggreg::Quality<U> &quality2)
{
    return lpaggreg::Quality<U>(quality1.gain+quality2.gain, quality1.loss+quality2.loss);
}

template<typename U>
lpaggreg::Quality<U> operator-(lpaggreg::Quality<U> &quality1, lpaggreg::Quality<U> &quality2)
{
    return lpaggreg::Quality<U>(quality1.gain-quality2.gain, quality1.loss-quality2.loss);
}

template<typename U>
lpaggreg::Quality<U> operator*(lpaggreg::Quality<U> &quality1, lpaggreg::Quality<U> &quality2)
{
    return lpaggreg::Quality<U>(quality1.gain*quality2.gain, quality1.loss*quality2.loss);
}

template<typename U>
lpaggreg::Quality<U> operator/(lpaggreg::Quality<U> &quality1, lpaggreg::Quality<U> &quality2)
{
    return lpaggreg::Quality<U>(quality1.gain/quality2.gain, quality1.loss/quality2.loss);
}

template<typename U>
bool operator==(lpaggreg::Quality<U> &quality1, lpaggreg::Quality<U> &quality2)
{
    U precision=std::max(quality1.gain+quality2.gain,quality1.loss+quality2.gloss)/2*LP_PRECISION;
    return (quality1.gain||quality2.gain&&quality1.loss||quality2.loss)||
            ((std::abs(quality1.gain-quality2.gain)<precision)&&
            (std::abs(quality1.gain-quality2.gain)<precision));
}

template<typename U>
bool operator!=(lpaggreg::Quality<U> &quality1, lpaggreg::Quality<U> &quality2)
{
    return !(quality1==quality2);
}

template class lpaggreg::Quality<lp_quality_type>;
