/*
 * DLPAggreg.cpp
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg.h"

/*
 * DLPAggreg.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#include "DLPAggreg.h"

DLPAggreg::DLPAggreg():
		id(0), rank(0), parent(0), childNodes(vector<DLPAggreg*>()), qualities(
				0), optimalCompromise(0), pIC(0), size(0), value_size(0), eval(
				0) {

}



DLPAggreg::DLPAggreg(DLPAggreg* parent, int id) :
				id(id), rank(0), parent(parent), childNodes(vector<DLPAggreg*>()), qualities(0), optimalCompromise(0), pIC(0), size(0), value_size(0), eval(
				0) {
	parent->addChild(this);
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
	for DCHILDS
	delete DCHILD;
	for (int i=value_size-1; i>=0; i++){
		for (int j=value_size-1; j>=0; j++){
			delete qualities[i][j];
		}
		qualities[i].clear();
	}
	qualities.clear();
	if (!hasParent())
	delete eval;
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


int DLPAggreg::getSize() const {
	return size;
}


void DLPAggreg::setParent(DLPAggreg* parent) {
	this->parent = parent;
}


bool DLPAggreg::hasChild() {
	return !childNodes.empty();
}


void DLPAggreg::normalize(double maxGain, double maxLoss) {
	if (maxGain == 0 && maxLoss == 0) {
		maxGain = qualities[value_size-1][value_size-1]->getGain();
		maxLoss = qualities[value_size-1][value_size-1]->getLoss();
		eval->incrQCounter(2);
	}
	for (unsigned j=0; j< value_size; j++){
		for (unsigned i=0; i<value_size-j; i++){
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




//void DLPAggreg::computeBestPartitions() {
//	bestPartitions = new vector<int>();
//	eval->incrBPCounter();
//	fillBestPartitions(bestPartitions, 0);
//}
//
//
//int DLPAggreg::fillBestPartitions(vector<int>*bestPartitions, int p) {
//	this->bestPartitions = bestPartitions;
//	eval->incrBPCounter();
//	if (aggregated) {
//		for (int i = 0; i < size; i++) {
//			this->bestPartitions->push_back(p);
//			eval->incrBPCounter();
//		}
//	}
//	else {
//		for DCHILDS {
//			p = DCHILD->fillBestPartitions(this->bestPartitions, p);
//			eval->incrBPCounter();
//		}
//	}
//	return p + 1;
//}




//vector<int>* DLPAggreg::getAggregation(float parameter) {
//	if (!hasParent()) {
//		//delete bestPartitions;
//		eval->resetBCCounter();
//		eval->startBCTimer();
//		computeAggregation(parameter);
//		eval->stopBCTimer();
//		eval->resetBPCounter();
//		eval->startBPTimer();
//		computeBestPartitions();
//		eval->stopBPTimer();
//		return bestPartitions;
//	}
//	return 0;
//}


void DLPAggreg::computeBestPartitions() {
	for (int i = 0; i < value_size; i++) {
		bestPartitions.push_back(-1); //WRITE
		eval->incrBPCounter();
	}
	for DCHILDS
		DCHILD->computeBestPartitions();
	if (!hasParent())
		fillPartition(value_size - 1, 0);
}
//
//void DLPAggreg::deleteBestPartitions() {
//	bestPartitions.clear();
//}
//
int DLPAggreg::fillPartition(int i, int p) {
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

double** DLPAggreg::getOptimalCompromise() const {
	return optimalCompromise;
}

const vector<vector<DLPPartition*> >& DLPAggreg::getOptimalPartition() const {
	return optimalPartition;
}

double** DLPAggreg::getPIC() const {
	return pIC;
}

const vector<vector<Quality*> >& DLPAggreg::getQualities() const {
	return qualities;
}

double DLPAggreg::sumOptimalCompromise(int i, int j) {
	double sum=0;
	for DCHILDS
		sum+=DCHILD->getOptimalCompromise();
	return sum;
}

double DLPAggreg::computePIC(float parameter, int i, int j) {
	return (((double) parameter ) * qualities[i][j]->getGain() - ((1 - (double) parameter) * qualities[i][j]->getLoss()));
}

void DLPAggreg::computeBestCut(float parameter) {
	optimalCompromise=new double*[value_size];
	optimalPartition=vector<vector<DLPPartition*> >();
	pIC=new double*[value_size];
	int i;
	for (i=0; i<value_size-1; i++){
		optimalCompromise[i]=new double[value_size];
		pIC[i]=new double[value_size];
		optimalPartition.push_back(vector<DLPPartition*>());
		for (int j=0; j<value_size; j++){
			optimalPartition[i][j]=new DLPPartition();
		}
	}
	pIC[i]=new double[value_size];
	if (!hasChild()){
		for (int k=value_size-1; k>=0; k--){
			pIC[k][0]=computePIC(parameter, k, 0);
			optimalCompromise[k][0]=pIC[k][0];
			optimalPartition[k][0]->setAll(k, true);
			for (int j=1; j<value_size-k; j++){
				DLPPartition currentCut = DLPPartition(k, true);
				pIC[k][j]=computePIC(parameter, k, j);
				double currentCompromise = pIC[k][j];
				for (int cut=1; cut<=j; cut++){
					double compromise = optimalCompromise[k][cut-1]+pIC[cut+k][j-cut];
					if (compromise>currentCompromise){
						currentCompromise=compromise;
						currentCut.setAll(cut+k, true);
					}
				}
				optimalCompromise[k][j]=currentCompromise;
				optimalPartition[k][j]->setAll(currentCut.getPartition(), currentCut.isAggregated());
			}
		}
	}else{
		for DCHILDS
			DCHILD->computeBestCut(parameter);
		for (int k=value_size-1; k>=0; k--){
			pIC[k][0]= computePIC(parameter, k, 0);
			optimalCompromise[k][0]=max(pIC[k][0], sumOptimalCompromise(k,0));
			optimalPartition[k][0]->setAll(k, pIC[k,0]==optimalCompromise[k][0]);
			for (int j=1; j<value_size-k; j++){
				pIC[k][j]=computePIC(parameter, k, j);
				double currentCompromise=max(pIC[k][j], sumOptimalCompromise(k,j));
				DLPPartition currentCut = DLPPartition(k, pIC[k][0]==optimalCompromise[k][0]);
				for (int cut=1; cut<=j; cut++){
					double compromise=optimalCompromise[k][cut-1]+max(pIC[cut+k][j-cut], sumOptimalCompromise(cut+k, j-cut));
					if (compromise>currentCompromise){
						currentCompromise=compromise;
						currentCut.setAll(cut+k, pIC[cut+k][j-cut]==compromise);
					}
				}
				optimalCompromise[k][j]=currentCompromise;
				optimalPartition[k][j]->setAll(currentCut.getPartition(), currentCut.isAggregated());
			}
		}
	}
}

int DLPAggreg::getValueSize() const {
	return value_size;
}

unsigned int DLPAggreg::childNodeSize() {
	return childNodes.size();
}



