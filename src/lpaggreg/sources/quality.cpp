#include "quality.h"

lpaggreg::Quality::Quality():gain(0),loss(0)
{

}

lpaggreg::Quality::Quality(lp_quality_type gain, lp_quality_type loss):gain(gain),loss(loss)
{

}

lp_quality_type lpaggreg::Quality::getGain() const
{
    return gain;
}

void lpaggreg::Quality::setGain(lp_quality_type gain)
{
    this->gain=gain;
}

lp_quality_type lpaggreg::Quality::getLoss() const
{
    return loss;
}

void lpaggreg::Quality::setLoss(lp_quality_type loss)
{
    this->loss=loss;
}

void lpaggreg::Quality::addToGain(lp_quality_type gain)
{
    this->gain+=gain;
}

void lpaggreg::Quality::addToLoss(lp_quality_type loss)
{
    this->loss+=loss;
}

void lpaggreg::Quality::operator+=(lpaggreg::Quality &quality)
{
    gain+=quality.getGain();
    loss+=quality.getLoss();
}

void lpaggreg::Quality::operator-=(lpaggreg::Quality &quality)
{
    gain-=quality.getGain();
    loss-=quality.getLoss();
}

void lpaggreg::Quality::operator*=(lpaggreg::Quality &quality)
{
    gain*=quality.getGain();
    loss*=quality.getLoss();
}

void lpaggreg::Quality::operator/=(lpaggreg::Quality &quality)
{
    gain/=quality.getGain();
    loss/=quality.getLoss();
}

lpaggreg::Quality lpaggreg::operator+(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return lpaggreg::Quality(quality1.getGain()+quality2.getGain(), quality1.getLoss()+quality2.getLoss());
}

lpaggreg::Quality lpaggreg::operator-(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return lpaggreg::Quality(quality1.getGain()-quality2.getGain(), quality1.getLoss()-quality2.getLoss());
}

lpaggreg::Quality lpaggreg::operator*(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return lpaggreg::Quality(quality1.getGain()*quality2.getGain(), quality1.getLoss()*quality2.getLoss());
}

lpaggreg::Quality lpaggreg::operator/(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return lpaggreg::Quality(quality1.getGain()/quality2.getGain(), quality1.getLoss()/quality2.getLoss());
}

bool lpaggreg::operator==(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    lp_quality_type precision=std::max(quality1.getGain()+quality2.getGain(),quality1.getLoss()+quality2.getLoss())/2*LP_PRECISION;
    return (quality1.getGain()==quality2.getGain()&&quality1.getLoss()==quality2.getLoss())||
            ((std::abs(quality1.getGain()-quality2.getGain())<precision)&&
            (std::abs(quality1.getGain()-quality2.getGain())<precision));
}

bool lpaggreg::operator!=(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return !(quality1==quality2);
}

std::ostream &lpaggreg::operator<<(std::ostream& stream, lpaggreg::Quality &quality)
{
    stream<<"("<<quality.getGain()<<","<<quality.getLoss()<<")";
    return stream;
}
