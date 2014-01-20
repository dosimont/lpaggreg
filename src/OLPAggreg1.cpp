/*
 * OLPAggreg1.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#include "OLPAggreg1.h"

OLPAggreg1::OLPAggreg1() :
		OLPAggreg() {
}

void OLPAggreg1::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	setSize(values.size());
	int n = this->getSize();
	double ** sumValues = new double*[n];
	double ** entValues = new double*[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double[n];
		entValues[i] = new double[n];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < n; j++) {
			qualities[i].push_back(new Quality(0, 0)); //WRITE*2
			eval.incrQCounter(2);
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		sumValues[0][j] = this->values[j]; //WRITE
		entValues[0][j] = entropyReduction(sumValues[0][j], 0); //WRITE
		eval.incrQCounter(2);
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) { //WRITE*4
			sumValues[i][j] = sumValues[i - 1][j] + sumValues[0][i + j];
			entValues[i][j] = entValues[i - 1][j] + entValues[0][i + j];
			qualities[i][j]->setGain(
					entropyReduction(sumValues[i][j], entValues[i][j]));
			qualities[i][j]->setLoss(
					divergence(i + 1, sumValues[i][j], entValues[i][j]));
			eval.incrQCounter(4);
		}
	}
	if (normalization) {
		Quality * maxQuality = new Quality(qualities[n - 1][0]->getGain(),
				qualities[n - 1][0]->getLoss()); //WRITE
		eval.incrQCounter();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) { //WRITE*2
				qualities[i][j]->setGain(
						qualities[i][j]->getGain() / maxQuality->getGain());
				qualities[i][j]->setLoss(
						qualities[i][j]->getLoss() / maxQuality->getLoss());
				eval.incrQCounter(2);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

OLPAggreg1::OLPAggreg1(vector<double> values) :
		OLPAggreg(), values(values) {
}

void OLPAggreg1::setValues(const vector<double>& values) {
	this->values = values;
}

OLPAggreg1::~OLPAggreg1() {
	// TODO Auto-generated destructor stub
}

unsigned int OLPAggreg1::getSize() {
	return values.size();
}

void OLPAggreg1::computeQualities(bool normalization) {
	deleteQualities();
	eval.resetQCounter();
	eval.startQTimer();
	computeQualitiesSpe(normalization);
	eval.stopQTimer();
}
