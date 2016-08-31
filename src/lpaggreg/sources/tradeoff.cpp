#include "tradeoff.h"

void lpaggreg::Tradeoff::computePIC(float p)
{
    value=(p*quality->getGain())-((1-p)*quality->getLoss());
}


void lpaggreg::Tradeoff::set(shared_ptr<lpaggreg::Quality> quality, float p)
{
    this->quality=shared_ptr<Quality>(new Quality(quality->getGain(), quality->getLoss()));
    computePIC(p);
}


shared_ptr<lpaggreg::Quality> lpaggreg::Tradeoff::getQuality() const
{
    return quality;
}


lp_quality_type lpaggreg::Tradeoff::getValue() const
{
    return value;
}

lpaggreg::Tradeoff::Tradeoff()
{
    this->quality=shared_ptr<Quality>(new Quality());
    value=0;
}

/*lpaggreg::Tradeoff::Tradeoff(Tradeoff &tradeoff):value(tradeoff.getValue()), quality(tradeoff.getQuality())
{

}*/


lpaggreg::Tradeoff::Tradeoff(lp_quality_type value, shared_ptr<lpaggreg::Quality> quality):value(value)
{
    this->quality=shared_ptr<Quality>(new Quality(quality->getGain(), quality->getLoss()));
}


lpaggreg::Tradeoff::Tradeoff(shared_ptr<lpaggreg::Quality> quality,float p)
{
    this->quality=shared_ptr<Quality>(new Quality(quality->getGain(), quality->getLoss()));
    computePIC(p);
}


lpaggreg::Tradeoff::Tradeoff(shared_ptr<lpaggreg::Quality> quality)
{
    this->quality=shared_ptr<Quality>(new Quality(quality->getGain(), quality->getLoss()));
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
    lp_quality_type value=tradeoff1.getValue()+tradeoff2.getValue();
    shared_ptr<lpaggreg::Quality> quality=shared_ptr<lpaggreg::Quality>(new lpaggreg::Quality());
    *quality+=*(tradeoff1.getQuality());
    *quality+=*(tradeoff2.getQuality());
    return lpaggreg::Tradeoff(value, quality);
}


lpaggreg::Tradeoff operator-(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    lp_quality_type value=tradeoff1.getValue()-tradeoff2.getValue();
    shared_ptr<lpaggreg::Quality> quality=shared_ptr<lpaggreg::Quality>(new lpaggreg::Quality());
    *quality+=*(tradeoff1.getQuality());
    *quality-=*(tradeoff2.getQuality());
    return lpaggreg::Tradeoff(value, quality);
}


lpaggreg::Tradeoff operator*(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    lp_quality_type value=tradeoff1.getValue()*tradeoff2.getValue();
    shared_ptr<lpaggreg::Quality> quality=shared_ptr<lpaggreg::Quality>(new lpaggreg::Quality());
    *quality+=*(tradeoff1.getQuality());
    *quality*=*(tradeoff2.getQuality());
    return lpaggreg::Tradeoff(value, quality);
}


lpaggreg::Tradeoff operator/(lpaggreg::Tradeoff &tradeoff1, lpaggreg::Tradeoff &tradeoff2)
{
    lp_quality_type value=tradeoff1.getValue()/tradeoff2.getValue();
    shared_ptr<lpaggreg::Quality> quality=shared_ptr<lpaggreg::Quality>(new lpaggreg::Quality());
    *quality+=*(tradeoff1.getQuality());
    *quality/=*(tradeoff2.getQuality());
    return lpaggreg::Tradeoff(value, quality);
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
            (tradeoff1.getQuality()->getGain()>tradeoff2.getQuality()->getGain()||
            (tradeoff1.getQuality()->getGain()==tradeoff2.getQuality()->getGain()&&
             tradeoff1.getQuality()->getLoss()<tradeoff2.getQuality()->getLoss())));
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
