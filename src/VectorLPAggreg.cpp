/*******************************************************************************
 *
 * This library is a C++ implementation of an algorithm designed by Robin
 * Lamarche-Perrin. This algorithm enables to aggregate sets of scalar or vector
 * data, according aggregation gain & information loss ratio parameter.
 * More information in "Robin Lamarche-Perrin, Yves Demazeau and Jean-Marc
 * Vincent. The Best-partitions Problem: How to Build Meaningful Agregations?
 * Research report RR-LIG-XXX, Laboratoire d’Informatique de Grenoble, France,
 * Feb. 2013. (forthcoming)"
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

/*Author : Damien Dosimont <damien.dosimont@imag.fr>*/

/*VectorLPAggreg cpp file
 *
 * Class that enables to perform LP aggregation on vectors. Inherits from
 * virtual LPAggreg class.
 */

#include "VectorLPAggreg.h"

VectorLPAggreg::VectorLPAggreg(vector< vector<double> > values):
	LPAggreg(), values(values) {
		setSize(this->values.size());
}

void VectorLPAggreg::setValues(const vector<vector<double> >& values) {
	this->values = values;
	setSize(this->values.size());
}

VectorLPAggreg::VectorLPAggreg():
	LPAggreg(), values(0) {
		setSize(this->values.size());
}

void VectorLPAggreg::computeQualities(bool normalization) {
	//Init and allocation
	int n = getSize();
	int m = values[0].size();
	double *** sumValues = new double**[n];
	double *** entValues = new double**[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double*[n];
		entValues[i] = new double*[n];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j<n; j++){
			sumValues[i][j] = new double[m];
			entValues[i][j] = new double[m];
			qualities[i].push_back(new Quality(0,0));
			eval.incrQCounter(2);
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		for (int k =0; k< m; k++){
			sumValues[0][j][k] = values[j][k];
			entValues[0][j][k] = entropyReduction(sumValues[0][j][k], 0);
			eval.incrQCounter(2);
		}
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			for (int k =0; k< m; k++){
			sumValues[i][j][k] = sumValues[i - 1][j][k] + sumValues[0][i + j][k];
			entValues[i][j][k] = entValues[i - 1][j][k] + entValues[0][i + j][k];
			qualities[i][j]->addToGain(entropyReduction(sumValues[i][j][k], entValues[i][j][k]));
			qualities[i][j]->addToLoss(divergence(i + 1, sumValues[i][j][k], entValues[i][j][k]));
			eval.incrQCounter(4);
			}
		}
	}
	if (normalization) {
		Quality * maxQuality = new Quality(qualities[n-1][0]->getGain(), qualities[n-1][0]->getLoss());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				qualities[i][j]->setGain(qualities[i][j]->getGain()/maxQuality->getGain());
				qualities[i][j]->setLoss(qualities[i][j]->getLoss()/maxQuality->getLoss());
				eval.incrQCounter(2);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j=0; j < n; j++){
			delete[] sumValues[i][j];
			delete[] entValues[i][j];
		}
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

