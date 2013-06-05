/*
 * VMLPAggregWrapper.cpp
 *
 *  Created on: 5 juin 2013
 *      Author: dosimont
 */

#include "MLPAggregWrapper.h"


MLPAggregWrapper::MLPAggregWrapper() :
LPAggregWrapper(), aggregator(MatrixLPAggreg()), values(vector< vector < vector <double> > >()){
}

MLPAggregWrapper::~MLPAggregWrapper() {
	for (int i=0; i<getMatrixNumber(); i++){
		for (int j=0; j<getMatrixSize(); j++)
			values[i][j].clear();
		values[i].clear();
	}
	values.clear();
	parts.clear();
}

void MLPAggregWrapper::newVector() {
	values[values.size()-1].push_back(vector<double>());
}

void MLPAggregWrapper::addToVector(double element) {
	values[values.size()-1][values[values.size()-1].size()-1].push_back(element);
}

void MLPAggregWrapper::addToVector(double element, int index) {
	if (index<(int)values[values.size()-1].size())
		values[values.size()-1][index].push_back(element);
}

int MLPAggregWrapper::getMatrixNumber() {
	return (int)values.size();
}

void MLPAggregWrapper::newMatrix() {
	values.push_back(vector< vector<double> >());
}

void MLPAggregWrapper::addToMatrix(double element, int index) {
	if (index<(int)values.size())
		values[index][values[index].size()-1].push_back(element);
}

void MLPAggregWrapper::addToMatrix(double element, int i, int j) {
	if ((i<(int)values.size())&&(j<(int)values[i].size()))
		values[i][j].push_back(element);
}

int MLPAggregWrapper::getMatrixSize() {
	for (int i=0; (i<getMatrixNumber()-1) && (getMatrixNumber()>1) ; i++){
		if (values[i].size()!=values[i+1].size())
			return -1;
	}
	if (getMatrixNumber()>0)
		return values[0].size();
	else
		return -1;
}

int MLPAggregWrapper::getVectorSize() {
	for (int i=0; (i<getMatrixSize()-1) && (getMatrixSize()>1) ; i++){
		if (values[0][i].size()!=values[0][i+1].size())
			return -1;
	}
	if (getMatrixSize()>0)
		return values[0][0].size();
	else
		return -1;
}

void MLPAggregWrapper::computeParts(float parameter) {
	parts.clear();
	parts=aggregator.getParts(parameter);
}

void MLPAggregWrapper::computeQualities(bool normalization) {
	aggregator.setValues(values);
	aggregator.init(normalization);
}

void MLPAggregWrapper::computeDichotomy(float threshold) {
	parameters=aggregator.getParameters(threshold);
	qualities=aggregator.getQualities();
}

