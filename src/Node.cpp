/*
 * Node.cpp
 *
 *  Created on: 25 juil. 2013
 *      Author: dosimont
 */

#include "Node.h"


Node::Node(): value(0), parent(0), childNodes(vector<Node*>()), childValues(vector<double>()), quality(new Quality(0,0)){
	// TODO Auto-generated constructor stub
	
}

//Node::Node(Node parent): value(0), parent(parent), childNodes(vector<Node>()), childValues(new vector<double>), quality(Quality(0,0)){
//	updateParents();
//}

void Node::addChild(Node *child) {
	childNodes.push_back(child);
	updateParents();
}

void Node::addChild(double child) {
	childValues.push_back(child);
	updateParents();
}

void Node::updateParents() {
	value=0;
	for (unsigned int i=0; i<childValues.size(); i++)
		value+=childValues[i];
	for (unsigned int i=0; i<childNodes.size(); i++)
		value+=childNodes[i]->getValue();
	if (parent!=0)
		parent->updateParents();
}

vector<Node*>Node::getChildNodes(int i){
	return childNodes[i];
}

vector<double> Node::getChildValues(int i){
	return childValues[i];
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

double Node::getValue(){
	return value;
}

Node::~Node() {
	for (unsigned int i=0; i<childNodes.size(); i++)
		delete childNodes[i];
	delete quality;
}

void Node::setParent(Node* parent) {
	this->parent = parent;
}

bool Node::hasChild() {
	return !childNodes.empty();
}
