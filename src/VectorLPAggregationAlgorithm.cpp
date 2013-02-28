/*
 * VectorLPAggregationAlgorithm.cpp
 *
 *  Created on: 27 févr. 2013
 *      Author: dosimont
 */

#include "VectorLPAggregationAlgorithm.h"

VectorLPAggregationAlgorithm::VectorLPAggregationAlgorithm(vector< vector<float> > values, float parameter,
		bool normalization):
	LPAggregationAlgorithm(parameter, normalization), values(values) {
		setSize(this->values.size());
	// TODO Auto-generated constructor stub
	
}

VectorLPAggregationAlgorithm::~VectorLPAggregationAlgorithm() {
	// TODO Auto-generated destructor stub
}

void VectorLPAggregationAlgorithm::computeQualities() {
	//Init and allocation
	int n = getSize();
	int m = values[0].size();
	float *** sumValues = new float**[n];
	float *** entValues = new float**[n];
	gain = new float*[n];
	loss = new float*[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new float*[n];
		entValues[i] = new float*[n];
		gain[i] = new float[n];
		loss[i] = new float[n];
		for (int j = 0; j<n; j++){
			sumValues[i][j] = new float[m];
			entValues[i][j] = new float[m];
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		for (int k =0; k< m; k++){
			sumValues[0][j][k] = values[j][k];
			entValues[0][j][k] = this->entropyReduction(sumValues[0][j][k], 0);
		}
		gain[0][j] = 0;
		loss[0][j] = 0;
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			gain[i][j] = 0;
			loss[i][j] = 0;
			for (int k =0; k< m; k++){
			sumValues[i][j][k] = sumValues[i - 1][j][k] + sumValues[0][i + j][k];
			entValues[i][j][k] = entValues[i - 1][j][k] + entValues[0][i + j][k];
			gain[i][j] += this->entropyReduction(sumValues[i][j][k], entValues[i][j][k]);
			loss[i][j] += this->divergence(i + 1, sumValues[i][j][k], entValues[i][j][k]);
			}
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

