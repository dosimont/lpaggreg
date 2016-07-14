#ifndef TRADEOFF_H
#define TRADEOFF_H

#include <memory>
#include "quality.h"

using namespace std;

namespace lpaggreg{

    template<typename T> class Tradeoff;

    template<typename T> class Tradeoff
    {

    private:

        shared_ptr<Quality<T> > quality;
        T value;

    public:
        Tradeoff();
        Tradeoff(Tradeoff<T> &tradeoff);
        Tradeoff(shared_ptr<Quality<T> > quality);
        Tradeoff(T value, shared_ptr<Quality<T> > quality);
        Tradeoff(shared_ptr<Quality<T> > quality, float p);

        void computePIC(float p);

        void operator+=(Tradeoff<T> &tradeoff);
        void operator-=(Tradeoff<T> &tradeoff);
        void operator*=(Tradeoff<T> &tradeoff);
        void operator/=(Tradeoff<T> &tradeoff);

        T getValue() const;

        void set(shared_ptr<Quality<T> > quality, float p);

        shared_ptr<Quality<T> > getQuality() const;
};

template<typename T>
Tradeoff<T> operator+(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
Tradeoff<T> operator-(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
Tradeoff<T> operator*(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
Tradeoff<T> operator/(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
bool operator==(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
bool operator!=(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
bool operator<(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
bool operator>(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
bool operator<=(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);
template<typename T>
bool operator>=(Tradeoff<T> &tradeoff1, Tradeoff<T> &tradeoff2);

}

#endif // TRADEOFF_H
