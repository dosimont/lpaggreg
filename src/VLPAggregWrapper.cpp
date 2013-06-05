/*
 * VVLPAggregWrapper.cpp
 *
 *  Created on: 5 juin 2013
 *      Author: dosimont
 */

#include "VLPAggregWrapper.h"


VLPAggregWrapper::VLPAggregWrapper() :
LPAggregWrapper(), aggregator(VectorLPAggreg()), values(vector< vector<double> >()){
}

VLPAggregWrapper::~VLPAggregWrapper() {
	for (int i=0; i<getVectorNumber(); i++)
		values[i].clear();
	values.clear();
	parts.clear();
}

void VLPAggregWrapper::newVector() {
	values.push_back(vector<double>());
}

void VLPAggregWrapper::addToVector(double element) {
	values[values.size()-1].push_back(element);
}

void VLPAggregWrapper::addToVector(double element, int index) {
	if (index<(int)values.size())
	values[index].push_back(element);
}

int VLPAggregWrapper::getVectorNumber() {
	return (int)values.size();
}

int VLPAggregWrapper::getVectorSize() {
	for (int i=0; (i<getVectorNumber()-1) && (getVectorNumber()>1) ; i++){
		if (values[i].size()!=values[i+1].size())
			return -1;
	}
	if (getVectorNumber()>0)
		return values[0].size();
	else
		return -1;
}

void VLPAggregWrapper::computeParts(float parameter) {
	parts.clear();
	parts=aggregator.getParts(parameter);
}

void VLPAggregWrapper::computeQualities(bool normalization) {
	aggregator.setValues(values);
	aggregator.init(normalization);
}

void VLPAggregWrapper::computeDichotomy(float threshold) {
	parameters=aggregator.getParameters(threshold);
	qualities=aggregator.getQualities();
}

