/*
 * DLPPartition.cpp
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#include "DLPCut.h"

DLPCut::DLPCut() :
		cut(0), aggregated(false) {
}

bool DLPCut::isAggregated() const {
	return aggregated;
}

void DLPCut::setAggregated(bool aggregated) {
	this->aggregated = aggregated;
}

int DLPCut::getCut() const {
	return cut;
}

DLPCut::DLPCut(int partition, bool aggregated) :
		cut(partition), aggregated(aggregated) {
}

void DLPCut::setCut(int partition) {
	this->cut = partition;
}

DLPCut::~DLPCut() {
}

void DLPCut::setAll(int partition, bool aggregated) {
	this->cut = partition;
	this->aggregated = aggregated;
}
