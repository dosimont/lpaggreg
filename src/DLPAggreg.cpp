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

DLPAggreg::DLPAggreg() :
		id(0), rank(0), parent(0), childNodes(vector<DLPAggreg*>()), quality(
				new Quality(0, 0)), size(0), eval(
				0) {

}



DLPAggreg::DLPAggreg(DLPAggreg* parent, int id) :
		id(id), rank(0), parent(parent), childNodes(vector<DLPAggreg*>()), quality(
				new Quality(0, 0)), size(0), eval(
				0) {
	parent->addChild(this);
}


void DLPAggreg::addChild(DLPAggreg *child) {
	childNodes.push_back(child);
	child->setParent(this);
	child->setRank(rank + 1);
}


void DLPAggreg::setQuality(Quality *quality) {
	this->quality = quality;
}


Quality* DLPAggreg::getQuality() {
	return quality;
}


DLPAggreg* DLPAggreg::getParent() {
	return parent;
}


DLPAggreg::~DLPAggreg() {
	for DCHILDS
	delete DCHILD;
	delete quality;
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


//void DLPAggreg::normalize(double maxGain, double maxLoss) {
//	if (maxGain == 0 && maxLoss == 0) {
//		maxGain = quality->getGain();
//		maxLoss = quality->getLoss();
//		eval->incrQCounter(2);
//	}
//	if (maxGain > 0) {
//		quality->setGain(quality->getGain() / maxGain);
//		eval->incrQCounter();
//	}
//	if (maxLoss > 0) {
//		quality->setLoss(quality->getLoss() / maxLoss);
//		eval->incrQCounter();
//	}
//	for DCHILDS
//	DCHILD->normalize(maxGain, maxLoss);
//}


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



//double DLPAggreg::computeAggregation(float parameter) {
//	if (!hasChild()) {
//		aggregated = true;
//		eval->incrBCCounter();
//		return 0;
//	}
//	else {
//		double nodeQuality = parameter * quality->getGain()
//				- (1 - parameter) * quality->getLoss();
//		double childQuality = 0.0;
//		eval->incrBCCounter(2);
//		for CHILDS {
//			childQuality+=CHILD->computeAggregation(parameter);
//			eval->incrBCCounter();
//		}
//		aggregated = (childQuality < nodeQuality);
//		eval->incrBCCounter();
//		return max(childQuality, nodeQuality);
//	}
//}


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


unsigned int DLPAggreg::childNodeSize() {
	return childNodes.size();
}



