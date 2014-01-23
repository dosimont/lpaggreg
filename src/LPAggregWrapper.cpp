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

#include "LPAggregWrapper.h"

LPAggregWrapper::LPAggregWrapper(int dimension) :
		parts(vector<int>()), dimension(dimension) {
	switch (dimension) {
	case 1: {
		values1 = LPValues<1, double>();
		aggreg = new OLPAggreg1();
		break;
	}
	case 2: {
		values2 = LPValues<2, double>();
		aggreg = new OLPAggreg2();
		break;
	}
	case 3: {
		values3 = LPValues<3, double>();
		aggreg = new OLPAggreg3();
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
	return (int) parts.size();
}

int LPAggregWrapper::getParameterNumber() {
	return (int) parameters.size();
}

float LPAggregWrapper::getParameter(int index) {
	if (index < getParameterNumber())
		return parameters[index];
	return -1;
}

double LPAggregWrapper::getGainByIndex(int index) {
	if (index < (int) qualities.size())
		return qualities[index]->getGain();
	return -1;
}

double LPAggregWrapper::getGainByParameter(float parameter) {
	for (int i = 0; i < (int) parameters.size(); i++)
		if (parameter == parameters[i])
			return qualities[i]->getGain();
	return -1;
}

double LPAggregWrapper::getLossByIndex(int index) {
	if (index < (int) qualities.size())
		return qualities[index]->getLoss();
	return -1;
}

double LPAggregWrapper::getLossByParameter(float parameter) {
	for (int i = 0; i < (int) parameters.size(); i++)
		if (parameter == parameters[i])
			return qualities[i]->getLoss();
	return -1;
}

void LPAggregWrapper::computeParts(float parameter) {
	parts.clear();
	parts = aggreg->getParts(parameter);
}

void LPAggregWrapper::computeQualities(bool normalization) {
	switch (dimension) {
	case 1: {
		OLPAggreg1 *aggreg1 = static_cast<OLPAggreg1*>(aggreg);
		aggreg1->setValues(values1.getValues());
		aggreg1->computeQualities(normalization);
		break;
	}
	case 2: {
		OLPAggreg2 *aggreg2 = static_cast<OLPAggreg2*>(aggreg);
		aggreg2->setValues(values2.getValues());
		aggreg2->computeQualities(normalization);
		break;
	}
	case 3: {
		OLPAggreg3 *aggreg3 = static_cast<OLPAggreg3*>(aggreg);
		aggreg3->setValues(values3.getValues());
		aggreg3->computeQualities(normalization);
		break;
	}
	}
}

void LPAggregWrapper::computeDichotomy(float threshold) {
	parameters = aggreg->getParameters(threshold);
	qualities = aggreg->getQualityList();
	
}

void LPAggregWrapper::setValue(int i, double value) {
	switch (dimension) {
	case 1: {
		values1.setValue(i, value);
		break;
	}
	}
}

void LPAggregWrapper::push_back(double value) {
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

void LPAggregWrapper::addVector() {
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

void LPAggregWrapper::setValue(int i, int j, double value) {
	switch (dimension) {
	case 2: {
		values2.setValue(i, j, value);
		break;
	}
	}
}

void LPAggregWrapper::push_back(int i, double value) {
	switch (dimension) {
	case 2: {
		values2.push_back(i, value);
		break;
	}
	}
}

void LPAggregWrapper::addMatrix() {
	switch (dimension) {
	case 3: {
		values3.addMatrix();
		break;
	}
	}
}

void LPAggregWrapper::setValue(int i, int j, int k, double value) {
	switch (dimension) {
	case 3: {
		values3.setValue(i, j, k, value);
		break;
	}
	}
}

void LPAggregWrapper::addVector(int i) {
	switch (dimension) {
	case 3: {
		values3.addVector(i);
		break;
	}
	}
}

void LPAggregWrapper::push_back(int i, int j, double value) {
	switch (dimension) {
	case 3: {
		values3.push_back(i, j, value);
		break;
	}
	}
}
