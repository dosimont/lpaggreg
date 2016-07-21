#ifndef TRADEOFF_H
#define TRADEOFF_H

#include <memory>
#include "quality.h"

using namespace std;

namespace lpaggreg{

    class Tradeoff
    {

    private:

        shared_ptr<Quality> quality;
        T value;

    public:
        Tradeoff();
        Tradeoff(Tradeoff &tradeoff);
        Tradeoff(shared_ptr<Quality> quality);
        Tradeoff(T value, shared_ptr<Quality> quality);
        Tradeoff(shared_ptr<Quality> quality, float p);

        void computePIC(float p);

        void operator+=(Tradeoff &tradeoff);
        void operator-=(Tradeoff &tradeoff);
        void operator*=(Tradeoff &tradeoff);
        void operator/=(Tradeoff &tradeoff);

        T getValue() const;

        void set(shared_ptr<Quality> quality, float p);

        shared_ptr<Quality> getQuality() const;
};

Tradeoff operator+(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
Tradeoff operator-(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
Tradeoff operator*(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
Tradeoff operator/(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
bool operator==(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
bool operator!=(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
bool operator<(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
bool operator>(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
bool operator<=(Tradeoff &tradeoff1, Tradeoff &tradeoff2);
bool operator>=(Tradeoff &tradeoff1, Tradeoff &tradeoff2);

}

#endif // TRADEOFF_H
