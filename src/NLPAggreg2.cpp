/*
 * NLPAggreg2.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#include "NLPAggreg2.h"

NLPAggreg2::NLPAggreg2() :
		NLPAggreg() {
}

NLPAggreg2::NLPAggreg2(int id, const vector<double>& values) :
		NLPAggreg(0, id) {
	setValues(values);
}

NLPAggreg2::NLPAggreg2(NLPAggreg2* parent, int id, const vector<double>& values) :
		NLPAggreg(parent, id) {
	setValues(values);
}

NLPAggreg2::~NLPAggreg2() {
	// TODO Auto-generated destructor stub
}

const vector<double>& NLPAggreg2::getValues() const {
	return values;
}

void NLPAggreg2::setValues(const vector<double>& values) {
	this->values = values;
}

void NLPAggreg2::computeQualities(bool normalization) {
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

void NLPAggreg2::computeQuality() {
	for (unsigned int i = 0; i < this->values.size(); i++)
		computeQuality_Vector(i);
}

void NLPAggreg2::computeQuality_Vector(int index) {
	if (!hasChild()) {
		entSum = entropyReduction(this->values[index], 0);
		size = 1;
		eval->incrQCounter(2);
	}
	else {
		this->values[index] = 0;
		entSum = 0;
		size = 0;
		eval->incrQCounter(3);
		for CHILDS {
			static_cast<NLPAggreg2*>(CHILD)->computeQuality_Vector(index);
			this->values[index]+=static_cast<NLPAggreg2*>(CHILD)->getValues()[index];
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		if (index == 0) {
			quality->setGain(0);
			quality->setLoss(0);
		}
		quality->addToGain(entropyReduction(this->values[index], entSum));
		quality->addToLoss(divergence(size, this->values[index], entSum));
		eval->incrQCounter(2);
	}
}

