/*******************************************************************************
 * Copyright or © or Copr. Damien Dosimont (February 28th 2013)
 * 
 * Damien Dosimont <damien.dosimont@imag.fr> 
 * 
 * This software is a C++ implementation of an algorithm designed by Robin 
 * Lamarche-Perrin available under the form of a shared library. This algorithm 
 * allows to aggregate sets of scalar or vector data, according aggregation 
 * gain and information loss parameters.
 * More information in "R. Lamarche-Perrin & al. - The Best-partitions Problem: 
 * How to Build Meaningful Aggregations? in ..."
 *
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software. You can use, modify
 * and/ or redistribute the software under the terms of the CeCILL-C license as
 * circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * As a counterpart to the access to the source code and rights to copy, modify
 * and redistribute granted by the license, users are provided only with a
 * limited warranty and the software's author, the holder of the economic
 * rights, and the successive licensors have only limited liability.
 * 
 * In this respect, the user's attention is drawn to the risks associated with
 * loading, using, modifying and/or developing or reproducing the software by
 * the user in light of its specific status of free software, that may mean that
 * it is complicated to manipulate, and that also therefore means that it is
 * reserved for developers and experienced professionals having in-depth
 * computer knowledge. Users are therefore encouraged to load and test the
 * software's suitability as regards their requirements in conditions enabling
 * the security of their systems and/or data to be ensured and, more generally,
 * to use and operate it in the same conditions as regards security.
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 * 
 * 
 * Copyright ou © ou Copr. Damien Dosimont (28 Février 2013)
 * 
 * Damien Dosimont <damien.dosimont@imag.fr> 
 * 
 * Ce programme est une implémentation en C++ d'un algorithme conçu par Robin
 * Lamarche-Perrin et disponible sous la forme d'une bibliothèque partagée.
 * Cet algorithme permet d'agréger un échantillon de données numériques (scalaires
 * ou vectorielles) en fonction du gain apporté par l'agrégation ainsi que la perte
 * d'information.
 * Plus d"information dans la publication :
 * "R. Lamarche-Perrin & al. - The Best-partitions Problem:  * How to Build 
 * Meaningful Aggregations? in ..."
 *
 * Ce logiciel est régi par la licence CeCILL-C soumise au droit français et
 * respectant les principes de diffusion des logiciels libres. Vous pouvez
 * utiliser, modifier et/ou redistribuer ce programme sous les conditions de la
 * licence CeCILL-C telle que diffusée par le CEA, le CNRS et l'INRIA sur le
 * site "http://www.cecill.info".
 * 
 * En contrepartie de l'accessibilité au code source et des droits de copie, de
 * modification et de redistribution accordés par cette licence, il n'est offert
 * aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons, seule une
 * responsabilité restreinte pèse sur l'auteur du programme, le titulaire des
 * droits patrimoniaux et les concédants successifs.
 * 
 * A cet égard l'attention de l'utilisateur est attirée sur les risques associés
 * au chargement, à l'utilisation, à la modification et/ou au développement et à
 * la reproduction du logiciel par l'utilisateur étant donné sa spécificité de
 * logiciel libre, qui peut le rendre complexe à manipuler et qui le réserve
 * donc à des développeurs et des professionnels avertis possédant des
 * connaissances informatiques approfondies. Les utilisateurs sont donc invités
 * à charger et tester l'adéquation du logiciel à leurs besoins dans des
 * conditions permettant d'assurer la sécurité de leurs systèmes et ou de leurs
 * données et, plus généralement, à l'utiliser et l'exploiter dans les mêmes
 * conditions de sécurité.
 * 
 * Le fait que vous puissiez accéder à cet en-tête signifie que vous avez pris
 * connaissance de la licence CeCILL-C, et que vous en avez accepté les termes.
 ******************************************************************************/

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

VectorLPAggreg::~VectorLPAggreg() {
}

void VectorLPAggreg::computeQualities(bool normalization) {
	//Init and allocation
	int n = getSize();
	int m = values[0].size();
	double *** sumValues = new double**[n];
	double *** entValues = new double**[n];
	gain = new double*[n];
	loss = new double*[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double*[n];
		entValues[i] = new double*[n];
		gain[i] = new double[n];
		loss[i] = new double[n];
		for (int j = 0; j<n; j++){
			sumValues[i][j] = new double[m];
			entValues[i][j] = new double[m];
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		for (int k =0; k< m; k++){
			sumValues[0][j][k] = values[j][k];
			entValues[0][j][k] = this->entropyReduction(sumValues[0][j][k], 0);
		}
		gain[0][j] = 0;
		loss[0][j] = 0;
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			gain[i][j] = 0;
			loss[i][j] = 0;
			for (int k =0; k< m; k++){
			sumValues[i][j][k] = sumValues[i - 1][j][k] + sumValues[0][i + j][k];
			entValues[i][j][k] = entValues[i - 1][j][k] + entValues[0][i + j][k];
			gain[i][j] += this->entropyReduction(sumValues[i][j][k], entValues[i][j][k]);
			loss[i][j] += this->divergence(i + 1, sumValues[i][j][k], entValues[i][j][k]);
			}
		}
	}
	if (normalization) {
		double maxGain = gain[n - 1][0];
		double maxLoss = gain[n - 1][0];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				gain[i][j] /= maxGain;
				loss[i][j] /= maxLoss;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

