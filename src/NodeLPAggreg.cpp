/*
 * Node.cpp
 *
 *  Created on: 25 juil. 2013
 *      Author: dosimont
 */

#include "NodeLPAggreg.h"

template <typename Value>
NodeLPAggreg<Value>::NodeLPAggreg(): id(0), rank(0), parent(0), childNodes(vector<NodeLPAggreg*>()), quality(new Quality(0,0)), aggregated(false), size(0), entSum(0), eval(0), bestPartitions(0){
	this->values=0;
}

template <typename Value>
NodeLPAggreg<Value>::NodeLPAggreg(int id, Value values): id(id), rank(0), parent(0), childNodes(vector<NodeLPAggreg*>()), quality(new Quality(0,0)), aggregated(false), size(0), entSum(0), eval(0), bestPartitions(0){
	this->values=values;
}

template <typename Value>
NodeLPAggreg<Value>::NodeLPAggreg(NodeLPAggreg<Value>* parent, int id, Value values): id(id), rank(0), parent(parent), childNodes(vector<NodeLPAggreg*>()), quality(new Quality(0,0)), aggregated(false), size(0), entSum(0), eval(0), bestPartitions(0){
	this->values=values;
	parent->addChild(this);
}

template <typename Value>
void NodeLPAggreg<Value>::addChild(NodeLPAggreg<Value> *child) {
	childNodes.push_back(child);
	child->setParent(this);
	child->setRank(rank+1);
}

template <typename Value>
void NodeLPAggreg<Value>::setQuality(Quality *quality) {
	this->quality = quality;
}

template <typename Value>
Quality* NodeLPAggreg<Value>::getQuality(){
	return quality;
}

template <typename Value>
NodeLPAggreg<Value>* NodeLPAggreg<Value>::getParent(){
	return parent;
}

template <typename Value>
NodeLPAggreg<Value>::~NodeLPAggreg() {
	for CHILDS
		delete CHILD;
	delete quality;
	if (!hasParent())
		delete eval;
}

template <typename Value>
bool NodeLPAggreg<Value>::isAggregated() const {
	return aggregated;
}

template <typename Value>
int NodeLPAggreg<Value>::getId() const {
	return id;
}

template <typename Value>
void NodeLPAggreg<Value>::setId(int id) {
	this->id = id;
}

template <typename Value>
const vector<NodeLPAggreg<Value>*>& NodeLPAggreg<Value>::getChildNodes() const {
	return childNodes;
}

template <typename Value>
int NodeLPAggreg<Value>::getSize() const {
	return size;
}

template <typename Value>
double NodeLPAggreg<Value>::getEntSum() const {
	return entSum;
}

template <typename Value>
void NodeLPAggreg<Value>::setParent(NodeLPAggreg<Value>* parent) {
	this->parent = parent;
}

template <typename Value>
bool NodeLPAggreg<Value>::hasChild() {
	return !childNodes.empty();
}

template <typename Value>
void NodeLPAggreg<Value>::normalize(double maxGain, double maxLoss) {
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

template <typename Value>
Eval* NodeLPAggreg<Value>::getEval(){
	return eval;
}

template <typename Value>
bool NodeLPAggreg<Value>::hasParent() {
	return (parent!=0);
}

template <typename Value>
void NodeLPAggreg<Value>::setEval(Eval* eval) {
	this->eval = eval;
	for CHILDS
		CHILD->setEval(eval);
}

template <typename Value>
void NodeLPAggreg<Value>::setAggregated(bool aggregated) {
	this->aggregated = aggregated;
}

template <typename Value>
double NodeLPAggreg<Value>::computeAggregation(float parameter) {
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

template <typename Value>
void NodeLPAggreg<Value>::computeBestPartitions() {
	bestPartitions = new vector<int>();
	eval->incrBPCounter();
	fillBestPartitions(bestPartitions, 0);
}

template <typename Value>
int NodeLPAggreg<Value>::fillBestPartitions(vector<int>*bestPartitions, int p) {
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

template <typename Value>
void NodeLPAggreg<Value>::computeQualities(bool normalization) {
	if (!hasParent()){
		setEval(new Eval);
		eval->resetQCounter();
		eval->startQTimer();
		computeQuality();
		if (normalization)
			normalize();
		eval->stopQTimer();
	}
}

template <typename Value>
vector<int>* NodeLPAggreg<Value>::getAggregation(float parameter) {
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

template <typename Value>
int NodeLPAggreg<Value>::getQualityDuration() {
	return eval->getQDuration();
}

template <typename Value>
int NodeLPAggreg<Value>::getBestCutDuration() {
	return eval->getBCDuration();
}

template <typename Value>
int NodeLPAggreg<Value>::getBestPartitionDuration() {
	return eval->getBPDuration();
}

template <typename Value>
int NodeLPAggreg<Value>::getQualityCount() {
	return eval->getQCount();
}

template <typename Value>
int NodeLPAggreg<Value>::getBestCutCount() {
	return eval->getBCCount();
}

template <typename Value>
int NodeLPAggreg<Value>::getBestPartitionCount() {
	return eval->getBPCount();
}

template <typename Value>
int NodeLPAggreg<Value>::getRank() const {
	return rank;
}

template <typename Value>
void NodeLPAggreg<Value>::setRank(int rank) {
	this->rank = rank;
	for CHILDS
		CHILD->setRank(rank+1);
}

template <typename Value>
bool NodeLPAggreg<Value>::ownsNode(NodeLPAggreg<Value>* node) {
	if (this==node)
		return true;
	if (hasChild()){
		for CHILDS
			if (CHILD->ownsNode(node))
				return true;
	}
	return false;
}

template<typename Value>
Value NodeLPAggreg<Value>::getValue(){
	return this->values;
}

template<typename Value>
void NodeLPAggreg<Value>::setValue(Value values) {
	if (!hasChild())
		this->values=values;
}

template<typename Value>
void NodeLPAggreg<Value>::computeQuality(){
	computeQuality(this->values);
}

template<typename Value>
void NodeLPAggreg<Value>::computeQuality(double value) {
	if (!hasChild()){
		entSum=entropyReduction(this->values, 0.0);
		size=1;
		eval->incrQCounter(2);
	}else{
		this->values=0;
		entSum=0;
		size=0;
		eval->incrQCounter(3);
		for CHILDS{
			CHILD->computeQuality();
			this->values+=CHILD->getValue();
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		quality->setGain(entropyReduction(this->values, entSum));
		quality->setLoss(divergence(size, this->values, entSum));
		eval->incrQCounter(2);
	}
}

template<typename Value>
void NodeLPAggreg<Value>::computeQuality(vector<double> values) {
	for (int i=0; i<this->values.size(); i++)
		computeQuality_Vector(i);
}

template<typename Value>
void NodeLPAggreg<Value>::computeQuality_Vector(int index) {
	if (!hasChild()){
		entSum=entropyReduction(this->values[index], 0);
		size=1;
		eval->incrQCounter(2);
	}else{
		this->values[index]=0;
		entSum=0;
		size=0;
		eval->incrQCounter(3);
		for CHILDS{
			CHILD->computeQuality_Vector(index);
			this->values[index]+=CHILD->getValue()[index];
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		if (index==0){
			quality->setGain(0);
			quality->setLoss(0);
		}
		quality->addToGain(entropyReduction(this->values[index], entSum));
		quality->addToLoss(divergence(size, this->values[index], entSum));
		eval->incrQCounter(2);
	}
}

template<typename Value>
void NodeLPAggreg<Value>::computeQuality(
		vector<vector<double> > values) {
	for (unsigned int i=0; i<this->values.size(); i++)
		for (unsigned int j=0; j<this->values[i].size(); j++)
			computeQuality_Matrix(i,j);
}

template<typename Value>
void NodeLPAggreg<Value>::computeQuality_Matrix(int i, int j) {
	if (!hasChild()){
		entSum=entropyReduction(this->values[i][j], 0);
		size=1;
		eval->incrQCounter(2);
	}else{
		this->values[i][j]=0;
		entSum=0;
		size=0;
		eval->incrQCounter(3);
		for CHILDS{
			CHILD->computeQuality(i,j);
			this->values[i][j]+=CHILD->getValue()[i][j];
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		if (i==0&&j==0){
			quality->setGain(0);
			quality->setLoss(0);
		}
		quality->addToGain(entropyReduction(this->values[i][j], entSum));
		quality->addToLoss(divergence(size, this->values[i][j], entSum));
		eval->incrQCounter(2);
	}
}

template<typename Value>
void NodeLPAggreg<Value>::computeQuality(Value values) {
	cerr<<"ComputeQuality() not implemented for this type yet"<<endl;
}

template <typename Value>
unsigned int NodeLPAggreg<Value>::childNodeSize() {
	return childNodes.size();
}
