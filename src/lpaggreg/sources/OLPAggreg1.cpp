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

#include "OLPAggreg1.h"

OLPAggreg1::OLPAggreg1() :
		OLPAggreg() {
}

void OLPAggreg1::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	setSize(values.size());
	int n = this->getSize();
	EVALQC_;
	double ** sumValues = new double*[n];
	double ** entValues = new double*[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double[n];
		entValues[i] = new double[n];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < n; j++) {
			qualities[i].push_back(new Quality(0, 0)); //WRITE*2
			EVALQC(2);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) { //WRITE*4

			//Microscopic level
			if (i == 0) {
				sumValues[0][j] = this->values[j]; //WRITE
				entValues[0][j] = entropyReduction(sumValues[0][j], 0); //WRITE
				EVALQC(2);
			} else //Other levels
			{
				sumValues[i][j] = sumValues[i - 1][j] + sumValues[0][i + j];
				entValues[i][j] = entValues[i - 1][j] + entValues[0][i + j];
#if ENTROPY
				qualities[i][j]->setGain(
						entropyReduction(sumValues[i][j], entValues[i][j]));
#endif
#if SIZEREDUCTION
				qualities[i][j]->setGain(i);
#endif
				qualities[i][j]->setLoss(
						divergence(i + 1, sumValues[i][j], entValues[i][j]));
				EVALQC(4);
			}
		}
	}
	if (normalization) {
		normalize(n);
	}
	for (int i = 0; i < n; i++) {
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

OLPAggreg1::OLPAggreg1(const vector<double>& values) :
		OLPAggreg(), values(values) {
}

void OLPAggreg1::setValues(const vector<double>& values) {
	this->values = values;
}

OLPAggreg1::~OLPAggreg1() {
	// TODO Auto-generated destructor stub
}

unsigned int OLPAggreg1::getSize() {
	return values.size();
}

void OLPAggreg1::computeQualities(bool normalization) {
	deleteQualities();
	EVALSTARTQ;
#if ENTROPY
	computeQualitiesSpe(normalization);
#endif
#if SIZEREDUCTION
	computeQualitiesSpe(true);
#endif
	EVALSTOPQ;
}
