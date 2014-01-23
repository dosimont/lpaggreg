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

#include "NLPAggreg3.h"

NLPAggreg3::NLPAggreg3() :
		NLPAggreg() {
}

NLPAggreg3::NLPAggreg3(int id, const vector<vector<double> >& values) :
		NLPAggreg(0, id) {
	setValues(values);
}

NLPAggreg3::NLPAggreg3(NLPAggreg3* parent, int id,
		const vector<vector<double> >& values) :
		NLPAggreg(parent, id) {
	setValues(values);
}

NLPAggreg3::~NLPAggreg3() {
	// TODO Auto-generated destructor stub
}

const vector<vector<double> >& NLPAggreg3::getValues() const {
	return values;
}

void NLPAggreg3::setValues(const vector<vector<double> >& values) {
	this->values = values;
}

void NLPAggreg3::computeQualities(bool normalization) {
	if (!hasParent()) {
		setEval(new Eval);
		_EVALSTARTQ;
		computeQuality();
		if (normalization)
			normalize();
		_EVALSTOPQ;
	}
}

void NLPAggreg3::computeQuality() {
	for (unsigned int i = 0; i < this->values.size(); i++)
		for (unsigned int j = 0; j < this->values[i].size(); j++)
			computeQuality_Matrix(i, j);
}

void NLPAggreg3::computeQuality_Matrix(int i, int j) {
	if (!hasChild()) {
		entSum = entropyReduction(this->values[i][j], 0);
		size = 1;
		_EVALQC(2);
	}
	else {
		this->values[i][j] = 0;
		entSum = 0;
		size = 0;
		_EVALQC(3);
		for CHILDS {
			static_cast<NLPAggreg3*>(CHILD)->computeQuality_Matrix(i, j);
			this->values[i][j]+=static_cast<NLPAggreg3*>(CHILD)->getValues()[i][j];
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			_EVALQC(3);
		}
		if (i == 0 && j == 0) {
			quality->setGain(0);
			quality->setLoss(0);
		}
		quality->addToGain(entropyReduction(this->values[i][j], entSum));
		quality->addToLoss(divergence(size, this->values[i][j], entSum));
		_EVALQC(2);
	}
}

