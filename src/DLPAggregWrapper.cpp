/*******************************************************************************
 *
 * This library is a C++ implementation of several algorithms that enables
 * to aggregate set of data according: an ordered dimension (OLP), a
 * hierarchy (NLP), or both (DLP). OLP and NLP scalar versions (1) have been
 * designed by Robin Lamarche-Perrin. OLP and NLP vector versions (2, 3) and
 * DLP (1, 2) have been designed by Damien Dosimont and are a generalization
 * of Robin Lamarche-Perrin works.
 *
 * Related works:
 * http://magma.imag.fr/content/robin-lamarche-perrin
 * http://moais.imag.fr/membres/damien.dosimont/research.html
 *
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

#include "DLPAggregWrapper.h"

DLPAggregWrapper::DLPAggregWrapper(int dimension) :
		dimension(dimension){
	switch (dimension) {
	case 1: {
		values1 = LPValues<1, double>();
		root = new DLPAggreg1(0);

		break;
	}
	case 2: {
		values2 = LPValues<2, double>();
		root = new DLPAggreg2(0);
		break;

	}
	}
	aggreg = vector<DLPAggreg*>();
	aggreg.push_back(root);
}


int DLPAggregWrapper::getPart(int id, int index) {
	if (index < getPartNumber())
		return aggreg[id]->getBestPartitions()[index];
	return -1;
}

int DLPAggregWrapper::getPartNumber() {
	return (int) root->getValueSize();
}

int DLPAggregWrapper::getParameterNumber() {
	return (int) parameters.size();
}

float DLPAggregWrapper::getParameter(int index) {
	if (index < getParameterNumber())
		return parameters[index];
	return -1;
}

double DLPAggregWrapper::getGainByIndex(int index) {
	if (index < (int) qualities.size())
		return qualities[index]->getGain();
	return -1;
}

double DLPAggregWrapper::getGainByParameter(float parameter) {
	for (int i = 0; i < (int) parameters.size(); i++)
		if (parameter == parameters[i])
			return qualities[i]->getGain();
	return -1;
}

double DLPAggregWrapper::getLossByIndex(int index) {
	if (index < (int) qualities.size())
		return qualities[index]->getLoss();
	return -1;
}

double DLPAggregWrapper::getLossByParameter(float parameter) {
	for (int i = 0; i < (int) parameters.size(); i++)
		if (parameter == parameters[i])
			return qualities[i]->getLoss();
	return -1;
}

void DLPAggregWrapper::computeParts(float parameter) {
	root->computeAggregation(parameter);
}

void DLPAggregWrapper::computeQualities(bool normalization) {
	switch (dimension) {
	case 1: {
		DLPAggreg1 *aggreg1 = static_cast<DLPAggreg1*>(root);
		aggreg1->computeQualities(normalization);
		break;
	}
	case 2: {
		DLPAggreg2 *aggreg2 = static_cast<DLPAggreg2*>(root);
		aggreg2->computeQualities(normalization);
		break;
	}
	}
}

void DLPAggregWrapper::computeDichotomy(float threshold) {
	parameters=root->getParameters(threshold);
	qualities=root->getQualityList();
	
}

void DLPAggregWrapper::setValue(int i, double value) {
	switch (dimension) {
	case 1: {
		values1.setValue(i, value);
		break;
	}
	}
}

void DLPAggregWrapper::push_back(double value) {
	switch (dimension) {
	case 1: {
		values1.push_back(value);
		break;
	}
	case 2: {
		values2.push_back(value);
		break;
	}
	case 3: {
		values3.push_back(value);
		break;
	}
	}
}

void DLPAggregWrapper::addVector() {
	switch (dimension) {
	case 2: {
		values2.addVector();
		break;
	}
	case 3: {
		values3.addVector();
		break;
	}
	}
}

void DLPAggregWrapper::setValue(int i, int j, double value) {
	switch (dimension) {
	case 2: {
		values2.setValue(i, j, value);
		break;
	}
	}
}

void DLPAggregWrapper::push_back(int i, double value) {
	switch (dimension) {
	case 2: {
		values2.push_back(i, value);
		break;
	}
	}
}

void DLPAggregWrapper::addMatrix() {
	switch (dimension) {
	case 3: {
		values3.addMatrix();
		break;
	}
	}
}

void DLPAggregWrapper::setValue(int i, int j, int k, double value) {
	switch (dimension) {
	case 3: {
		values3.setValue(i, j, k, value);
		break;
	}
	}
}

void DLPAggregWrapper::addVector(int i) {
	switch (dimension) {
	case 3: {
		values3.addVector(i);
		break;
	}
	}
}


void DLPAggregWrapper::push_back(int i, int j, double value) {
	switch (dimension) {
	case 3: {
		values3.push_back(i, j, value);
		break;
	}
	}
}


int DLPAggregWrapper::newElement(int parent) {
	switch (dimension) {
	case 1: {
		DLPAggreg1 * temp=new DLPAggreg1((int) aggreg.size());
		temp->setParent(aggreg[parent]);
		aggreg.push_back(temp);
		return temp->getId();
		break;
	}
	case 2: {
		DLPAggreg2 * temp=new DLPAggreg2((int) aggreg.size());
		temp->setParent(aggreg[parent]);
		aggreg.push_back(temp);
		return temp->getId();
		break;
	}
	}
	return -1;
}

void DLPAggregWrapper::setActiveElement(int id) {

}
