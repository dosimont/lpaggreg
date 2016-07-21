#include "quality.h"

lpaggreg::Quality::Quality():gain(0),loss(0)
{

}

lpaggreg::Quality::Quality(lp_quality_typegain, lp_quality_typeloss):gain(gain),loss(loss)
{

}

lpaggreg::Quality::Quality(Quality &quality):gain(quality.getGain()), loss(quality.getLoss())
{

}

lp_quality_typelpaggreg::Quality::getGain() const
{
    return gain;
}

void lpaggreg::Quality::setGain(lp_quality_typegain)
{
    this->gain=gain;
}

lp_quality_typelpaggreg::Quality::getLoss() const
{
    return loss;
}

void lpaggreg::Quality::setLoss(lp_quality_typeloss)
{
    this->loss=loss;
}

void lpaggreg::Quality::addToGain(lp_quality_typegain)
{
    this->gain+=gain;
}

void lpaggreg::Quality::addToLoss(lp_quality_typeloss)
{
    this->loss+=loss;
}

void lpaggreg::Quality::operator+=(lpaggreg::Quality &quality)
{
    gain+=quality.gain;
    loss+=quality.loss;
}

void lpaggreg::Quality::operator-=(lpaggreg::Quality &quality)
{
    gain-=quality.gain;
    loss-=quality.loss;
}

void lpaggreg::Quality::operator*=(lpaggreg::Quality &quality)
{
    gain*=quality.gain;
    loss*=quality.loss;
}

void lpaggreg::Quality::operator/=(lpaggreg::Quality &quality)
{
    gain/=quality.gain;
    loss/=quality.loss;
}

void lpaggreg::Quality::operator+=(lpaggreg::Quality* quality)
{
    gain+=quality->gain;
    loss+=quality->loss;
}

void lpaggreg::Quality::operator-=(lpaggreg::Quality* quality)
{
    gain-=quality->gain;
    loss-=quality->loss;
}

void lpaggreg::Quality::operator*=(lpaggreg::Quality* quality)
{
    gain*=quality->gain;
    loss*=quality->loss;
}

void lpaggreg::Quality::operator/=(lpaggreg::Quality* quality)
{
    gain/=quality->gain;
    loss/=quality->loss;
}

lpaggreg::Quality operator+(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return lpaggreg::Quality(quality1.gain+quality2.gain, quality1.loss+quality2.loss);
}

lpaggreg::Quality operator-(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return lpaggreg::Quality(quality1.gain-quality2.gain, quality1.loss-quality2.loss);
}

lpaggreg::Quality operator*(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return lpaggreg::Quality(quality1.gain*quality2.gain, quality1.loss*quality2.loss);
}

lpaggreg::Quality operator/(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return lpaggreg::Quality(quality1.gain/quality2.gain, quality1.loss/quality2.loss);
}

bool operator==(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    lp_quality_type precision=std::max(quality1.gain+quality2.gain,quality1.loss+quality2.gloss)/2*LP_PRECISION;
    return (quality1.gain||quality2.gain&&quality1.loss||quality2.loss)||
            ((std::abs(quality1.gain-quality2.gain)<precision)&&
            (std::abs(quality1.gain-quality2.gain)<precision));
}

bool operator!=(lpaggreg::Quality &quality1, lpaggreg::Quality &quality2)
{
    return !(quality1==quality2);
}
