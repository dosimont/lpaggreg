/*
 * Node.cpp
 *
 *  Created on: 25 juil. 2013
 *      Author: dosimont
 */

#include "Node.h"


Node::Node(): id(0), value(0), parent(0), childNodes(vector<Node*>()), quality(new Quality(0,0)), aggregated(false), size(0), entSum(0){
	// TODO Auto-generated constructor stub
	
}

Node::Node(Node* parent, int id=0): id(id), value(0), parent(parent), childNodes(vector<Node*>()), quality(new Quality(0,0)), aggregated(false), size(0), entSum(0){
	parent->addChild(this);
}

void Node::addChild(Node *child) {
	childNodes.push_back(child);
	child->setParent(this);
}

void Node::updateParents() {
	if (hasChild()){
		value=0;
		for CHILDS
			value+=CHILD->getValue();
	}
	if (parent!=0)
		parent->updateParents();
}


void Node::setQuality(Quality *quality) {
	this->quality = quality;
}

Quality* Node::getQuality(){
	return quality;
}

Node* Node::getParent(){
	return parent;
}

Node::~Node() {
	for CHILDS
		delete CHILD;
	delete quality;
}

bool Node::isAggregated() const {
	return aggregated;
}

int Node::getId() const {
	return id;
}

void Node::setId(int id) {
	this->id = id;
}

double Node::getValue() const {
	return value;
}

void Node::setValue(double value) {
	if (!hasChild()){
		this->value = value;
		updateParents();
	}
}

const vector<Node*>& Node::getChildNodes() const {
	return childNodes;
}

void Node::computeQuality() {
	if (!hasChild()){
		entSum = entropyReduction(value, 0);
		size = 1;
	}else{
		value=0;
		entSum=0;
		size=0;
		for CHILDS{
			CHILD->computeQuality();
			value+=CHILD->getValue();
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
		}
		quality->setGain(entropyReduction(value, entSum));
		quality->setLoss(divergence(size, value, entSum));
	}
}


int Node::getSize() const {
	return size;
}

double Node::getEntSum() const {
	return entSum;
}

void Node::setParent(Node* parent) {
	this->parent = parent;
	updateParents();
}

bool Node::hasChild() {
	return !childNodes.empty();
}

void Node::normalize(double maxGain=0, double maxLoss=0) {
	if (maxGain==0&&maxLoss==0){
		maxGain=quality->getGain();
		maxLoss=quality->getLoss();
	}
	if (maxGain>0)
		quality->setGain(quality->getGain()/maxGain);
	if (maxLoss>0)
		quality->setLoss(quality->getLoss()/maxLoss);
	for CHILDS
		CHILD->normalize(maxGain, maxLoss);
}

void Node::setAggregated(bool aggregated) {
	this->aggregated = aggregated;
}

double Node::computeAggregation(float parameter) {
	if (!hasChild()){
		aggregated=true;
		return 0;
	}else{
		double nodeQuality=parameter*quality->getGain()-(1-parameter)*quality->getLoss();
		double childQuality=0.0;
		for CHILDS
			childQuality+=CHILD->computeAggregation(parameter);
		aggregated=(childQuality<nodeQuality);
		return max(childQuality, nodeQuality);
	}
}

vector<int> * Node::computeBestPartitions() {
	vector<int> *bestPartitions = new vector<int>();
	fillBestPartitions(bestPartitions, 0);
	return bestPartitions;

}

int Node::fillBestPartitions(vector<int>*bestPartition, int p) {
	if (aggregated){
		for (int i=0; i<size; i++)
			bestPartition->push_back(p);
	}else{
		for CHILDS
			p = CHILD->fillBestPartitions(bestPartition, p);
	}
	return p +1;
}
