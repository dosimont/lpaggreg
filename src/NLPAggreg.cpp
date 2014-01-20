/*
 * NLPAggreg.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#include "NLPAggreg.h"

NLPAggreg::NLPAggreg() :
		id(0), rank(0), parent(0), childNodes(vector<NLPAggreg*>()), quality(
				new Quality(0, 0)), aggregated(false), size(0), entSum(0), eval(
				0), bestPartitions(0) {
	
}

//NLPAggreg::NLPAggreg(int id, Value values) :
//		id(id), rank(0), parent(0), childNodes(vector<NLPAggreg*>()), quality(
//				new Quality(0, 0)), aggregated(false), size(0), entSum(0), eval(
//				0), bestPartitions(0) {
//	this->values = values;
//}

NLPAggreg::NLPAggreg(NLPAggreg* parent, int id) :
		id(id), rank(0), parent(parent), childNodes(vector<NLPAggreg*>()), quality(
				new Quality(0, 0)), aggregated(false), size(0), entSum(0), eval(
				0), bestPartitions(0) {
	parent->addChild(this);
}

void NLPAggreg::addChild(NLPAggreg *child) {
	childNodes.push_back(child);
	child->setParent(this);
	child->setRank(rank + 1);
}

void NLPAggreg::setQuality(Quality *quality) {
	this->quality = quality;
}

Quality* NLPAggreg::getQuality() {
	return quality;
}

NLPAggreg* NLPAggreg::getParent() {
	return parent;
}

NLPAggreg::~NLPAggreg() {
	for CHILDS
	delete CHILD;
	delete quality;
	if (!hasParent())
	delete eval;
}

bool NLPAggreg::isAggregated() const {
	return aggregated;
}

int NLPAggreg::getId() const {
	return id;
}

void NLPAggreg::setId(int id) {
	this->id = id;
}

const vector<NLPAggreg*>& NLPAggreg::getChildNodes() const {
	return childNodes;
}

int NLPAggreg::getSize() const {
	return size;
}

double NLPAggreg::getEntSum() const {
	return entSum;
}

void NLPAggreg::setParent(NLPAggreg* parent) {
	this->parent = parent;
}

bool NLPAggreg::hasChild() {
	return !childNodes.empty();
}

void NLPAggreg::normalize(double maxGain, double maxLoss) {
	if (maxGain == 0 && maxLoss == 0) {
		maxGain = quality->getGain();
		maxLoss = quality->getLoss();
		eval->incrQCounter(2);
	}
	if (maxGain > 0) {
		quality->setGain(quality->getGain() / maxGain);
		eval->incrQCounter();
	}
	if (maxLoss > 0) {
		quality->setLoss(quality->getLoss() / maxLoss);
		eval->incrQCounter();
	}
	for CHILDS
	CHILD->normalize(maxGain, maxLoss);
}

Eval* NLPAggreg::getEval() {
	return eval;
}

bool NLPAggreg::hasParent() {
	return (parent != 0);
}

void NLPAggreg::setEval(Eval* eval) {
	this->eval = eval;
	for CHILDS
	CHILD->setEval(eval);
}

void NLPAggreg::setAggregated(bool aggregated) {
	this->aggregated = aggregated;
}

double NLPAggreg::computeAggregation(float parameter) {
	if (!hasChild()) {
		aggregated = true;
		eval->incrBCCounter();
		return 0;
	}
	else {
		double nodeQuality = parameter * quality->getGain()
				- (1 - parameter) * quality->getLoss();
		double childQuality = 0.0;
		eval->incrBCCounter(2);
		for CHILDS {
			childQuality+=CHILD->computeAggregation(parameter);
			eval->incrBCCounter();
		}
		aggregated = (childQuality < nodeQuality);
		eval->incrBCCounter();
		return max(childQuality, nodeQuality);
	}
}

void NLPAggreg::computeBestPartitions() {
	bestPartitions = new vector<int>();
	eval->incrBPCounter();
	fillBestPartitions(bestPartitions, 0);
}

int NLPAggreg::fillBestPartitions(vector<int>*bestPartitions, int p) {
	this->bestPartitions = bestPartitions;
	eval->incrBPCounter();
	if (aggregated) {
		for (int i = 0; i < size; i++) {
			this->bestPartitions->push_back(p);
			eval->incrBPCounter();
		}
	}
	else {
		for CHILDS {
			p = CHILD->fillBestPartitions(this->bestPartitions, p);
			eval->incrBPCounter();
		}
	}
	return p + 1;
}

vector<int>* NLPAggreg::getAggregation(float parameter) {
	if (!hasParent()) {
		delete bestPartitions;
		eval->resetBCCounter();
		eval->startBCTimer();
		computeAggregation(parameter);
		eval->stopBCTimer();
		eval->resetBPCounter();
		eval->startBPTimer();
		computeBestPartitions();
		eval->stopBPTimer();
		return bestPartitions;
	}
	return 0;
}

int NLPAggreg::getQualityDuration() {
	return eval->getQDuration();
}

int NLPAggreg::getBestCutDuration() {
	return eval->getBCDuration();
}

int NLPAggreg::getBestPartitionDuration() {
	return eval->getBPDuration();
}

int NLPAggreg::getQualityCount() {
	return eval->getQCount();
}

int NLPAggreg::getBestCutCount() {
	return eval->getBCCount();
}

int NLPAggreg::getBestPartitionCount() {
	return eval->getBPCount();
}

int NLPAggreg::getRank() const {
	return rank;
}

void NLPAggreg::setRank(int rank) {
	this->rank = rank;
	for CHILDS
	CHILD->setRank(rank+1);
}

bool NLPAggreg::ownsNode(NLPAggreg* node) {
	if (this == node)
		return true;
	if (hasChild()) {
		for CHILDS
		if (CHILD->ownsNode(node))
		return true;
	}
	return false;
}



unsigned int NLPAggreg::childNodeSize() {
	return childNodes.size();
}

