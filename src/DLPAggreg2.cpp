/*
 * DLPAggreg2.cpp
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg2.h"

DLPAggreg2::DLPAggreg2() :
		DLPAggreg(), values(0), sumValue(0), microInfo(0) {
}

DLPAggreg2::DLPAggreg2(int id) :
		DLPAggreg(id), values(0), sumValue(0), microInfo(0) {
}

DLPAggreg2::DLPAggreg2(int id, vector<double> values) :
		DLPAggreg(0, id), values(values), sumValue(0), microInfo(0) {
}

DLPAggreg2::DLPAggreg2(DLPAggreg2* parent, int id, vector<double> values) :
		DLPAggreg(parent, id) {
	setValues(values);
}

DLPAggreg2::~DLPAggreg2() {
	for (int i=valueSize-1; i>=0; i--) {
		delete sumValue[i];
		delete microInfo[i];
	}
	delete sumValue;
	delete microInfo;
}

const vector<double>& DLPAggreg2::getValues() const {
	return values;
}

void DLPAggreg2::computeQualities() {
	if (hasChild()) {
		nodeSize = 0;
		for DCHILDS {
			DCHILD2->computeQualities();
			nodeSize+=DCHILD2->getNodeSize();
		}
		valueSize = static_cast<DLPAggreg2*>(childNodes[0])->getValueSize();
	}
	else {
		valueSize = values.size();
		nodeSize = 1;
	}
	sumValue = new double*[valueSize];
	microInfo = new double*[valueSize];
	for (int i = 0; i < valueSize; i++) {
		sumValue[i] = new double[valueSize];
		microInfo[i] = new double[valueSize];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < valueSize; j++)
			qualities[i].push_back(new Quality());
	}
	if (!hasChild()) {
		for (int i = 0; i < valueSize; i++) {
			sumValue[i][0] = values[i];
			microInfo[i][0] = entropyReduction(values[i], 0);
		}
		for (int j = 1; j < valueSize; j++) {
			for (int i = 0; i < valueSize - j; i++) {
				sumValue[i][j] = sumValue[i][j - 1] + sumValue[i + j][0];
				microInfo[i][j] = microInfo[i][j - 1] + microInfo[i + j][0];
				qualities[i][j]->setGain(
						entropyReduction(sumValue[i][j], microInfo[i][j]));
				qualities[i][j]->setLoss(
						divergence(j + 1, sumValue[i][j], microInfo[i][j]));
			}
		}
	}
	else {
		for (int j = 0; j < valueSize; j++) {
			for (int i = 0; i < valueSize - j; i++) {
				sumValue[i][j] = 0;
				microInfo[i][j] = 0;
				for DCHILDS {
					sumValue[i][j]+=DCHILD2->getSumValue()[i][j];
					microInfo[i][j]+=DCHILD2->getMicroInfo()[i][j];
				}
				qualities[i][j]->setGain(
						entropyReduction(sumValue[i][j], microInfo[i][j]));
				qualities[i][j]->setLoss(
						divergence((j + 1)*nodeSize, sumValue[i][j],
								microInfo[i][j]));
			}
		}
	}
}

void DLPAggreg2::computeQualities(bool normalization) {
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

double** DLPAggreg2::getMicroInfo() const {
	return microInfo;
}

double** DLPAggreg2::getSumValue() const {
	return sumValue;
}

void DLPAggreg2::setValues(const vector<double>& values) {
	this->values = values;
}

