/*
 * Node.cpp
 *
 *  Created on: 25 juil. 2013
 *      Author: dosimont
 */

#include "Node.h"


Node::Node(): id(0), value(0), parent(0), childNodes(vector<Node*>()), quality(new Quality(0,0)), aggregate(false), size(0), entSum(0){
	// TODO Auto-generated constructor stub
	
}

Node::Node(Node* parent, int id=0): id(id), value(0), parent(parent), childNodes(vector<Node*>()), quality(new Quality(0,0)), aggregate(false), size(0), entSum(0){
	parent->addChild(this);
}

void Node::addChild(Node *child) {
	childNodes.push_back(child);
	child->setParent(this);
}

void Node::updateParents() {
	if (hasChild()){
		value=0;
		for (unsigned int i=0; i<childNodes.size(); i++)
			value+=childNodes[i]->getValue();
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
	for (unsigned int i=0; i<childNodes.size(); i++)
		delete childNodes[i];
	delete quality;
}

bool Node::isAggregate() const {
	return aggregate;
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
		for (unsigned int i=0; i<childNodes.size(); i++){
			childNodes[i]->computeQuality();
			value+=childNodes[i]->getValue();
			entSum+=childNodes[i]->getEntSum();
			size+=childNodes[i]->getSize();
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
