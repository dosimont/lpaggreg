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

#include "NLPAggreg1.h"

NLPAggreg1::NLPAggreg1() :
		NLPAggreg() {
	this->values = 0;
}

double NLPAggreg1::getValues() const {
	return values;
}

void NLPAggreg1::setValues(double values) {
	this->values = values;
}

NLPAggreg1::NLPAggreg1(NLPAggreg1* parent, int id, double values) :
		NLPAggreg(parent, id) {
	setValues(values);
}

NLPAggreg1::NLPAggreg1(int id, double values) :
		NLPAggreg(0, id) {
	setValues(values);
}

NLPAggreg1::~NLPAggreg1() {
	// TODO Auto-generated destructor stub
}

void NLPAggreg1::computeQuality() {
	if (!hasChild()) {
		entSum = entropyReduction(this->values, 0.0);
		size = 1;
		_EVALQC(2);
	}
	else {
		this->values = 0;
		entSum = 0;
		size = 0;
		_EVALQC(3);
		for CHILDS {
			static_cast<NLPAggreg1*>(CHILD)->computeQuality();
			this->values+=static_cast<NLPAggreg1*>(CHILD)->getValues();
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			_EVALQC(3);
		}
		quality->setGain(entropyReduction(this->values, entSum));
		quality->setLoss(divergence(size, this->values, entSum));
		_EVALQC(2);
	}
}

void NLPAggreg1::computeQualities(bool normalization) {
	if (!hasParent()) {
		setEval(new Eval);
		_EVALSTARTQ;
		computeQuality();
		if (normalization)
			normalize();
		_EVALSTOPQ;
	}
}
