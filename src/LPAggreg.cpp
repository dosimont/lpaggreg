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

/*LPAggreg cpp file
 *
 * Virtual class that contains methods enabling to perform LP aggregation computation
 * and get aggregated parts, a list of relevant parameters obtained by dichotomy and
 * their associated quality measures
 *
 * computeQualities(bool normalization) method is virtual and need to be implemented
 * in child classes
 */

#include "LPAggreg.h"

LPAggreg::~LPAggreg() {
	deleteQualities();
	deleteBestPartitions();
	deleteParameters();
	deleteQualitiesD();
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
	return value * log(size) / log(2)  - entropyReduction(value, ent);
}

int LPAggreg::getSize() const {
	return size;
}

void LPAggreg::setSize(int size) {
	this->size = size;
}

void LPAggreg::computeBestCuts(float parameter) {
	int n = getSize();
//	bestCuts = new int*[n];
//	double ** bestQuality = new double*[n];
//	for (int i = 0; i < n; i++) {
//		bestCuts[i] = new int[n];
//		bestQuality[i] = new double[n];
//	}
//	for (int j = 0; j < n; j++) {
//		bestCuts[0][j] = 0;
//		bestQuality[0][j] = 0;
//	}
	bestCuts = new int[n];
	double * bestQuality = new double[n];
	bestCuts[0] = 0;
	bestQuality[0] = 0;
	for (int i = 1; i < n; i++) {
		//for (int j = 0; j < n - i; j++) {
			long currentCut = 0;
			double currentQuality = parameter * qualities[i][0]->getGain()
					- (1 - parameter) * qualities[i][0]->getLoss();
			for (int k = 1; k < i + 1; k++) {
				double quality = bestQuality[k - 1] + parameter * qualities[i-k][k]->getGain()-(1-parameter) * qualities[i-k][k]->getLoss();
				if (quality > currentQuality) {//TODO have replaced >= by > ; to verify
					currentCut = k;
					currentQuality = quality;
				}
				bestCuts[i] = currentCut;
				bestQuality[i] = currentQuality;

		}
	}
	delete[] bestQuality;
}

void LPAggreg::computeBestPartitions() {
	int n = getSize();
	for (int i = 0; i < n; i++)
		bestPartitions.push_back(-1);
	fillPartition(n - 1, 0);
	
}

int LPAggreg::fillPartition(int i, int p) {
	int c = bestCuts[i];
	if (c > 0)
		p = fillPartition(c - 1, p);
	for (int k = c; k < i + 1; k++)
		bestPartitions[k] = p;
	return p + 1;
}

void LPAggreg::init(bool normalization) {
	deleteQualities();
	computeQualities(normalization);

}

vector<int> LPAggreg::getParts(float parameter) {
	deleteBestPartitions();
	computeBestCuts(parameter);
	computeBestPartitions();
	deleteBestCuts();
	return bestPartitions;
}

LPAggreg::LPAggreg():
		size(0), qualities(vector< vector<Quality*> >()), bestCuts(0), bestPartitions(vector<int>()), parametersD(vector<float>()), qualitiesD(vector<Quality*>()) {
}

void LPAggreg::deleteBestCuts() {
	delete[] bestCuts;
}

void LPAggreg::deleteQualities() {
	for (unsigned int i = 0; i < qualities.size(); i++) {
		for (unsigned int j=0; j < qualities[i].size(); j++){
			if (&qualities[i][j]!=0)
				delete qualities[i][j];
		}
		qualities[i].clear();
	}
	qualities.clear();
}

void LPAggreg::deleteBestPartitions() {
	bestPartitions.clear();
}

void LPAggreg::computeBestQualities(float threshold) {
	Quality *bestQualityParam0=new Quality();
	Quality *bestQualityParam1=new Quality();
	computeBestCuts(0);
	computeBestQuality(bestQualityParam0);
	deleteBestCuts();
	parametersD.push_back(0);
	qualitiesD.push_back(bestQualityParam0);
	computeBestCuts(1);
	computeBestQuality(bestQualityParam1);
	deleteBestCuts();
	addBestQualities(0, 1, bestQualityParam0, bestQualityParam1, threshold);
	parametersD.push_back(1);
	qualitiesD.push_back(bestQualityParam1);
	for (unsigned int i=qualitiesD.size()-1; i>0; i--){
		if ((qualitiesD[i]->getGain()==qualitiesD[i-1]->getGain())&&(qualitiesD[i]->getLoss()==qualitiesD[i-1]->getLoss())){
			delete qualitiesD[i];
			qualitiesD.erase(qualitiesD.begin()+i);
			parametersD.erase(parametersD.begin()+i);
		}
	}
}

void LPAggreg::computeBestQuality(Quality *bestQuality) {
	int n = getSize();
	bestQuality->setGain(0);
	bestQuality->setLoss(0);
	fillQuality(n-1, bestQuality);
}

void LPAggreg::fillQuality(int i, Quality *bestQuality) {
	int c = bestCuts[i];
	if (c > 0) {
		fillQuality(c - 1,bestQuality);
	}
	bestQuality->addToGain(qualities[i-c][c]->getGain());//
	bestQuality->addToLoss(qualities[i-c][c]->getLoss());
}

void LPAggreg::addBestQualities(float parameter1, float parameter2,	Quality *bestQuality1, Quality *bestQuality2, float threshold) {
	if (!(((bestQuality1->getGain()==bestQuality2->getGain())&&(bestQuality1->getLoss()==bestQuality2->getLoss()))||(parameter2-parameter1<=threshold))){
	float parameter = parameter1 + ((parameter2 -parameter1) / 2);
	Quality *bestQuality=new Quality();
	computeBestCuts(parameter);
	computeBestQuality(bestQuality);
	deleteBestCuts();
	addBestQualities(parameter1, parameter, bestQuality1, bestQuality, threshold);
	parametersD.push_back(parameter);
	qualitiesD.push_back(bestQuality);
	addBestQualities(parameter, parameter2, bestQuality, bestQuality2, threshold);
	}
}

vector<float> LPAggreg::getParameters(float threshold) {
	deleteParameters();
	deleteQualitiesD();
	computeBestQualities(threshold);
	return parametersD;
}

void LPAggreg::deleteQualitiesD() {
	for (unsigned int i=0; i<qualitiesD.size(); i++)
		delete qualitiesD[i];
	qualitiesD.clear();
}

void LPAggreg::deleteParameters() {
	parametersD.clear();
}

int LPAggreg::sizeReduction(int size) {
	return size-1;
}
