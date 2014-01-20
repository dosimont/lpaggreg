/*
 * OLPAggreg3.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#include "OLPAggreg3.h"

OLPAggreg3::OLPAggreg3() :
		OLPAggreg() {
	// TODO Auto-generated constructor stub
	
}

void OLPAggreg3::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	setSize(values.size());
	int n = this->getSize();
	int m = this->values[0].size();
	int l = this->values[0][0].size();
	double **** sumValues = new double***[n];
	double **** entValues = new double***[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double**[n];
		entValues[i] = new double**[n];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < n; j++) {
			sumValues[i][j] = new double*[m];
			entValues[i][j] = new double*[m];
			qualities[i].push_back(new Quality(0, 0));
			eval.incrQCounter(2);
			for (int k = 0; k < m; k++) {
				sumValues[i][j][k] = new double[l];
				entValues[i][j][k] = new double[l];
			}
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < m; k++) {
			for (int o = 0; o < l; o++) {
				sumValues[0][j][k][o] = this->values[j][k][o];
				entValues[0][j][k][o] = entropyReduction(sumValues[0][j][k][o],
						0);
				eval.incrQCounter(2);
			}
		}
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			for (int k = 0; k < m; k++) {
				for (int o = 0; o < l; o++) {
					sumValues[i][j][k][o] = sumValues[i - 1][j][k][o]
							+ sumValues[0][i + j][k][o];
					entValues[i][j][k][o] = entValues[i - 1][j][k][o]
							+ entValues[0][i + j][k][o];
					qualities[i][j]->addToGain(
							entropyReduction(sumValues[i][j][k][o],
									entValues[i][j][k][o]));
					qualities[i][j]->addToLoss(
							divergence(i + 1, sumValues[i][j][k][o],
									entValues[i][j][k][o]));
					eval.incrQCounter(4);
				}
			}
		}
	}
	if (normalization) {
		Quality * maxQuality = new Quality(qualities[n - 1][0]->getGain(),
				qualities[n - 1][0]->getLoss());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				qualities[i][j]->setGain(
						qualities[i][j]->getGain() / maxQuality->getGain());
				qualities[i][j]->setLoss(
						qualities[i][j]->getLoss() / maxQuality->getLoss());
				eval.incrQCounter(2);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				delete[] sumValues[i][j][k];
				delete[] entValues[i][j][k];
			}
			delete[] sumValues[i][j];
			delete[] entValues[i][j];
		}
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

OLPAggreg3::OLPAggreg3(vector<vector<vector<double> > > values) :
		OLPAggreg(), values(values) {
}

void OLPAggreg3::setValues(const vector<vector<vector<double> > >& values) {
	this->values = values;
}

OLPAggreg3::~OLPAggreg3() {
	// TODO Auto-generated destructor stub
}

unsigned int OLPAggreg3::getSize() {
	return values.size();
}

void OLPAggreg3::computeQualities(bool normalization) {
	deleteQualities();
	eval.resetQCounter();
	eval.startQTimer();
	computeQualitiesSpe(normalization);
	eval.stopQTimer();
}
