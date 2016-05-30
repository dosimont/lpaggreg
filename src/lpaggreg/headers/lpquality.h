#ifndef LPQUALITY_H
#define LPQUALITY_H

#include <cmath>
#include <algorithm>
#include "lpglobal.h"

template<typename T> class LPQuality
{
private:

    /*Gain*/
    T gain;

    /*Loss*/
    T loss;

public:

    /*Constructor, initialize gain and loss with value 0*/
    LPQuality();

    /*Constructor with parameters*/
    LPQuality(T gain, T loss);

    /*Destructor*/
    virtual ~LPQuality();

    /*Gain getter*/
    T getGain() const;

    /*Gain setter*/
    void setGain(T gain);

    /*Loss getter*/
    T getLoss() const;

    /*Loss setter*/
    void setLoss(T loss);

    /*Add a value to current gain*/
    void addToGain(T gain);

    /*Add a value to current loss*/
    void addToLoss(T loss);

    /*Override operators*/



    void operator+=(LPQuality<T> &quality);
    void operator-=(LPQuality<T> &quality);
    void operator*=(LPQuality<T> &quality);
    void operator/=(LPQuality<T> &quality);

    template<typename U>
    friend LPQuality<U> operator+(LPQuality<U> &quality1, LPQuality<U> &quality2);
    template<typename U>
    friend LPQuality<U> operator-(LPQuality<U> &quality1, LPQuality<U> &quality2);
    template<typename U>
    friend LPQuality<U> operator*(LPQuality<U> &quality1, LPQuality<U> &quality2);
    template<typename U>
    friend LPQuality<U> operator/(LPQuality<U> &quality1, LPQuality<U> &quality2);
    template<typename U>
    friend bool operator==(LPQuality<U> &quality1, LPQuality<U> &quality2);
    template<typename U>
    friend bool operator!=(LPQuality<U> &quality1, LPQuality<U> &quality2);
};



#endif // LPQUALITY_H
