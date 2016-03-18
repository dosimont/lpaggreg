#ifndef LPQUALITY_H
#define LPQUALITY_H


class LPQuality
{
private:

    /*Gain*/
    double gain;

    /*Loss*/
    double loss;

public:

    /*Constructor, initialize gain and loss with value 0*/
    LPQuality();

    /*Constructor with parameters*/
    LPQuality(double gain, double loss);

    /*Destructor*/
    virtual ~LPQuality();

    /*Gain getter*/
    double getGain() const;

    /*Gain setter*/
    void setGain(double gain);

    /*Loss getter*/
    double getLoss() const;

    /*Loss setter*/
    void setLoss(double loss);

    /*Add a value to current gain*/
    void addToGain(double gain);

    /*Add a value to current loss*/
    void addToLoss(double loss);

    friend bool operator== (LPQuality &quality1, LPQuality &quality2);
    friend bool operator+= (LPQuality &quality1, LPQuality &quality2);
    friend bool operator-= (LPQuality &quality1, LPQuality &quality2);
    friend bool operator/= (LPQuality &quality1, LPQuality &quality2);
    friend bool operator*= (LPQuality &quality1, LPQuality &quality2);
    friend bool operator!= (LPQuality &quality1, LPQuality &quality2);
    friend bool operator> (LPQuality &quality1, LPQuality &quality2);
    friend bool operator<= (LPQuality &quality1, LPQuality &quality2);
    friend bool operator< (LPQuality &quality1, LPQuality &quality2);
    friend bool operator>= (LPQuality &quality1, LPQuality &quality2);
};

#endif // LPQUALITY_H
