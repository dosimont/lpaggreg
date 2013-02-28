/*
 * ScalarLPAggregationAlgorithm.cpp
 *
 *  Created on: 26 févr. 2013
 *      Author: dosimont
 */

#include "ScalarLPAggregationAlgorithm.h"
#include <math.h>

using namespace std;
ScalarLPAggregationAlgorithm::ScalarLPAggregationAlgorithm(
		vector<float> values, float parameter, bool normalization) :
		LPAggregationAlgorithm(parameter, normalization), values(values) {
	setSize(this->values.size());
}

ScalarLPAggregationAlgorithm::~ScalarLPAggregationAlgorithm() {
}

void ScalarLPAggregationAlgorithm::computeQualities() {
	//Init and allocation
	int n = getSize();
	float ** sumValues = new float*[n];
	float ** entValues = new float*[n];
	gain = new float*[n];
	loss = new float*[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new float[n];
		entValues[i] = new float[n];
		gain[i] = new float[n];
		loss[i] = new float[n];
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		sumValues[0][j] = values[j];
		entValues[0][j] = this->entropyReduction(sumValues[0][j], 0);
		gain[0][j] = 0;
		loss[0][j] = 0;
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			sumValues[i][j] = sumValues[i - 1][j] + sumValues[0][i + j];
			entValues[i][j] = entValues[i - 1][j] + entValues[0][i + j];
			gain[i][j] = this->entropyReduction(sumValues[i][j], entValues[i][j]);
			loss[i][j] = this->divergence(i + 1, sumValues[i][j], entValues[i][j]);
		}
	}
	if (isNormalization()) {
		float maxGain = gain[n - 1][0];
		float maxLoss = gain[n - 1][0];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				gain[i][j] /= maxGain;
				loss[i][j] /= maxLoss;
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

