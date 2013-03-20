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

#include "LPAggreg.h"

LPAggreg::LPAggreg(bool normalization) :
		normalization(normalization), size(0), loss(0), gain(0), bestCuts(0), bestPartitions(
				0) {
	
}

LPAggreg::~LPAggreg() {
	deleteQualities();
	deleteBestPartitions();
}

inline double LPAggreg::entropy(double value) {
	return value * log(value) / log(2);
	
}

double LPAggreg::entropyReduction(double value, double ent) {
	if (value > 0)
		return entropy(value) - ent;
	else
		return 0;
}

double LPAggreg::divergence(int size, double value, double ent) {
	return value * log(size) / log(2) - entropyReduction(value, ent);
	
}

bool LPAggreg::isNormalization() const {
	return normalization;
}

void LPAggreg::setNormalization(bool normalization) {
	this->normalization = normalization;
}

int LPAggreg::getSize() const {
	return size;
}

void LPAggreg::setSize(int size) {
	this->size = size;
}

void LPAggreg::computeBestCuts(float parameter) {
	int n = getSize();
	bestCuts = new int*[n];
	double ** bestQuality = new double*[n];
	for (int i = 0; i < n; i++) {
		bestCuts[i] = new int[n];
		bestQuality[i] = new double[n];
	}
	for (int j = 0; j < n; j++) {
		bestCuts[0][j] = 0;
		bestQuality[0][j] = 0;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			long currentCut = 0;
			double currentQuality = parameter * gain[i][j]
					- (1 - parameter) * loss[i][j];
			for (int k = 1; k < i + 1; k++) {
				double quality = bestQuality[k - 1][j]
						+ bestQuality[i - k][j + k];
				if (quality > currentQuality) {//TODO have replaced >= by > ; to verify
					currentCut = k;
					currentQuality = quality;
				}
				bestCuts[i][j] = currentCut;
				bestQuality[i][j] = currentQuality;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] bestQuality[i];
	}
	delete[] bestQuality;
}

void LPAggreg::computeBestPartitions() {
	int n = getSize();
	for (int i = 0; i < n; i++)
		bestPartitions.push_back(-1);
	fillPartition(n - 1, 0, 0);
	
}

int LPAggreg::fillPartition(int i, int j, int p) {
	int c = bestCuts[i][j];
	if (c > 0) {
		p = fillPartition(c - 1, j, p);
		p = fillPartition(i - c, j + c, p);
		return p;
	}
	else {
		for (int k = 0; k < i + 1; k++) {
			bestPartitions[j + k] = p;
		}
		return p + 1;
	}
}

void LPAggreg::init() {
	computeQualities();
}

vector<int> LPAggreg::process(float parameter) {
	deleteBestPartitions();
	computeBestCuts(parameter);
	computeBestPartitions();
	deleteBestCuts();
	return bestPartitions;
}

LPAggreg::LPAggreg() :
		normalization(false), size(0), loss(0), gain(0), bestCuts(0), bestPartitions(
				0) {
}

void LPAggreg::deleteBestCuts() {
	int n = getSize();
	for (int i = 0; i < n; i++) {
		delete[] bestCuts[i];
	}
	delete[] bestCuts;
}

void LPAggreg::deleteQualities() {
	int n = getSize();
	for (int i = 0; i < n; i++) {
		delete[] gain[i];
		delete[] loss[i];
	}
	delete[] gain;
	delete[] loss;
}

void LPAggreg::deleteBestPartitions() {
	bestPartitions.clear();
}
