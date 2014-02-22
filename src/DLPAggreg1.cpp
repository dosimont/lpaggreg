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

#include "DLPAggreg1.h"

DLPAggreg1::DLPAggreg1() :
		DLPAggreg(), values(0), sumValue(0), microInfo(0) {
}

DLPAggreg1::DLPAggreg1(int id) :
		DLPAggreg(id), values(0), sumValue(0), microInfo(0) {
}

DLPAggreg1::DLPAggreg1(int id, const vector<double>& values) :
		DLPAggreg(0, id), values(values), sumValue(0), microInfo(0) {
}

DLPAggreg1::DLPAggreg1(DLPAggreg1* parent, int id) :
		DLPAggreg(parent, id), sumValue(0), microInfo(0) {
}

DLPAggreg1::DLPAggreg1(DLPAggreg1* parent, int id, const vector<double>& values) :
		DLPAggreg(parent, id), sumValue(0), microInfo(0) {
	setValues(values);
}

DLPAggreg1::~DLPAggreg1() {
	for (int i=valueSize-1; i>=0; i--) {
		delete sumValue[i];
		delete microInfo[i];
	}
	delete sumValue;
	delete microInfo;
}

const vector<double>& DLPAggreg1::getValues() const {
	return values;
}

void DLPAggreg1::computeQualities() {
	if (hasChild()) {
		nodeSize = 0;
		_EVALQC();
		for DCHILDS {
			DCHILD1->computeQualities();
			nodeSize+=DCHILD1->getNodeSize();
			_EVALQC();
		}
		valueSize = static_cast<DLPAggreg1*>(childNodes[0])->getValueSize();
		_EVALQC();
	}
	else {
		valueSize = values.size();
		nodeSize = 1;
		_EVALQC(2);
	}
	sumValue = new double*[valueSize];
	microInfo = new double*[valueSize];
	for (int i = 0; i < valueSize; i++) {
		sumValue[i] = new double[valueSize];
		microInfo[i] = new double[valueSize];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < valueSize; j++){
			qualities[i].push_back(new Quality());
			_EVALQC();
		}
	}
	if (!hasChild()) {
		for (int i = 0; i < valueSize; i++) {
			sumValue[i][0] = values[i];
			microInfo[i][0] = entropyReduction(values[i], 0);
			_EVALQC(2);
		}
		for (int j = 1; j < valueSize; j++) {
			for (int i = 0; i < valueSize - j; i++) {
				sumValue[i][j] = sumValue[i][j - 1] + sumValue[i + j][0];
				microInfo[i][j] = microInfo[i][j - 1] + microInfo[i + j][0];
#if ENTROPY
				qualities[i][j]->setGain(
						entropyReduction(sumValue[i][j], microInfo[i][j]));
#endif
#if SIZEREDUCTION
				qualities[i][j]->setGain(j+1);
#endif

				qualities[i][j]->setLoss(
						divergence(j + 1, sumValue[i][j], microInfo[i][j]));
				_EVALQC(4);
			}
		}
	}
	else {
		for (int j = 0; j < valueSize; j++) {
			for (int i = 0; i < valueSize - j; i++) {
				sumValue[i][j] = 0;
				microInfo[i][j] = 0;
				_EVALQC(2);
				for DCHILDS {
					sumValue[i][j]+=DCHILD1->getSumValue()[i][j];
					microInfo[i][j]+=DCHILD1->getMicroInfo()[i][j];
					_EVALQC(2);
				}
#if ENTROPY
				qualities[i][j]->setGain(
						entropyReduction(sumValue[i][j], microInfo[i][j]));
#endif
#if SIZEREDUCTION
				qualities[i][j]->setGain((j+1)*(nodeSize-1));
#endif
				qualities[i][j]->setLoss(
						divergence((j + 1)*nodeSize, sumValue[i][j],
								microInfo[i][j]));
				_EVALQC(2);
			}
		}
	}
}

void DLPAggreg1::computeQualities(bool normalization) {
	if (!hasParent()) {
		setEval(new Eval);
		_EVALSTARTQ;
		computeQualities();
#if ENTROPY
		if (normalization)
			normalize();
#endif
#if SIZEREDUCTION
		normalize();
#endif
		_EVALSTOPQ;
	}
}

double** DLPAggreg1::getMicroInfo() const {
	return microInfo;
}

double** DLPAggreg1::getSumValue() const {
	return sumValue;
}

void DLPAggreg1::setValues(const vector<double>& values) {
	this->values = values;
}

