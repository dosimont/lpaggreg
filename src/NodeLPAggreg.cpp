/*
 * Node.cpp
 *
 *  Created on: 25 juil. 2013
 *      Author: dosimont
 */

#include "NodeLPAggreg.h"


NodeLPAggreg::NodeLPAggreg(): id(0), rank(0), value(0), parent(0), childNodes(vector<NodeLPAggreg*>()), quality(new Quality(0,0)), aggregated(false), size(0), entSum(0), eval(new Eval()), bestPartitions(0){
	
}

NodeLPAggreg::NodeLPAggreg(int id, int value=0): id(id), rank(0), value(value), parent(0), childNodes(vector<NodeLPAggreg*>()), quality(new Quality(0,0)), aggregated(false), size(0), entSum(0), eval(new Eval()), bestPartitions(0){

}

NodeLPAggreg::NodeLPAggreg(NodeLPAggreg* parent, int id=0, int value=0): id(id), rank(0), value(value), parent(parent), childNodes(vector<NodeLPAggreg*>()), quality(new Quality(0,0)), aggregated(false), size(0), entSum(0), eval(new Eval()), bestPartitions(0){
	parent->addChild(this);
}

void NodeLPAggreg::addChild(NodeLPAggreg *child) {
	childNodes.push_back(child);
	child->setParent(this);
	child->setRank(rank+1);
	child->setEval(eval);
}

void NodeLPAggreg::setQuality(Quality *quality) {
	this->quality = quality;
}

Quality* NodeLPAggreg::getQuality(){
	return quality;
}

NodeLPAggreg* NodeLPAggreg::getParent(){
	return parent;
}

NodeLPAggreg::~NodeLPAggreg() {
	for CHILDS
		delete CHILD;
	delete quality;
	if (!hasParent())
		delete eval;
}

bool NodeLPAggreg::isAggregated() const {
	return aggregated;
}

int NodeLPAggreg::getId() const {
	return id;
}

void NodeLPAggreg::setId(int id) {
	this->id = id;
}

double NodeLPAggreg::getValue() const {
	return value;
}

void NodeLPAggreg::setValue(double value) {
	if (!hasChild()){
		this->value = value;
	}
}

const vector<NodeLPAggreg*>& NodeLPAggreg::getChildNodes() const {
	return childNodes;
}

void NodeLPAggreg::computeQuality() {
	if (!hasChild()){
		entSum=entropyReduction(value, 0);
		size=1;
		eval->incrQCounter(2);
	}else{
		value=0;
		entSum=0;
		size=0;
		eval->incrQCounter(3);
		for CHILDS{
			CHILD->computeQuality();
			value+=CHILD->getValue();
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		quality->setGain(entropyReduction(value, entSum));
		quality->setLoss(divergence(size, value, entSum));
		eval->incrQCounter(2);
	}
}


int NodeLPAggreg::getSize() const {
	return size;
}

double NodeLPAggreg::getEntSum() const {
	return entSum;
}

void NodeLPAggreg::setParent(NodeLPAggreg* parent) {
	this->parent = parent;
}

bool NodeLPAggreg::hasChild() {
	return !childNodes.empty();
}

void NodeLPAggreg::normalize(double maxGain=0, double maxLoss=0) {
	if (maxGain==0&&maxLoss==0){
		maxGain=quality->getGain();
		maxLoss=quality->getLoss();
		eval->incrQCounter(2);
	}
	if (maxGain>0){
		quality->setGain(quality->getGain()/maxGain);
		eval->incrQCounter();
	}
	if (maxLoss>0){
		quality->setLoss(quality->getLoss()/maxLoss);
		eval->incrQCounter();
	}
	for CHILDS
		CHILD->normalize(maxGain, maxLoss);
}

Eval* NodeLPAggreg::getEval(){
	return eval;
}

bool NodeLPAggreg::hasParent() {
	return (parent!=0);
}

void NodeLPAggreg::setEval(Eval* eval) {
	delete this->eval;
	this->eval = eval;
}

void NodeLPAggreg::setAggregated(bool aggregated) {
	this->aggregated = aggregated;
}

double NodeLPAggreg::computeAggregation(float parameter) {
	if (!hasChild()){
		aggregated=true;
		eval->incrBCCounter();
		return 0;
	}else{
		double nodeQuality=parameter*quality->getGain()-(1-parameter)*quality->getLoss();
		double childQuality=0.0;
		eval->incrBCCounter(2);
		for CHILDS{
			childQuality+=CHILD->computeAggregation(parameter);
			eval->incrBCCounter();
		}
		aggregated=(childQuality<nodeQuality);
		eval->incrBCCounter();
		return max(childQuality, nodeQuality);
	}
}

void NodeLPAggreg::computeBestPartitions() {
	bestPartitions = new vector<int>();
	eval->incrBPCounter();
	fillBestPartitions(bestPartitions, 0);
}

int NodeLPAggreg::fillBestPartitions(vector<int>*bestPartitions, int p) {
	this->bestPartitions=bestPartitions;
	eval->incrBPCounter();
	if (aggregated){
		for (int i=0; i<size; i++){
			this->bestPartitions->push_back(p);
			eval->incrBPCounter();
		}
	}else{
		for CHILDS{
			p = CHILD->fillBestPartitions(this->bestPartitions, p);
			eval->incrBPCounter();
		}
	}
	return p+1;
}

void NodeLPAggreg::init(bool normalization) {
	if (!hasParent()){
		eval->resetQCounter();
		eval->startQTimer();
		computeQuality();
		if (normalization)
			normalize();
		eval->stopQTimer();
	}
}

vector<int>* NodeLPAggreg::getAggregation(float parameter) {
	if (!hasParent()){
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

int NodeLPAggreg::getQualityDuration() {
	return eval->getQDuration();
}

int NodeLPAggreg::getBestCutDuration() {
	return eval->getBCDuration();
}

int NodeLPAggreg::getBestPartitionDuration() {
	return eval->getBPDuration();
}

int NodeLPAggreg::getQualityCount() {
	return eval->getQCount();
}

int NodeLPAggreg::getBestCutCount() {
	return eval->getBCCount();
}

int NodeLPAggreg::getBestPartitionCount() {
	return eval->getBPCount();
}

int NodeLPAggreg::getRank() const {
	return rank;
}

void NodeLPAggreg::setRank(int rank) {
	this->rank = rank;
	for CHILDS
		CHILD->setRank(rank+1);
}
