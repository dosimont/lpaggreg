/*
 * NodeLPAggregWrapper.cpp
 *
 *  Created on: 20 août 2013
 *      Author: dosimont
 */

#include "NodeLPAggregWrapper.h"

NodeLPAggregWrapper::NodeLPAggregWrapper(): root(0){
	// TODO Auto-generated constructor stub
}

NodeLPAggregWrapper::~NodeLPAggregWrapper() {
	// TODO Auto-generated destructor stub
}

void NodeLPAggregWrapper::computeQualities(bool normalization) {
	root->computeQuality();
}

void NodeLPAggregWrapper::computeAggregation(float parameter) {
	aggregatedId.clear();
	root->computeAggregation(parameter);
	root->computeBestPartitions();
	computeAggregatedId(root);
}
//TODO
void NodeLPAggregWrapper::computeDichotomy(float threshold) {
}

bool NodeLPAggregWrapper::isAggregated(int id) {
	return aggregatedId[id];
}

void NodeLPAggregWrapper::computeAggregatedId(NodeLPAggreg* node) {
	if (node->isAggregated())
		aggregatedId[node->getId()]=true;
	else
		aggregatedId[node->getId()]=false;
	if (!node->hasChild())
		return;
	for NCHILDS(node)
		computeAggregatedId(NCHILD(node));
}
