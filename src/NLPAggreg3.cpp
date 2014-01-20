/*
 * NLPAggreg3.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#include "NLPAggreg3.h"

NLPAggreg3::NLPAggreg3() :
		NLPAggreg() {
}

NLPAggreg3::NLPAggreg3(int id, vector<vector<double> > values) :
		NLPAggreg(0, id) {
	setValues(values);
}

NLPAggreg3::NLPAggreg3(NLPAggreg3* parent, int id,
		vector<vector<double> > values) :
		NLPAggreg(parent, id) {
	setValues(values);
}

NLPAggreg3::~NLPAggreg3() {
	// TODO Auto-generated destructor stub
}

const vector<vector<double> >& NLPAggreg3::getValues() const {
	return values;
}

void NLPAggreg3::setValues(const vector<vector<double> >& values) {
	this->values = values;
}

void NLPAggreg3::computeQualities(bool normalization) {
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

void NLPAggreg3::computeQuality() {
	for (unsigned int i = 0; i < this->values.size(); i++)
		for (unsigned int j = 0; j < this->values[i].size(); j++)
			computeQuality_Matrix(i, j);
}

void NLPAggreg3::computeQuality_Matrix(int i, int j) {
	if (!hasChild()) {
		entSum = entropyReduction(this->values[i][j], 0);
		size = 1;
		eval->incrQCounter(2);
	}
	else {
		this->values[i][j] = 0;
		entSum = 0;
		size = 0;
		eval->incrQCounter(3);
		for CHILDS {
			static_cast<NLPAggreg3*>(CHILD)->computeQuality_Matrix(i, j);
			this->values[i][j]+=static_cast<NLPAggreg3*>(CHILD)->getValues()[i][j];
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		if (i == 0 && j == 0) {
			quality->setGain(0);
			quality->setLoss(0);
		}
		quality->addToGain(entropyReduction(this->values[i][j], entSum));
		quality->addToLoss(divergence(size, this->values[i][j], entSum));
		eval->incrQCounter(2);
	}
}

