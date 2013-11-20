/*
 * OLPAggreg.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#include "OLPAggreg.h"

void OLPAggreg::deleteQualities() {
	for (unsigned int i = 0; i < qualities.size(); i++) {
		for (unsigned int j = 0; j < qualities[i].size(); j++) {
			if (&qualities[i][j] != 0)
				delete qualities[i][j];
		}
		qualities[i].clear();
	}
	qualities.clear();
}

int OLPAggreg::sizeReduction(int size) {
	return size - 1;
}

void OLPAggreg::computeBestCuts(float parameter) {
	int n = getSize();
	bestCuts = new int[n];
	double * bestQuality = new double[n];
	bestCuts[0] = 0; //WRITE
	bestQuality[0] = 0; //WRITE	int n = getSize();
	eval.incrBCCounter(2);
	for (int i = 1; i < n; i++) {
		long currentCut = 0; //WRITE
		double currentQuality = parameter * qualities[i][0]->getGain() //WRITE
		- (1 - parameter) * qualities[i][0]->getLoss();
		eval.incrBCCounter(2);
		for (int k = 1; k < i + 1; k++) { //WRITE
			double quality = bestQuality[k - 1]
					+ parameter * qualities[i - k][k]->getGain()
					- (1 - parameter) * qualities[i - k][k]->getLoss();
			eval.incrBCCounter();
			if (quality >= currentQuality) {//TODO influence p
				currentCut = k; //WRITE*2
				currentQuality = quality;
				eval.incrBCCounter(2);
			}
			bestCuts[i] = currentCut; //WRITE*2
			bestQuality[i] = currentQuality;
			eval.incrBCCounter(2);
		}
	}
	delete[] bestQuality;
}

void OLPAggreg::deleteBestCuts() {
	delete[] bestCuts;
}

void OLPAggreg::computeBestPartitions() {
	int n = getSize();
	for (int i = 0; i < n; i++) {
		bestPartitions.push_back(-1); //WRITE
		eval.incrBPCounter();
	}
	fillPartition(n - 1, 0);
}

void OLPAggreg::deleteBestPartitions() {
	bestPartitions.clear();
}

int OLPAggreg::fillPartition(int i, int p) {
	int c = bestCuts[i]; //WRITE
	eval.incrBPCounter();
	if (c > 0) {
		p = fillPartition(c - 1, p); //WRITE
		eval.incrBPCounter();
	}
	for (int k = c; k < i + 1; k++) {
		bestPartitions[k] = p; //WRITE
		eval.incrBPCounter();
	}
	return p + 1;
}

void OLPAggreg::setSize(int size) {
	this->size = size;
}

void OLPAggreg::computeBestQualities(float threshold) {
	Quality *bestQualityParam0 = new Quality();
	Quality *bestQualityParam1 = new Quality();
	computeBestCuts(0);
	computeBestQuality(bestQualityParam0);
	deleteBestCuts();
	parameters.push_back(0);
	qualityList.push_back(bestQualityParam0);
	computeBestCuts(1);
	computeBestQuality(bestQualityParam1);
	deleteBestCuts();
	addBestQualities(0, 1, bestQualityParam0, bestQualityParam1, threshold);
	parameters.push_back(1);
	qualityList.push_back(bestQualityParam1);
	for (unsigned int i = qualityList.size() - 1; i > 0; i--) {
		if ((qualityList[i]->getGain() == qualityList[i - 1]->getGain())
				&& (qualityList[i]->getLoss() == qualityList[i - 1]->getLoss())) {
			delete qualityList[i];
			qualityList.erase(qualityList.begin() + i);
			parameters.erase(parameters.begin() + i);
		}
	}
}

void OLPAggreg::computeBestQuality(Quality* bestQuality) {
	int n = getSize();
	bestQuality->setGain(0);
	bestQuality->setLoss(0);
	fillQuality(n - 1, bestQuality);
}

void OLPAggreg::fillQuality(int i, Quality* bestQuality) {
	int c = bestCuts[i];
	if (c > 0) {
		fillQuality(c - 1, bestQuality);
	}
	bestQuality->addToGain(qualities[i - c][c]->getGain());
	bestQuality->addToLoss(qualities[i - c][c]->getLoss());
}

void OLPAggreg::addBestQualities(float parameter1, float parameter2,
		Quality* bestQuality1, Quality* bestQuality2, float threshold) {
	if (!(((bestQuality1->getGain() == bestQuality2->getGain())
			&& (bestQuality1->getLoss() == bestQuality2->getLoss()))
			|| (parameter2 - parameter1 <= threshold))) {
		float parameter = parameter1 + ((parameter2 - parameter1) / 2);
		Quality *bestQuality = new Quality();
		computeBestCuts(parameter);
		computeBestQuality(bestQuality);
		deleteBestCuts();
		addBestQualities(parameter1, parameter, bestQuality1, bestQuality,
				threshold);
		parameters.push_back(parameter);
		qualityList.push_back(bestQuality);
		addBestQualities(parameter, parameter2, bestQuality, bestQuality2,
				threshold);
	}
}

void OLPAggreg::deleteQualityList() {
	for (unsigned int i = 0; i < qualityList.size(); i++)
		delete qualityList[i];
	qualityList.clear();
}

void OLPAggreg::deleteParameters() {
	parameters.clear();
}

OLPAggreg::OLPAggreg() :
		size(0), qualities(vector<vector<Quality*> >()), bestCuts(0), bestPartitions(
				vector<int>()), parameters(vector<float>()), qualityList(
				vector<Quality*>()), eval(Eval()) {
}

OLPAggreg::~OLPAggreg() {
	deleteQualities();
	deleteBestPartitions();
	deleteParameters();
	deleteQualityList();
}



vector<int> OLPAggreg::getParts(float parameter) {
	deleteBestPartitions();
	eval.resetBCCounter();
	eval.startBCTimer();
	computeBestCuts(parameter);
	eval.stopBCTimer();
	eval.resetBPCounter();
	eval.startBPTimer();
	computeBestPartitions();
	eval.stopBPTimer();
	deleteBestCuts();
	return bestPartitions;
}

vector<float> OLPAggreg::getParameters(float threshold) {
	deleteParameters();
	deleteQualityList();
	computeBestQualities(threshold);
	return parameters;
	
}

const vector<Quality*>& OLPAggreg::getQualityList() const {
	return qualityList;
}

int OLPAggreg::getQualityDuration() {
	return eval.getQDuration();
}

int OLPAggreg::getBestCutDuration() {
	return eval.getBCDuration();
}

int OLPAggreg::getBestPartitionDuration() {
	return eval.getBPDuration();
}

int OLPAggreg::getQualityCount() {
	return eval.getQCount();
}

int OLPAggreg::getBestCutCount() {
	return eval.getBCCount();
}

int OLPAggreg::getBestPartitionCount() {
	return eval.getBPCount();
}

unsigned int OLPAggreg::getSize() {
	return size;
}