#ifndef QUALITY_H
#define QUALITY_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>
#include "lpglobal.h"

using namespace std;

namespace lpaggreg{

    class Quality
    {
    private:

        /*Gain*/
        lp_quality_type gain;

        /*Loss*/
        lp_quality_type loss;

    public:

        /*Constructor, initialize gain and loss with value 0*/
        Quality();

        /*Constructor with parameters*/
        Quality(lp_quality_type gain, lp_quality_type loss);

        /*Gain getter*/
        lp_quality_type getGain() const;

        /*Gain setter*/
        void setGain(lp_quality_type gain);

        /*Loss getter*/
        lp_quality_type getLoss() const;

        /*Loss setter*/
        void setLoss(lp_quality_type loss);

        /*Add a value to currenlp_quality_type gain*/
        void addToGain(lp_quality_type gain);

        /*Add a value to currenlp_quality_type loss*/
        void addToLoss(lp_quality_type loss);

        /*Override operators*/

        void operator+=(Quality &quality);
        void operator-=(Quality &quality);
        void operator*=(Quality &quality);
        void operator/=(Quality &quality);

    };

    Quality operator+(Quality &quality1, Quality &quality2);
    Quality operator-(Quality &quality1, Quality &quality2);
    Quality operator*(Quality &quality1, Quality &quality2);
    Quality operator/(Quality &quality1, Quality &quality2);
    bool operator==(Quality &quality1, Quality &quality2);
    bool operator!=(Quality &quality1, Quality &quality2);
    ostream& operator<<(std::ostream& stream, Quality &quality);


}



#endif // QUALITY_H
