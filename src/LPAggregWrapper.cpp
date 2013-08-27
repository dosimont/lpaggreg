/*******************************************************************************
 *
 * This library is a C++ implementation of an algorithm designed by Robin
 * Lamarche-Perrin. This algorithm enables to aggregate sets of scalar or vector
 * data, according aggregation gain & information loss ratio parameter.
 * More information in "Robin Lamarche-Perrin, Yves Demazeau and Jean-Marc
 * Vincent. The Best-partitions Problem: How to Build Meaningful Agregations?
 * Research report RR-LIG-XXX, Laboratoire d’Informatique de Grenoble, France,
 * Feb. 2013. (forthcoming)"
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


LPAggregWrapper::LPAggregWrapper(int dimension) :
parts(vector<int>()), dimension(dimension){
	switch(dimension){
	case 1:{
		values1=LPValues<1, double>();
		aggreg1=LPAggreg<vector<double> >();
		break;
	}
	case 2:{
		values2=LPValues<2, double>();
		aggreg2=LPAggreg<vector< vector<double> > >();
		break;
	}
	case 3:{
		values3=LPValues<3, double>();
		aggreg3=LPAggreg<vector< vector< vector<double> > > >();
		break;
	}
	}
}

LPAggregWrapper::~LPAggregWrapper() {
	parts.clear();
}

int LPAggregWrapper::getPart(int index) {
	if (index < getPartNumber())
		return parts[index];
	return -1;
}

int LPAggregWrapper::getPartNumber() {
	return (int)parts.size();
}

int LPAggregWrapper::getParameterNumber() {
	return (int)parameters.size();
}

float LPAggregWrapper::getParameter(int index) {
	if (index < getParameterNumber())
		return parameters[index];
	return -1;
}

double LPAggregWrapper::getGainByIndex(int index) {
	if (index<(int) qualities.size())
		return qualities[index]->getGain();
	return -1;
}

double LPAggregWrapper::getGainByParameter(float parameter) {
	for (int i=0; i<(int) parameters.size(); i++)
		if (parameter==parameters[i])
		   return qualities[i]->getGain();
	return -1;
}

double LPAggregWrapper::getLossByIndex(int index) {
	if (index<(int) qualities.size())
		return qualities[index]->getLoss();
	return -1;
}

double LPAggregWrapper::getLossByParameter(float parameter) {
	for (int i=0; i<(int) parameters.size(); i++)
		if (parameter==parameters[i])
		   return qualities[i]->getLoss();
	return -1;
}


void LPAggregWrapper::computeParts(float parameter) {
	parts.clear();
	switch(dimension){
	case 1:
		parts=aggreg1.getParts(parameter); break;
	case 2:
		parts=aggreg2.getParts(parameter); break;
	case 3:
		parts=aggreg3.getParts(parameter); break;
	}
}

void LPAggregWrapper::computeQualities(bool normalization) {
	switch(dimension){
	case 1:{
		aggreg1.setValues(values1.getValues());
		aggreg1.computeQualities(normalization);
		break;
	}
	case 2:{
		aggreg2.setValues(values2.getValues());
		aggreg2.computeQualities(normalization);
		break;
	}
	case 3:{
		aggreg3.setValues(values3.getValues());
		aggreg3.computeQualities(normalization);
		break;
	}
	}
}

void LPAggregWrapper::computeDichotomy(float threshold) {
	switch(dimension){
	case 1:{
		parameters=aggreg1.getParameters(threshold);
		qualities=aggreg1.getQualityList();
		break;
	}
	case 2:{
		parameters=aggreg2.getParameters(threshold);
		qualities=aggreg2.getQualityList();
		break;
	}
	case 3:{
		parameters=aggreg3.getParameters(threshold);
		qualities=aggreg3.getQualityList();
		break;
	}
	}
}

void LPAggregWrapper::setValue(int i, double value) {
	switch(dimension){
	case 1:{
		values1.setValue(i, value);
		break;
	}
	}
}

void LPAggregWrapper::push_back(double value) {
	switch(dimension){
	case 1:{
		values1.push_back(value);
		break;
	}
	case 2:{
		values2.push_back(value);
		break;
	}
	case 3:{
		values3.push_back(value);
		break;
	}
	}
}

void LPAggregWrapper::addVector() {
	switch(dimension){
	case 2:{
		values2.addVector();
		break;
	}
	case 3:{
		values3.addVector();
		break;
	}
	}
}

void LPAggregWrapper::setValue(int i, int j, double value) {
	switch(dimension){
	case 2:{
		values2.setValue(i, j, value);
		break;
	}
	}
}

void LPAggregWrapper::push_back(int i, double value) {
	switch(dimension){
	case 2:{
		values2.push_back(i, value);
		break;
	}
	}
}

void LPAggregWrapper::addMatrix() {
	switch(dimension){
	case 3:{
		values3.addMatrix();
		break;
	}
	}
}

void LPAggregWrapper::setValue(int i, int j, int k, double value) {
	switch(dimension){
	case 3:{
		values3.setValue(i, j, k, value);
		break;
	}
	}
}

void LPAggregWrapper::addVector(int i) {
	switch(dimension){
	case 3:{
		values3.addVector(i);
		break;
	}
	}
}

void LPAggregWrapper::push_back(int i, int j, double value) {
	switch(dimension){
	case 3:{
		values3.push_back(i, j, value);
		break;
	}
	}
}
