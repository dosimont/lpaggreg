/*
 * NLPAggreg1.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#include "NLPAggreg1.h"

NLPAggreg1::NLPAggreg1(): NLPAggreg(){
	this->values=0;
}

double NLPAggreg1::getValues() const {
	return values;
}

void NLPAggreg1::setValues(double values) {
		this->values = values;
}

NLPAggreg1::NLPAggreg1(NLPAggreg1* parent, int id, double values): NLPAggreg(parent, id){
	setValues(values);
}

NLPAggreg1::NLPAggreg1(int id, double values): NLPAggreg(0, id){
	setValues(values);
}

NLPAggreg1::~NLPAggreg1() {
	// TODO Auto-generated destructor stub
}

void NLPAggreg1::computeQuality() {
	if (!hasChild()) {
		entSum = entropyReduction(this->values, 0.0);
		size = 1;
		eval->incrQCounter(2);
	}
	else {
		this->values = 0;
		entSum = 0;
		size = 0;
		eval->incrQCounter(3);
		for CHILDS {
			static_cast<NLPAggreg1*>(CHILD)->computeQuality();
			this->values+=static_cast<NLPAggreg1*>(CHILD)->getValues();
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		quality->setGain(entropyReduction(this->values, entSum));
		quality->setLoss(divergence(size, this->values, entSum));
		eval->incrQCounter(2);
	}
}


void NLPAggreg1::computeQualities(bool normalization) {
	if (!hasParent()) {
		setEval(new Eval);
		eval->resetQCounter();
		eval->startQTimer();
		computeQuality();
		if (normalization)
			normalize();
		eval->stopQTimer();
	}
}
