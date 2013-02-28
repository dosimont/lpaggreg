/*
 * TimeAggregationAlgorithm.cpp
 *
 *  Created on: 26 févr. 2013
 *      Author: dosimont
 */

#include "LPAggregationAlgorithm.h"

LPAggregationAlgorithm::LPAggregationAlgorithm(float parameter,
		bool normalization) :
		parameter(parameter), normalization(normalization), size(0), loss(0), gain(
				0), bestCuts(0), bestPartitions(0) {
	
}

float LPAggregationAlgorithm::getParameter() {
	return parameter;
}

void LPAggregationAlgorithm::setParameter(float parameter) {
	this->parameter = parameter;
}

LPAggregationAlgorithm::~LPAggregationAlgorithm() {
	bestPartitions.clear();
}

void LPAggregationAlgorithm::computeQualities() {
}

inline float LPAggregationAlgorithm::entropy(float value) {
	return value * log(value) / log(2);
	
}

float LPAggregationAlgorithm::entropyReduction(float value,
		float ent) {
	if (value > 0)
		return entropy(value) - ent;
	else
		return 0;
}

float LPAggregationAlgorithm::divergence(int size, float value,
		float ent) {
	return value * log(size) / log(2) - entropyReduction(value, ent);
	
}

bool LPAggregationAlgorithm::isNormalization() const {
	return normalization;
}

void LPAggregationAlgorithm::setNormalization(bool normalization) {
	this->normalization = normalization;
}

int LPAggregationAlgorithm::getSize() const {
	return size;
}

void LPAggregationAlgorithm::setSize(int size) {
	this->size = size;
}

void LPAggregationAlgorithm::computeBestCuts() {
	int n = getSize();
	bestCuts = new float*[n];
	float ** bestQuality = new float*[n];
	for (int i = 0; i < n; i++) {
		bestCuts[i] = new float[n];
		bestQuality[i] = new float[n];
	}
	for (int j = 0; j < n; j++) {
		bestCuts[0][j] = 0;
		bestQuality[0][j] = 0;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			float currentCut = 0;
			float currentQuality = getParameter() * gain[i][j]
					- (1 - getParameter()) * loss[i][j];
			for (int k = 1; k < i + 1; k++) {
				float quality = bestQuality[k - 1][j]
						+ bestQuality[i - k][j + k];
				if (quality >= currentQuality) {
					currentCut = k;
					currentQuality = quality;
				}
				bestCuts[i][j] = currentCut;
				bestQuality[i][j] = currentQuality;
				
			}
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] bestQuality[i];
		delete[] gain[i];
		delete[] loss[i];
	}
	delete[] bestQuality;
	delete[] gain;
	delete[] loss;
	
}

void LPAggregationAlgorithm::computeBestPartitions() {
	int n = getSize();
	for (int i = 0; i < n; i++)
		bestPartitions.push_back(-1);
	fillPartition(n - 1, 0, 0);
	for (int i = 0; i < n; i++) {
		delete[] bestCuts[i];
	}
	delete[] bestCuts;
}

int LPAggregationAlgorithm::fillPartition(int i, int j, int p) {
	int c = bestCuts[i][j];
	if (c > 0) {
		p = fillPartition(c - 1, j, p);
		p = fillPartition(i - c, j + c, p);
		return p;
	}
	else {
		for (int k = 0; k < i + 1; k++) {
			bestPartitions[j + k] = p;
		}
		return p + 1;
	}
}

vector<float> LPAggregationAlgorithm::process() {
	computeQualities();
	computeBestCuts();
	computeBestPartitions();
	return bestPartitions;
}

LPAggregationAlgorithm::LPAggregationAlgorithm() :parameter(0), normalization(false), size(0), loss(0), gain(
		0), bestCuts(0), bestPartitions(0){
}
