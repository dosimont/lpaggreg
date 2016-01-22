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
#include <omp.h>

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

#ifdef OPENMP /* Parallel version */

	int nbthreads = omp_get_max_threads();

	double*** sumValues = new double**[nbthreads];
	double*** entValues = new double**[nbthreads];

	/*Temporal matrix of quality measures : */
	vector<vector<Quality*> >* qualitiesTmp = new vector<vector<Quality*> >[nbthreads];

	/* initialization */
	for(int k=0;k<nbthreads;k++){
		sumValues[k] = new double*[n];
		entValues[k] = new double*[n];
		for (int i = 0; i < n; i++) {
			sumValues[k][i] = new double[n];
			entValues[k][i] = new double[n];
			qualitiesTmp[k].push_back(vector<Quality*>());
			for (int j = 0; j < n; j++) {
				qualitiesTmp[k][i].push_back(new Quality(0, 0));
			}
		}
	}

	for (int i = 0; i < n; i++) {
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < n; j++) {
			qualities[i].push_back(new Quality(0, 0));
			EVALQC(2);
		}
	}

	//Other levels
	#pragma omp parallel for shared(m,l,n,qualitiesTmp,sumValues,entValues) num_threads(nbthreads) schedule(static)
	for (int k = 0; k < m; k++) {
		for (int o = 0; o < l; o++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n - i; j++) {
					int numt = omp_get_thread_num();

	#if SIZEREDUCTION
					qualitiesTmp[numt][i][j]->setGain(i);
					EVALQC(1);
	#endif
					//Microscopic level
					if (i == 0) {
						sumValues[numt][i][j] = this->values[j][k][o];
						entValues[numt][i][j] = entropyReduction(sumValues[numt][i][j], 0);
						EVALQC(2);
					} else {
						//Other levels
						sumValues[numt][i][j] = sumValues[numt][i - 1][j]
										+ sumValues[numt][0][i + j];
						entValues[numt][i][j] = entValues[numt][i - 1][j]
										+ entValues[numt][0][i + j];
	#if ENTROPY
						qualitiesTmp[numt][i][j]->addToGain(
						                    entropyReduction(sumValues[numt][i][j],
											entValues[numt][i][j]));
	#endif
						qualitiesTmp[numt][i][j]->addToLoss(
						                    divergence(i + 1, sumValues[numt][i][j],
											entValues[numt][i][j]));
						EVALQC(4);
					}
				}
			}
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n-i;j++){
			for(int k=0;k<nbthreads;k++){
				qualities[i][j]->addToGain(qualitiesTmp[k][i][j]->getGain());
				qualities[i][j]->addToLoss(qualitiesTmp[k][i][j]->getLoss());
			}
		}
	}

	if (normalization) {
		normalize(n);
	}

	for (int i = 0; i < nbthreads; i++) {
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;

	for (int k = 0; k < nbthreads; k++) {
		for (unsigned int i = 0; i < qualitiesTmp[k].size(); i++) {
			for (unsigned int j = 0; j < qualitiesTmp[k][i].size(); j++) {
				if (&qualitiesTmp[k][i][j] != 0){
					delete qualitiesTmp[k][i][j];
				}
			}
			qualitiesTmp[k][i].clear();
		}
		qualitiesTmp[k].clear();
	}
	delete[] qualitiesTmp;

#else /* Serial version */

	double ** sumValues = new double*[n];
	double ** entValues = new double*[n];

	/* initialization */

	for (int i = 0; i < n; i++) {
		sumValues[i] = new double[n];
		entValues[i] = new double[n];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j < n; j++) {
			qualities[i].push_back(new Quality(0, 0));
			EVALQC(2);
		}
	}

	//Other levels
	for (int k = 0; k < m; k++) {
		for (int o = 0; o < l; o++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n - i; j++) {
	#if SIZEREDUCTION
					qualities[i][j]->setGain(i);
					EVALQC(1);
	#endif
					//Microscopic level
					if (i == 0) {
						sumValues[i][j] = this->values[j][k][o];
						entValues[i][j] = entropyReduction(sumValues[i][j], 0);
						EVALQC(2);
					} else {
						//Other levels
						sumValues[i][j] = sumValues[i - 1][j]
										+ sumValues[0][i + j];
						entValues[i][j] = entValues[i - 1][j]
										+ entValues[0][i + j];
	#if ENTROPY
						qualities[i][j]->addToGain(
									        entropyReduction(sumValues[i][j],
											entValues[i][j]));
	#endif
						qualities[i][j]->addToLoss(
									        divergence(i + 1, sumValues[i][j],
											entValues[i][j]));
						EVALQC(4);
					}
				}
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

#endif

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

