/*
 * Node.cpp
 *
 *  Created on: 25 juil. 2013
 *      Author: dosimont
 */

#include "Node.h"


Node::Node() {
	// TODO Auto-generated constructor stub
	
}

const vector<Node>& Node::getChildren() const {
	return children;
}

void Node::setChildren(const vector<Node>& children) {
	this->children = children;
}

double Node::getValue() const {
	return value;
}

void Node::setValue(double value) {
	this->value = value;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

