/*
 * DLPAggreg.cpp
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg.h"

DLPAggreg::DLPAggreg() :
		id(0), rank(0), parent(0), childNodes(vector<DLPAggreg*>()), qualities(
				0), optimalCompromises(0), pIC(0), nodeSize(0), valueSize(0), eval(0) {
	
}

DLPAggreg::DLPAggreg(DLPAggreg* parent, int id) :
		id(id), rank(0), parent(parent), childNodes(vector<DLPAggreg*>()), qualities(
				0), optimalCompromises(0), pIC(0), nodeSize(0), valueSize(0), eval(0) {
	parent->addChild(this);
}

DLPAggreg::DLPAggreg(int id) :
		id(id), rank(0), parent(0), childNodes(vector<DLPAggreg*>()), qualities(
				0), optimalCompromises(0), pIC(0), nodeSize(0), valueSize(0), eval(0) {
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
		computeBestCut(parameter);
		eval->stopBCTimer();
		eval->resetBPCounter();
		eval->startBPTimer();
		computeBestPartitions();
		eval->stopBPTimer();
		clean();
	}
}

void DLPAggreg::computeBestPartitions() {
	for (int i = 0; i < valueSize; i++) {
		optimalPartitions.push_back(-1); //WRITE
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
	cout<<id<<" "<<start<<" "<<end;

	DLPCut c = *optimalCuts[start][end-start]; //WRITE
	cout<<"    "<<c.getCut()<<endl;
	eval->incrBPCounter();
	if (c.isAggregated()){
		setPartitions(c.getCut(), end, *counter);//TODO verificar
		(*counter)++;
		eval->incrBPCounter();
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
		optimalPartitions[i]=value;
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
	return optimalCompromises;
}

const vector<vector<DLPCut*> >& DLPAggreg::getOptimalCuts() const {
	return optimalCuts;
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
	return sum;
}

double DLPAggreg::computePIC(double parameter, int i, int j) {
	return (((double) parameter) * qualities[i][j]->getGain()
			- ((1 - (double) parameter) * qualities[i][j]->getLoss()));
}

void DLPAggreg::computeBestCut(double parameter) {
	optimalCompromises = new double*[valueSize];
	optimalCuts = vector<vector<DLPCut*> >();
	pIC = new double*[valueSize];
	int i;
	for (i = 0; i < valueSize; i++) {
		optimalCompromises[i] = new double[valueSize];
		pIC[i] = new double[valueSize];
		optimalCuts.push_back(vector<DLPCut*>());
		for (int j = 0; j < valueSize; j++) {
			optimalCuts[i].push_back(new DLPCut());
		}
	}
	if (!hasChild()) {
		for (int k = valueSize - 1; k >= 0; k--) {
			pIC[k][0] = computePIC(parameter, k, 0);
			cout<<pIC[k][0]<<endl;
			optimalCompromises[k][0] = pIC[k][0];
			optimalCuts[k][0]->setAll(k, true);
			for (int j = 1; j < valueSize - k; j++) {
				DLPCut currentCut = DLPCut(k, true);
				pIC[k][j] = computePIC(parameter, k, j);
				cout<<pIC[k][j]<<endl;
				double currentCompromise = pIC[k][j];
				for (int cut = 1; cut <= j; cut++) {
					double compromise = optimalCompromises[k][cut - 1]
							+ pIC[cut + k][j - cut];
					cout<<compromise<<endl;
					if (compromise >= currentCompromise) {
						currentCompromise = compromise;
						currentCut.setAll(cut + k, true);
					}
				}
				optimalCompromises[k][j] = currentCompromise;
				optimalCuts[k][j]->setAll(currentCut.getCut(),
						currentCut.isAggregated());
			}
		}
	}
	else {
		for DCHILDS
		DCHILD->computeBestCut(parameter);
		for (int k=valueSize-1; k>=0; k--) {
			pIC[k][0]= computePIC(parameter, k, 0);
			optimalCompromises[k][0]=max(pIC[k][0], sumOptimalCompromise(k,0));
			optimalCuts[k][0]->setAll(k, pIC[k][0]==optimalCompromises[k][0]);
			for (int j=1; j<valueSize-k; j++) {
				pIC[k][j]=computePIC(parameter, k, j);
				double currentCompromise=max(pIC[k][j], sumOptimalCompromise(k,j));
				DLPCut currentCut = DLPCut(k, pIC[k][j]==currentCompromise);
				for (int cut=1; cut<=j; cut++) {
					double compromise=optimalCompromises[k][cut-1]+max(pIC[cut+k][j-cut], sumOptimalCompromise(cut+k, j-cut));
					if (compromise>=currentCompromise) {
						currentCompromise=compromise;
						currentCut.setAll(cut+k, pIC[cut+k][j-cut]==(compromise-optimalCompromises[k][cut-1]));
					}
				}
				optimalCompromises[k][j]=currentCompromise;
				optimalCuts[k][j]->setAll(currentCut.getCut(), currentCut.isAggregated());
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
	cout<<valueSize<<endl;
	for (int i=valueSize-1; i>=0; i--) {
		for (int j=valueSize-1; j>=0; j--) {
			delete optimalCuts[i][j];
		}
		optimalCuts[i].clear();
		delete pIC[i];
		delete optimalCompromises[i];
	}
	optimalCuts.clear();
	delete pIC;
	delete optimalCompromises;
}

void DLPAggreg::deleteEval(){
	delete eval;
}

const vector<int>& DLPAggreg::getOptimalPartitions() const {
	return optimalPartitions;
}
