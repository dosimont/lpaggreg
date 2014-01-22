/*
 * DLPAggreg2.cpp
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg1.h"

DLPAggreg1::DLPAggreg1() :
		DLPAggreg(), values(0), sumValue(0), microInfo(0) {
}

DLPAggreg1::DLPAggreg1(int id) :
		DLPAggreg(id), values(0), sumValue(0), microInfo(0) {
}

DLPAggreg1::DLPAggreg1(int id, const vector<double>& values) :
		DLPAggreg(0, id), values(values), sumValue(0), microInfo(0) {
}

DLPAggreg1::DLPAggreg1(DLPAggreg1* parent, int id, const vector<double>& values) :
		DLPAggreg(parent, id) {
	setValues(values);
}

DLPAggreg1::~DLPAggreg1() {
	for (int i=valueSize-1; i>=0; i--) {
		delete sumValue[i];
		delete microInfo[i];
	}
	delete sumValue;
	delete microInfo;
}

const vector<double>& DLPAggreg1::getValues() const {
	return values;
}

void DLPAggreg1::computeQualities() {
	if (hasChild()) {
		nodeSize = 0;
		eval->incrQCounter();
		for DCHILDS {
			DCHILD1->computeQualities();
			nodeSize+=DCHILD1->getNodeSize();
			eval->incrQCounter();
		}
		valueSize = static_cast<DLPAggreg1*>(childNodes[0])->getValueSize();
		eval->incrQCounter();
	}
	else {
		valueSize = values.size();
		nodeSize = 1;
		eval->incrQCounter(2);
	}
	sumValue = new double*[valueSize];
	microInfo = new double*[valueSize];
	for (int i = 0; i < valueSize; i++) {
		sumValue[i] = new double[valueSize];
		microInfo[i] = new double[valueSize];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < valueSize; j++){
			qualities[i].push_back(new Quality());
			eval->incrQCounter();
		}
	}
	if (!hasChild()) {
		for (int i = 0; i < valueSize; i++) {
			sumValue[i][0] = values[i];
			microInfo[i][0] = entropyReduction(values[i], 0);
			eval->incrQCounter(2);
		}
		for (int j = 1; j < valueSize; j++) {
			for (int i = 0; i < valueSize - j; i++) {
				sumValue[i][j] = sumValue[i][j - 1] + sumValue[i + j][0];
				microInfo[i][j] = microInfo[i][j - 1] + microInfo[i + j][0];
				qualities[i][j]->setGain(
						entropyReduction(sumValue[i][j], microInfo[i][j]));
				qualities[i][j]->setLoss(
						divergence(j + 1, sumValue[i][j], microInfo[i][j]));
				eval->incrQCounter(4);
			}
		}
	}
	else {
		for (int j = 0; j < valueSize; j++) {
			for (int i = 0; i < valueSize - j; i++) {
				sumValue[i][j] = 0;
				microInfo[i][j] = 0;
				eval->incrQCounter(2);
				for DCHILDS {
					sumValue[i][j]+=DCHILD1->getSumValue()[i][j];
					microInfo[i][j]+=DCHILD1->getMicroInfo()[i][j];
					eval->incrQCounter(2);
				}
				qualities[i][j]->setGain(
						entropyReduction(sumValue[i][j], microInfo[i][j]));
				qualities[i][j]->setLoss(
						divergence((j + 1)*nodeSize, sumValue[i][j],
								microInfo[i][j]));
				eval->incrQCounter(2);
			}
		}
	}
}

void DLPAggreg1::computeQualities(bool normalization) {
	if (!hasParent()) {
		setEval(new Eval);
		eval->resetQCounter();
		eval->startQTimer();
		computeQualities();
		if (normalization)
			normalize();
		eval->stopQTimer();
	}
}

double** DLPAggreg1::getMicroInfo() const {
	return microInfo;
}

double** DLPAggreg1::getSumValue() const {
	return sumValue;
}

void DLPAggreg1::setValues(const vector<double>& values) {
	this->values = values;
}

