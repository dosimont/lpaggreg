#include "lpquality.h"

template<typename T>
LPQuality<T>::LPQuality():gain(0),loss(0)
{

}

template<typename T>
LPQuality<T>::LPQuality(T gain, T loss):gain(gain),loss(loss)
{

}

template<typename T>
T LPQuality<T>::getGain() const
{
    return gain;
}

template<typename T>
void LPQuality<T>::setGain(T gain)
{
    this->gain=gain;
}

template<typename T>
T LPQuality<T>::getLoss() const
{
    return loss;
}

template<typename T>
void LPQuality<T>::setLoss(T loss)
{
    this->loss=loss;
}

template<typename T>
void LPQuality<T>::addToGain(T gain)
{
    this->gain+=gain;
}

template<typename T>
void LPQuality<T>::addToLoss(T loss)
{
    this->loss+=loss;
}

template<typename T>
void LPQuality<T>::operator+=(LPQuality<T> &quality)
{
    gain+=quality.gain;
    loss+=quality.loss;
}

template<typename T>
void LPQuality<T>::operator-=(LPQuality<T> &quality)
{
    gain-=quality.gain;
    loss-=quality.loss;
}

template<typename T>
void LPQuality<T>::operator*=(LPQuality<T> &quality)
{
    gain*=quality.gain;
    loss*=quality.loss;
}

template<typename T>
void LPQuality<T>::operator/=(LPQuality<T> &quality)
{
    gain/=quality.gain;
    loss/=quality.loss;
}

template<typename U>
LPQuality<U> operator+(LPQuality<U> &quality1, LPQuality<U> &quality2)
{
    return LPQuality<U>(quality1.gain+quality2.gain, quality1.loss+quality2.loss);
}

template<typename U>
LPQuality<U> operator-(LPQuality<U> &quality1, LPQuality<U> &quality2)
{
    return LPQuality<U>(quality1.gain-quality2.gain, quality1.loss-quality2.loss);
}

template<typename U>
LPQuality<U> operator*(LPQuality<U> &quality1, LPQuality<U> &quality2)
{
    return LPQuality<U>(quality1.gain*quality2.gain, quality1.loss*quality2.loss);
}

template<typename U>
LPQuality<U> operator/(LPQuality<U> &quality1, LPQuality<U> &quality2)
{
    return LPQuality<U>(quality1.gain/quality2.gain, quality1.loss/quality2.loss);
}

template<typename U>
void operator==(LPQuality<U> &quality1, LPQuality<U> &quality2)
{
    U precision=std::max(quality1.gain+quality2.gain,quality1.loss+quality2.gloss)/2*LP_PRECISION;
    return (quality1.gain||quality2.gain&&quality1.loss||quality2.loss)||
            ((std::abs(quality1.gain-quality2.gain)<precision)&&
            (std::abs(quality1.gain-quality2.gain)<precision));
}

template<typename U>
void operator!=(LPQuality<U> &quality1, LPQuality<U> &quality2)
{
    return !(quality1==quality2);
}

template class LPQuality<double>;
template class LPQuality<long double>;
