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

#include "OLPAggreg3.h"

OLPAggreg3::OLPAggreg3() :
		OLPAggreg() {
	// TODO Auto-generated constructor stub
	
}

void OLPAggreg3::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	setSize(values.size());
	int n = this->getSize();
	int m = this->values[0].size();
	int l = this->values[0][0].size();
	double ** sumValues = new double*[n];
	double ** entValues = new double*[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double[m*l];
		entValues[i] = new double[m*l];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < n; j++) {
			qualities[i].push_back(new Quality(0, 0));
			EVALQC(2);
		}
	}
	int o, ktemp;
	//Microscopic level
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < m*l; k++) {
			o = k % l;
			ktemp = (int) (k / l);
			
				sumValues[j][k] = this->values[j][ktemp][o];
				entValues[j][k] = entropyReduction(sumValues[j][k],	0);
				EVALQC(2);
		}
	}
	o=0;
	ktemp =0;
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
#if SIZEREDUCTION
			qualities[i][j]->setGain(i);
#endif
			for (int k = 0; k < m*l; k++) {
				o = k % l;
				ktemp = (int) (k / l);

				/*if(i == 1)
				{
					sumValues[j][k] = this->values[j][ktemp][o];
					entValues[j][k] = entropyReduction(sumValues[j][k], 0);
				}*/
				
				sumValues[j][k] = sumValues[j][k] + this->values[i+j][ktemp][o];
				entValues[j][k] = entValues[j][k] + entropyReduction(this->values[i+j][ktemp][o], 0);
				
					/*sumValues[i][j][k][o] = sumValues[i - 1][j][k][o]
							+ sumValues[0][i + j][k][o];
					entValues[i][j][k][o] = entValues[i - 1][j][k][o]
							+ entValues[0][i + j][k][o];*/
#if ENTROPY
					qualities[i][j]->addToGain(
							entropyReduction(sumValues[j][k],
									entValues[j][k]));
#endif
					qualities[i][j]->addToLoss(
							divergence(i + 1, sumValues[j][k],
									entValues[j][k]));
					EVALQC(4);
			}
		}
	}
	if (normalization) {
		Quality * maxQuality = new Quality(qualities[n - 1][0]->getGain(),
				qualities[n - 1][0]->getLoss());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				qualities[i][j]->setGain(
						qualities[i][j]->getGain() / maxQuality->getGain());
				qualities[i][j]->setLoss(
						qualities[i][j]->getLoss() / maxQuality->getLoss());
				EVALQC(2);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		/*for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				delete[] sumValues[i][j][k];
				delete[] entValues[i][j][k];
			}
			delete[] sumValues[i][j];
			delete[] entValues[i][j];
		}*/
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

OLPAggreg3::OLPAggreg3(const vector<vector<vector<double> > >& values) :
		OLPAggreg(), values(values) {
}

void OLPAggreg3::setValues(const vector<vector<vector<double> > >& values) {
	this->values = values;
}

OLPAggreg3::~OLPAggreg3() {
	// TODO Auto-generated destructor stub
}

unsigned int OLPAggreg3::getSize() {
	return values.size();
}

void OLPAggreg3::computeQualities(bool normalization) {
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
