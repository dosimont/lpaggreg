#ifndef TRADEOFF_H
#define TRADEOFF_H

#include "quality.h"

namespace lpaggreg{

    template<typename T> class Tradeoff
    {

    private:

        Quality<T> quality;
        T value;

    public:
        Tradeoff(Tradeoff<T> &tradeoff);
        Tradeoff(Quality<T> quality);
        Tradeoff(T value, Quality<T> quality);
        Tradeoff(Quality<T> quality, T P);

        void computePIC(T p);

        void operator+=(Tradeoff<T> &Tradeoff);
        void operator-=(Tradeoff<T> &Tradeoff);
        void operator*=(Tradeoff<T> &Tradeoff);
        void operator/=(Tradeoff<T> &Tradeoff);


        template<typename U>
        friend Tradeoff<U> operator+(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        template<typename U>
        friend Tradeoff<U> operator-(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        template<typename U>
        friend Tradeoff<U> operator*(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        template<typename U>
        friend Tradeoff<U> operator/(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        template<typename U>
        friend bool operator==(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        template<typename U>
        friend bool operator!=(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        template<typename U>
        friend bool operator<(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        template<typename U>
        friend bool operator>(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        friend bool operator<=(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);
        template<typename U>
        friend bool operator>=(Tradeoff<U> &Tradeoff1, Tradeoff<U> &Tradeoff2);

        T getValue() const;
        Quality<T> getQuality() const;
};

}

#endif // TRADEOFF_H
