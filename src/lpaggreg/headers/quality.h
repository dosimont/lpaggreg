#ifndef QUALITY_H
#define QUALITY_H

#include <cmath>
#include <algorithm>
#include "lpglobal.h"

namespace lpaggreg{

    template<typename T> class Quality
    {
    private:

        /*Gain*/
        T gain;

        /*Loss*/
        T loss;

    public:

        /*Constructor, initialize gain and loss with value 0*/
        Quality();

        Quality(Quality &quality);

        /*Constructor with parameters*/
        Quality(T gain, T loss);

        /*Destructor*/
        virtual ~Quality();

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

        void operator+=(Quality<T> &quality);
        void operator-=(Quality<T> &quality);
        void operator*=(Quality<T> &quality);
        void operator/=(Quality<T> &quality);

        void operator+=(Quality<T> *quality);
        void operator-=(Quality<T> *quality);
        void operator*=(Quality<T> *quality);
        void operator/=(Quality<T> *quality);

        template<typename U>
        friend Quality<U> operator+(Quality<U> &quality1, Quality<U> &quality2);
        template<typename U>
        friend Quality<U> operator-(Quality<U> &quality1, Quality<U> &quality2);
        template<typename U>
        friend Quality<U> operator*(Quality<U> &quality1, Quality<U> &quality2);
        template<typename U>
        friend Quality<U> operator/(Quality<U> &quality1, Quality<U> &quality2);
        template<typename U>
        friend bool operator==(Quality<U> &quality1, Quality<U> &quality2);
        template<typename U>
        friend bool operator!=(Quality<U> &quality1, Quality<U> &quality2);
    };

}



#endif // QUALITY_H
