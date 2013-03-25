/*******************************************************************************
 *
 * This library is a C++ implementation of an algorithm designed by Robin
 * Lamarche-Perrin. This algorithm allows to aggregate sets of scalar or vector
 * data, according aggregation gain & information loss ratio parameter.
 * More information in "R. Lamarche-Perrin & al. - The Best-partitions Problem:
 * How to Build Meaningful Aggregations? in ..."
 *
 * (C) Copyright (February 28th 2013) Damien Dosimont. All rights reserved.
 *
 * Damien Dosimont <damien.dosimont@imag.fr>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 *******************************************************************************/

#include "LPAggregWrapper.h"


LPAggregWrapper::LPAggregWrapper() :
aggregator(VectorLPAggreg()), values(vector< vector<double> >()), parts(vector<int>()){
}

LPAggregWrapper::~LPAggregWrapper() {
	for (int i=0; i<getVectorsNumber(); i++)
		values[i].clear();
	values.clear();
	parts.clear();
}

void LPAggregWrapper::newVector() {
	values.push_back(vector<double>());
}

void LPAggregWrapper::addToVector(double element) {
	values[values.size()-1].push_back(element);
}

void LPAggregWrapper::addToVector(double element, int index) {
	if (index<(int)values.size())
	values[index].push_back(element);
}

int LPAggregWrapper::getVectorsNumber() {
	return (int)values.size();
}

int LPAggregWrapper::getVectorSize() {
	for (int i=0; (i<getVectorsNumber()-1) && (getVectorsNumber()>1) ; i++){
		if (values[i].size()!=values[i+1].size())
			return -1;
	}
	if (getVectorsNumber()>0)
		return values[0].size();
	else
		return -1;
}

void LPAggregWrapper::computeParts(float parameter) {
	parts.clear();
	parts=aggregator.process(parameter);
}

void LPAggregWrapper::computeQualities(bool normalization) {
	aggregator.setValues(values);
	aggregator.init(normalization);
}

int LPAggregWrapper::getPart(int index) {
	if (index < getPartsNumber())
		return parts[index];
	return -1;
}

int LPAggregWrapper::getPartsNumber() {
	return (int)parts.size();
}

void LPAggregWrapper::computeDichotomy(float threshold) {
	parameters=aggregator.dichotomy(threshold);
}

int LPAggregWrapper::getParametersNumber() {
	return (int)parameters.size();
}

float LPAggregWrapper::getParameter(int index) {
	if (index < getParametersNumber())
		return parameters[index];
	return -1;
}
