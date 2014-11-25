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
		dimension(dimension), root(0){
	switch (dimension) {
	case 1: {
		values1 = map<int, LPValues<1, double> >();

		break;
	}
	case 2: {
		values2 = map<int, LPValues<2, double> >();
		break;

	}
	}
	aggreg = map<int, DLPAggreg*>();
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

double DLPAggregWrapper::getGainByParameter(double parameter) {
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

double DLPAggregWrapper::getLossByParameter(double parameter) {
	for (int i = 0; i < (int) parameters.size(); i++)
		if (parameter == parameters[i])
			return qualities[i]->getLoss();
	return -1;
}

void DLPAggregWrapper::computeParts(double parameter) {
	root->computeAggregation(parameter);
}

void DLPAggregWrapper::computeQualities(bool normalization) {
	switch (dimension) {
	case 1: {
		DLPAggreg1 *aggreg1 = static_cast<DLPAggreg1*>(root);
		aggreg1->computeQualities(false);
		break;
	}
	case 2: {
		static_cast<DLPAggreg2*>(root)->computeQualities(false);
		break;
	}
	}
}

void DLPAggregWrapper::computeDichotomy(float threshold) {
	parameters=root->getParameters(threshold);
	qualities=root->getQualityList();
	
}

void DLPAggregWrapper::setValue(int id, int i, double value) {
	switch (dimension) {
	case 1: {
		values1[id].setValue(i, value);
		break;
	}
	}
}

void DLPAggregWrapper::push_back(int id, double value) {
	switch (dimension) {
	case 1: {
		values1[id].push_back(value);
		break;
	}
	case 2: {
		values2[id].push_back(value);
		break;
	}
	}
}

void DLPAggregWrapper::addVector(int id) {
	switch (dimension) {
	case 2: {
		values2[id].addVector();
		break;
	}
	}
}

void DLPAggregWrapper::setValue(int id, int i, int j, double value) {
	switch (dimension) {
	case 2: {
		values2[id].setValue(i, j, value);
		break;
	}
	}
}

int DLPAggregWrapper::newRoot(int id) {
	switch (dimension) {
		case 1: {
			DLPAggreg1 * temp=new DLPAggreg1(id);
			aggreg.insert(pair<int, DLPAggreg1*>(id,temp));
			root=temp;
			return temp->getId();
			break;
		}
		case 2: {
			root=new DLPAggreg2(id);
			aggreg[id]=root;
			return aggreg[id]->getId();
			break;
		}
	}
	return -1;
}

void DLPAggregWrapper::validate() {
	map<int,DLPAggreg*>::iterator it;
	for (it = aggreg.begin(); it!=aggreg.end(); it++){
		int id=it->first;
		DLPAggreg* node=it->second;
		if (!node->hasChild()){
			switch (dimension) {
				case 1: {
					DLPAggreg1 * temp=static_cast<DLPAggreg1*>(node);
					temp->setValues(values1[id].getValues());
					break;
				}
				case 2: {
					DLPAggreg2 * temp=static_cast<DLPAggreg2*>(node);
					temp->setValues(values2[id].getValues());
					break;
				}
			}
		}
	}
}

DLPAggregWrapper::~DLPAggregWrapper() {
	delete root;
}

bool DLPAggregWrapper::hasFullAggregation(int id) {
	return aggreg[id]->hasFullAggregation();
}

void DLPAggregWrapper::push_back(int id, int i, double value) {
	switch (dimension) {
	case 2: {
		values2[id].push_back(i, value);
		break;
	}
	}
}

int DLPAggregWrapper::newLeaf(int id, int parent) {
	switch (dimension) {
	case 1: {
		DLPAggreg1 * temp=new DLPAggreg1(static_cast<DLPAggreg1*>(aggreg[parent]), id);
		aggreg.insert(pair<int, DLPAggreg1*>(id,temp));
		values1.insert(pair<int, LPValues<1, double> >(id, LPValues<1, double>()));
		return temp->getId();
		break;
	}
	case 2: {
		DLPAggreg2 * temp=new DLPAggreg2(static_cast<DLPAggreg2*>(aggreg[parent]), id);
		aggreg.insert(pair<int, DLPAggreg2*>(id,temp));
		values2.insert(pair<int, LPValues<2, double> >(id, LPValues<2, double>()));
		return temp->getId();
		break;
	}
	}
	return -1;
}

int DLPAggregWrapper::newNode(int id, int parent) {
	switch (dimension) {
	case 1: {
		aggreg[parent]->hasParent();
		DLPAggreg1 * temp=new DLPAggreg1(static_cast<DLPAggreg1*>(aggreg[parent]), id);
		aggreg.insert(pair<int, DLPAggreg1*>(id,temp));
		return temp->getId();
		break;
	}
	case 2: {
		aggreg[parent]->getRank();
		DLPAggreg2 * temp=new DLPAggreg2(static_cast<DLPAggreg2*>(aggreg[parent]), id);
		aggreg.insert(pair<int, DLPAggreg2*>(id,temp));
		return temp->getId();
		break;
	}
	}
	return -1;
}

DLPAggreg*& DLPAggregWrapper::getRoot(){
	return root;
}
