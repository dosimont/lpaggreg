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

#include "DLPAggreg2.h"

DLPAggreg2::DLPAggreg2() :
		DLPAggreg(), values(0), sumValue(0), microInfo(0), valueISize(0) {
}

DLPAggreg2::DLPAggreg2(int id) :
		DLPAggreg(id), values(0), sumValue(0), microInfo(0), valueISize(0) {
}

DLPAggreg2::DLPAggreg2(int id, const vector<vector<double> >& values) :
		DLPAggreg(0, id), values(values), sumValue(0), microInfo(0), valueISize(0) {
}

DLPAggreg2::DLPAggreg2(DLPAggreg2* parent, int id, const vector<vector<double> >& values) :
		DLPAggreg(parent, id) {
	setValues(values);
}

DLPAggreg2::~DLPAggreg2() {
	for (int i=valueSize-1; i>=0; i--) {
		delete sumValue[i];
		delete microInfo[i];
	}
	delete sumValue;
	delete microInfo;
}

const vector<vector<double> >& DLPAggreg2::getValues() const {
	return values;
}

void DLPAggreg2::computeQualities() {
	if (hasChild()) {
		nodeSize = 0;
		eval->incrQCounter();
		for DCHILDS {
			DCHILD2->computeQualities();
			nodeSize+=DCHILD2->getNodeSize();
			eval->incrQCounter();
		}
		valueSize = static_cast<DLPAggreg2*>(childNodes[0])->getValueSize();
		valueISize = static_cast<DLPAggreg2*>(childNodes[0])->getValueISize();
		eval->incrQCounter(2);
	}
	else {
		valueSize = values.size();
		valueISize=values[0].size();
		nodeSize = 1;
		eval->incrQCounter(3);
	}
	sumValue = new double**[valueSize];
	microInfo = new double**[valueSize];
	for (int i = 0; i < valueSize; i++) {
		sumValue[i] = new double*[valueSize];
		microInfo[i] = new double*[valueSize];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < valueSize; j++){
			qualities[i].push_back(new Quality(0, 0));
			sumValue[i][j] = new double[valueISize];
			microInfo[i][j] = new double[valueISize];
			eval->incrQCounter();
		}
	}
	if (!hasChild()) {
		for (int i = 0; i < valueSize; i++) {
			for (int k = 0; k < valueISize; k++){
				sumValue[i][0][k] = values[i][k];
				microInfo[i][0][k] = entropyReduction(values[i][k], 0);
			eval->incrQCounter(2);
			}
		}
		for (int j = 1; j < valueSize; j++) {
			for (int i = 0; i < valueSize - j; i++) {
				for (int k = 0; k < valueISize; k++){
				sumValue[i][j][k] = sumValue[i][j - 1][k] + sumValue[i + j][0][k];
				microInfo[i][j][k] = microInfo[i][j - 1][k] + microInfo[i + j][0][k];
				qualities[i][j]->addToGain(
						entropyReduction(sumValue[i][j][k], microInfo[i][j][k]));
				qualities[i][j]->addToLoss(
						divergence(j + 1, sumValue[i][j][k], microInfo[i][j][k]));
				eval->incrQCounter(4);
				}
			}
		}
	}
	else {
		for (int j = 0; j < valueSize; j++) {
			for (int i = 0; i < valueSize - j; i++) {
				for (int k = 0; k < valueISize; k++){
				sumValue[i][j][k] = 0;
				microInfo[i][j][k] = 0;
				eval->incrQCounter(2);
				for DCHILDS {
					sumValue[i][j][k]+=DCHILD2->getSumValue()[i][j][k];
					microInfo[i][j][k]+=DCHILD2->getMicroInfo()[i][j][k];
					eval->incrQCounter(2);
				}
				qualities[i][j]->addToGain(
						entropyReduction(sumValue[i][j][k], microInfo[i][j][k]));
				qualities[i][j]->addToLoss(
						divergence((j + 1)*nodeSize, sumValue[i][j][k],
								microInfo[i][j][k]));
				eval->incrQCounter(2);
			}
			}
		}
	}
}

void DLPAggreg2::computeQualities(bool normalization) {
	if (!hasParent()) {
		setEval(new Eval);
		eval->resetQCounter();
		eval->startQTimer();
		computeQualities();
		if (normalization)
			normalize();
		eval->stopQTimer();
	}
}

double*** DLPAggreg2::getMicroInfo() const {
	return microInfo;
}

double*** DLPAggreg2::getSumValue() const {
	return sumValue;
}

void DLPAggreg2::setValues(const vector<vector<double> >& values) {
	this->values = values;
}

int DLPAggreg2::getValueISize() const {
	return valueISize;
}
