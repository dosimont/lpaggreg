/*
 * DLPAggreg.cpp
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg.h"

DLPAggreg::DLPAggreg() :
		id(0), rank(0), parent(0), childNodes(vector<DLPAggreg*>()), qualities(
				0), bestCompromises(0), bestCuts(0), bestPartitions(
						vector<int>()), parameters(vector<float>()), qualityList(
								vector<Quality*>()), pIC(0), nodeSize(0), valueSize(0), eval(0) {
	
}

DLPAggreg::DLPAggreg(DLPAggreg* parent, int id) :
		id(id), rank(0), parent(parent), childNodes(vector<DLPAggreg*>()), qualities(
				0), bestCompromises(0), bestCuts(0), bestPartitions(
						vector<int>()), parameters(vector<float>()), qualityList(
						vector<Quality*>()), pIC(0), nodeSize(0), valueSize(0), eval(0) {
	parent->addChild(this);
}

DLPAggreg::DLPAggreg(int id) :
		id(id), rank(0), parent(0), childNodes(vector<DLPAggreg*>()), qualities(
				0), bestCompromises(0), bestCuts(0), bestPartitions(
						vector<int>()), parameters(vector<float>()), qualityList(
						vector<Quality*>()), pIC(0), nodeSize(0), valueSize(0), eval(0) {
}

void DLPAggreg::addChild(DLPAggreg *child) {
	childNodes.push_back(child);
	child->setParent(this);
	child->setRank(rank + 1);
}

DLPAggreg* DLPAggreg::getParent() {
	return parent;
}

DLPAggreg::~DLPAggreg() {
	deleteChildNodes();
	clean();
	deleteQualities();
	deleteQualityList();
	deleteParameters();
	if (!hasParent())
	deleteEval();
}

int DLPAggreg::getId() const {
	return id;
}

void DLPAggreg::setId(int id) {
	this->id = id;
}

const vector<DLPAggreg*>& DLPAggreg::getChildNodes() const {
	return childNodes;
}

int DLPAggreg::getNodeSize() const {
	return nodeSize;
}

void DLPAggreg::setParent(DLPAggreg* parent) {
	this->parent = parent;
}

bool DLPAggreg::hasChild() {
	return !childNodes.empty();
}

void DLPAggreg::normalize(double maxGain, double maxLoss) {
	if (maxGain == 0 && maxLoss == 0) {
		maxGain = qualities[valueSize - 1][valueSize - 1]->getGain();
		maxLoss = qualities[valueSize - 1][valueSize - 1]->getLoss();
		eval->incrQCounter(2);
	}
	for (int j = 0; j < valueSize; j++) {
		for (int i = 0; i < valueSize - j; i++) {
			if (maxGain > 0) {
				qualities[i][j]->setGain(qualities[i][j]->getGain() / maxGain);
				eval->incrQCounter();
			}
			if (maxLoss > 0) {
				qualities[i][j]->setLoss(qualities[i][j]->getLoss() / maxLoss);
				eval->incrQCounter();
			}
			for DCHILDS
			DCHILD->normalize(maxGain, maxLoss);
		}
	}
}

Eval* DLPAggreg::getEval() {
	return eval;
}

bool DLPAggreg::hasParent() {
	return (parent != 0);
}

void DLPAggreg::setEval(Eval* eval) {
	this->eval = eval;
	for DCHILDS
	DCHILD->setEval(eval);
}

void DLPAggreg::computeAggregation(double parameter) {
	if (!hasParent()) {
		eval->resetBCCounter();
		eval->startBCTimer();
		computeBestCuts(parameter);
		eval->stopBCTimer();
		eval->resetBPCounter();
		eval->startBPTimer();
		computeBestPartitions();
		eval->stopBPTimer();
		clean();
		for DCHILDS
		DCHILD->clean();
	}
}

void DLPAggreg::computeBestPartitions() {
	for (int i = 0; i < valueSize; i++) {
		bestPartitions.push_back(-1); //WRITE
		eval->incrBPCounter();
	}
	for DCHILDS
	DCHILD->computeBestPartitions();
	if (!hasParent()){
		int *partCounter=new int;
		*partCounter=0;
		eval->incrBPCounter();
		fillPartition(0, valueSize - 1, partCounter);
		delete partCounter;
	}
}

void DLPAggreg::fillPartition(int start, int end, int * counter) {
	DLPCut c = *bestCuts[start][end-start]; //WRITE
	eval->incrBPCounter();
	if (c.isAggregated()){
		setPartitions(c.getCut(), end, *counter);//TODO verificar
		(*counter)++;
		eval->incrBPCounter(2);
		if (c.getCut()>start)
			fillPartition(start, c.getCut()-1, counter);
	}else{
		setPartitions(c.getCut(), end, -1);
		for DCHILDS
		DCHILD->fillPartition(c.getCut(), end, counter);
		if (c.getCut()>start)
			fillPartition(start, c.getCut()-1, counter);
	}
}

void DLPAggreg::setPartitions(int start, int end, int value){
	for (int i=start; i<=end; i++){
		bestPartitions[i]=value;
		eval->incrBPCounter();
	}
	if (value>-1){
		for DCHILDS
		DCHILD->setPartitions(start, end, value);
	}
}

int DLPAggreg::getQualityDuration() {
	return eval->getQDuration();
}

int DLPAggreg::getBestCutDuration() {
	return eval->getBCDuration();
}

int DLPAggreg::getBestPartitionDuration() {
	return eval->getBPDuration();
}

int DLPAggreg::getQualityCount() {
	return eval->getQCount();
}

int DLPAggreg::getBestCutCount() {
	return eval->getBCCount();
}

int DLPAggreg::getBestPartitionCount() {
	return eval->getBPCount();
}

int DLPAggreg::getRank() const {
	return rank;
}

void DLPAggreg::setRank(int rank) {
	this->rank = rank;
	for DCHILDS
	DCHILD->setRank(rank+1);
}

bool DLPAggreg::ownsNode(DLPAggreg* node) {
	if (this == node)
		return true;
	if (hasChild()) {
		for DCHILDS
		if (DCHILD->ownsNode(node))
		return true;
	}
	return false;
}

double** DLPAggreg::getOptimalCompromises() const {
	return bestCompromises;
}

const vector<vector<DLPCut*> >& DLPAggreg::getOptimalCuts() const {
	return bestCuts;
}

double** DLPAggreg::getPIC() const {
	return pIC;
}

const vector<vector<Quality*> >& DLPAggreg::getQualities() const {
	return qualities;
}

double DLPAggreg::sumOptimalCompromise(int i, int j) {
	double sum = 0;
	for DCHILDS
	sum+=DCHILD->getOptimalCompromises()[i][j];
	eval->incrBCCounter(childNodeSize()+1);
	return sum;
}

double DLPAggreg::computePIC(double parameter, int i, int j) {
	return (((double) parameter) * qualities[i][j]->getGain()
			- ((1 - (double) parameter) * qualities[i][j]->getLoss()));
}

void DLPAggreg::computeBestCuts(double parameter) {
	bestCompromises = new double*[valueSize];
	bestCuts = vector<vector<DLPCut*> >();
	pIC = new double*[valueSize];
	int i;
	for (i = 0; i < valueSize; i++) {
		bestCompromises[i] = new double[valueSize];
		pIC[i] = new double[valueSize];
		bestCuts.push_back(vector<DLPCut*>());
		for (int j = 0; j < valueSize; j++) {
			bestCuts[i].push_back(new DLPCut());
			eval->incrBCCounter();
		}
	}
	if (!hasChild()) {
		for (int k = valueSize - 1; k >= 0; k--) {
			pIC[k][0] = computePIC(parameter, k, 0);
			bestCompromises[k][0] = pIC[k][0];
			bestCuts[k][0]->setAll(k, true);
			eval->incrBCCounter(4);
			for (int j = 1; j < valueSize - k; j++) {
				DLPCut currentCut = DLPCut(k, true);
				pIC[k][j] = computePIC(parameter, k, j);
				double currentCompromise = pIC[k][j];
				eval->incrBCCounter(4);
				for (int cut = 1; cut <= j; cut++) {
					double compromise = bestCompromises[k][cut - 1]
							+ pIC[cut + k][j - cut];
					eval->incrBCCounter(1);
					if (compromise>currentCompromise){//||(compromise>=currentCompromise&&(cut+k)>currentCut.getCut())) {
						currentCompromise = compromise;
						currentCut.setAll(cut + k, true);
						eval->incrBCCounter(3);
					}
				}
				bestCompromises[k][j] = currentCompromise;
				bestCuts[k][j]->setAll(currentCut.getCut(),
						currentCut.isAggregated());
				eval->incrBCCounter(3);
			}
		}
	}
	else {
		for DCHILDS
		DCHILD->computeBestCuts(parameter);
		for (int k=valueSize-1; k>=0; k--) {
			pIC[k][0]= computePIC(parameter, k, 0);
			bestCompromises[k][0]=max(pIC[k][0], sumOptimalCompromise(k,0));
			bestCuts[k][0]->setAll(k, pIC[k][0]==bestCompromises[k][0]);
			eval->incrBCCounter(4);
			for (int j=1; j<valueSize-k; j++) {
				pIC[k][j]=computePIC(parameter, k, j);
				double currentCompromise=max(pIC[k][j], sumOptimalCompromise(k,j));
				DLPCut currentCut = DLPCut(k, pIC[k][j]==currentCompromise);
				eval->incrBCCounter(4);
				for (int cut=1; cut<=j; cut++) {
					double compromise=bestCompromises[k][cut-1]+max(pIC[cut+k][j-cut], sumOptimalCompromise(cut+k, j-cut));
					eval->incrBCCounter(1);
					//bool tempAggreg=(pIC[cut+k][j-cut]==(compromise-optimalCompromises[k][cut-1]));
					if (((compromise>currentCompromise))){//||(compromise>=currentCompromise&&(cut+k)>currentCut.getCut()))){
						currentCompromise=compromise;
						currentCut.setAll(cut+k, pIC[cut+k][j-cut]==(compromise-bestCompromises[k][cut-1]));
						eval->incrBCCounter(3);
					}
				}
				bestCompromises[k][j]=currentCompromise;
				bestCuts[k][j]->setAll(currentCut.getCut(), currentCut.isAggregated());
				eval->incrBCCounter(3);
			}
		}
	}
}

int DLPAggreg::getValueSize() const {
	return valueSize;
}

unsigned int DLPAggreg::childNodeSize() {
	return childNodes.size();
}

void DLPAggreg::deleteChildNodes(){
	if (hasChild()){
	for DCHILDS
	delete DCHILD;
	childNodes.clear();
	}
}

void DLPAggreg::deleteQualities(){
	for (int i=valueSize-1; i>=0; i--) {
		for (int j=valueSize-1; j>=0; j--) {
			delete qualities[i][j];
		}
		qualities[i].clear();
	}
	qualities.clear();
}



void DLPAggreg::clean(){
	for (int i=valueSize-1; i>=0; i--) {
		for (int j=valueSize-1; j>=0; j--) {
			delete bestCuts[i][j];
		}
		bestCuts[i].clear();
		delete pIC[i];
		delete bestCompromises[i];
	}
	bestCuts.clear();
	delete pIC;
	delete bestCompromises;
}

void DLPAggreg::deleteEval(){
	delete eval;
}

const vector<int>& DLPAggreg::getOptimalPartitions() const {
	return bestPartitions;
}

void DLPAggreg::computeBestQualities(float threshold) {
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

void DLPAggreg::computeBestQuality(Quality* bestQuality) {
	bestQuality->setGain(0);
	bestQuality->setLoss(0);
	fillQuality(0, valueSize-1, bestQuality);
}

void DLPAggreg::fillQuality(int start, int end, Quality* bestQuality) {
	DLPCut c = *bestCuts[start][end-start]; //WRITE
	eval->incrBPCounter();
	if (c.isAggregated()){
		if (c.getCut()>start)
			fillQuality(start, c.getCut()-1, bestQuality);
		bestQuality->addToGain(qualities[c.getCut()][end-c.getCut()]->getGain());
		bestQuality->addToLoss(qualities[c.getCut()][end-c.getCut()]->getLoss());
	}else{
		for DCHILDS
			DCHILD->fillQuality(c.getCut(), end, bestQuality);

		if (c.getCut()>start)
			fillQuality(start, c.getCut()-1, bestQuality);
	}

}

void DLPAggreg::addBestQualities(float parameter1, float parameter2,
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

void DLPAggreg::deleteQualityList() {
	for (unsigned int i = 0; i < qualityList.size(); i++)
		delete qualityList[i];
	qualityList.clear();
}

void DLPAggreg::deleteBestCuts() {
	for (int i=valueSize-1; i>=0; i--) {
		for (int j=valueSize-1; j>=0; j--) {
			delete bestCuts[i][j];
		}
		bestCuts[i].clear();
	}
}

vector<float> DLPAggreg::getParameters(float threshold) {
	deleteParameters();
	deleteQualityList();
	computeBestQualities(threshold);
	return parameters;

}

const vector<Quality*>& DLPAggreg::getQualityList() const {
	return qualityList;
}

void DLPAggreg::deleteParameters() {
	parameters.clear();
}


