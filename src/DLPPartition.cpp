/*
 * DLPPartition.cpp
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#include "DLPPartition.h"

DLPPartition::DLPPartition(): partition(0), aggregated(false){
}

bool DLPPartition::isAggregated() const {
	return aggregated;
}

void DLPPartition::setAggregated(bool aggregated) {
	this->aggregated = aggregated;
}

int DLPPartition::getPartition() const {
	return partition;
}

DLPPartition::DLPPartition(int partition, bool aggregated): partition(partition), aggregated(aggregated){
}

void DLPPartition::setPartition(int partition) {
	this->partition = partition;
}

DLPPartition::~DLPPartition() {
}

