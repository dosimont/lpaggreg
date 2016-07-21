#include "tradeoff.h"



T lpaggreg::Tradeoff::getValue() const
{
    return value;
}


void lpaggreg::Tradeoff::computePIC(float p)
{
    value=(p*quality->getGain())+((p-1)*quality->getLoss());
}


void lpaggreg::Tradeoff::set(shared_ptr<lpaggreg::Quality> quality, float p)
{
    this->quality=quality;
    computePIC(p);
}


shared_ptr<lpaggreg::Quality> lpaggreg::Tradeoff::getQuality() const
{
    return quality;
}


lpaggreg::Tradeoff::Tradeoff()
{

}


lpaggreg::Tradeoff::Tradeoff(Tradeoff &tradeoff):value(tradeoff.getValue()), quality(tradeoff.getQuality())
{

}


lpaggreg::Tradeoff::Tradeoff(lp_quality_type value, shared_ptr<lpaggreg::Quality> quality):value(value), quality(quality)
{
}


lpaggreg::Tradeoff::Tradeoff(shared_ptr<lpaggreg::Quality> quality,float p):quality(quality)
{
    computePIC(p);
}


lpaggreg::Tradeoff::Tradeoff(shared_ptr<lpaggreg::Quality> quality):quality(quality)
{
    value=0;
}


void lpaggreg::Tradeoff::operator+=(lpaggreg::Tradeoff &tradeoff)
{
    *quality+=*(tradeoff.quality);
    value+=tradeoff.value;
}


void lpaggreg::Tradeoff::operator-=(lpaggreg::Tradeoff &tradeoff)
{
    *quality-=*(tradeoff.quality);
    value-=tradeoff.value;
}


void lpaggreg::Tradeoff::operator*=(lpaggreg::Tradeoff &tradeoff)
{
    *quality*=*(tradeoff.quality);
    value*=tradeoff.value;
}


void lpaggreg::Tradeoff::operator/=(lpaggreg::Tradeoff &tradeoff)
{
    *quality/=*(tradeoff.quality);
    value/=tradeoff.value;
}


lpaggreg::Tradeoff operator+(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return lpaggreg::Tradeoff(tradeoff1.getValue()+tradeoff2.getValue(), tradeoff1.getQuality()+tradeoff2.getQuality());
}


lpaggreg::Tradeoff operator-(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return lpaggreg::Tradeoff(tradeoff1.getValue()-tradeoff2.getValue(), tradeoff1.getQuality()-tradeoff2.getQuality());
}


lpaggreg::Tradeoff operator*(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return lpaggreg::Tradeoff(tradeoff1.getValue()*tradeoff2.getValue(), tradeoff1.getQuality()*tradeoff2.getQuality());
}


lpaggreg::Tradeoff operator/(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return lpaggreg::Tradeoff(tradeoff1.getValue()/tradeoff2.getValue(), tradeoff1.getQuality()/tradeoff2.getQuality());
}


bool lpaggreg::operator==(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return tradeoff1.getValue()==tradeoff2.getValue();

}


bool lpaggreg::operator!=(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return !(tradeoff1.getValue()==tradeoff2.getValue());
}


bool lpaggreg::operator>(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return (tradeoff1.getValue()>tradeoff2.getValue()||(tradeoff1.getValue()==tradeoff2.getValue())&&
            (tradeoff1.getQuality().getGain()>tradeoff2.getQuality().getGain()||
            (tradeoff1.getQuality().getGain()==tradeoff2.getQuality().getGain()&&
             tradeoff1.getQuality().getLoss()<tradeoff2.getQuality().getLoss())));
}


bool lpaggreg::operator<=(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return !(tradeoff1>tradeoff2);
}


bool lpaggreg::operator<(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return !(tradeoff1>tradeoff2||tradeoff1==tradeoff2);
}


bool lpaggreg::operator>=(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    return !(tradeoff1<tradeoff2);
}
