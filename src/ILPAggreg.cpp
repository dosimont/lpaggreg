/*
 * ILPAggreg.cpp
 *
 *  Created on: 26 août 2013
 *      Author: dosimont
 */

#include "ILPAggreg.h"


void ILPAggreg::deleteQualities() {
	for (unsigned int i = 0; i < qualities.size(); i++) {
		for (unsigned int j = 0; j < qualities[i].size(); j++) {
			if (&qualities[i][j] != 0)
				delete qualities[i][j];
		}
		qualities[i].clear();
	}
	qualities.clear();
}


int ILPAggreg::sizeReduction(int size) {
	return size - 1;
}


void ILPAggreg::computeBestCuts(float parameter) {
	int n = getSize();
	bestCuts = new int[n];
	double * bestQuality = new double[n];
	bestCuts[0] = 0; //WRITE
	bestQuality[0] = 0; //WRITE	int n = getSize();
	for (int i = 0; i < n; i++) {
		bestPartitions.push_back(-1); //WRITE
		eval.incrBPCounter();
	}
	fillPartition(n - 1, 0);
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
			if (quality > currentQuality) {
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


void ILPAggreg::deleteBestCuts() {
	delete[] bestCuts;
}


void ILPAggreg::computeBestPartitions() {
	int n = getSize();
	for (int i = 0; i < n; i++) {
		bestPartitions.push_back(-1); //WRITE
		eval.incrBPCounter();
	}
	fillPartition(n - 1, 0);
}


void ILPAggreg::deleteBestPartitions() {
	bestPartitions.clear();
}


int ILPAggreg::fillPartition(int i, int p) {
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


void ILPAggreg::setSize(int size) {
	this->size=size;
}


void ILPAggreg::computeBestQualities(float threshold) {
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


void ILPAggreg::computeBestQuality(Quality* bestQuality) {
	int n = getSize();
	bestQuality->setGain(0);
	bestQuality->setLoss(0);
	fillQuality(n - 1, bestQuality);
}


void ILPAggreg::fillQuality(int i, Quality* bestQuality) {
	int c = bestCuts[i];
	if (c > 0) {
		fillQuality(c - 1, bestQuality);
	}
	bestQuality->addToGain(qualities[i - c][c]->getGain());
	bestQuality->addToLoss(qualities[i - c][c]->getLoss());
}


void ILPAggreg::addBestQualities(float parameter1, float parameter2,
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


void ILPAggreg::deleteQualityList() {
	for (unsigned int i = 0; i < qualityList.size(); i++)
		delete qualityList[i];
	qualityList.clear();
}


void ILPAggreg::deleteParameters() {
	parameters.clear();
}


ILPAggreg::ILPAggreg():
		size(0), qualities(vector< vector<Quality*> >()), bestCuts(0), bestPartitions(vector<int>()), parameters(vector<float>()), qualityList(vector<Quality*>()), eval(Eval()) {
}


ILPAggreg::~ILPAggreg() {
	deleteQualities();
	deleteBestPartitions();
	deleteParameters();
	deleteQualityList();
}

void ILPAggreg::computeQualities(bool normalization) {
	deleteQualities();
	eval.resetQCounter();
	eval.startQTimer();
	computeQualitiesSpe(normalization);
	eval.stopQTimer();
}


vector<int> ILPAggreg::getParts(float parameter) {
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


vector<float> ILPAggreg::getParameters(float threshold) {
	deleteParameters();
	deleteQualityList();
	computeBestQualities(threshold);
	return parameters;

}


const vector<Quality*>& ILPAggreg::getQualityList() const {
	return qualityList;
}


int ILPAggreg::getQualityDuration() {
	return eval.getQDuration();
}


int ILPAggreg::getBestCutDuration() {
	return eval.getBCDuration();
}


int ILPAggreg::getBestPartitionDuration() {
	return eval.getBPDuration();
}


int ILPAggreg::getQualityCount() {
	return eval.getQCount();
}


int ILPAggreg::getBestCutCount() {
	return eval.getBCCount();
}


int ILPAggreg::getBestPartitionCount() {
	return eval.getBPCount();
}
