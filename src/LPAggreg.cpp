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


template<typename Value>
void LPAggreg<Value>::computeQualities(bool normalization,
		vector<double> values) {
	//Init and allocation
	int n = getSize();
	double ** sumValues = new double*[n];
	double ** entValues = new double*[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double[n];
		entValues[i] = new double[n];
		qualities.push_back(vector<Quality*>());
		for (int j=0; j<n; j++){
			qualities[i].push_back(new Quality(0,0));//WRITE*2
			eval.incrQCounter(2);
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		sumValues[0][j] = values[j];//WRITE
		entValues[0][j] = entropyReduction<double>(sumValues[0][j], 0);//WRITE
		eval.incrQCounter(2);
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {//WRITE*4
			sumValues[i][j] = sumValues[i - 1][j] + sumValues[0][i + j];
			entValues[i][j] = entValues[i - 1][j] + entValues[0][i + j];
			qualities[i][j]->setGain(entropyReduction(sumValues[i][j], entValues[i][j]));
			qualities[i][j]->setLoss(divergence(i + 1, sumValues[i][j], entValues[i][j]));
			eval.incrQCounter(4);
		}
	}
	if (normalization) {
		Quality * maxQuality = new Quality(qualities[n-1][0]->getGain(), qualities[n-1][0]->getLoss());//WRITE
		eval.incrQCounter();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {//WRITE*2
				qualities[i][j]->setGain(qualities[i][j]->getGain()/maxQuality->getGain());
				qualities[i][j]->setLoss(qualities[i][j]->getLoss()/maxQuality->getLoss());
				eval.incrQCounter(2);
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

template<typename Value>
void LPAggreg<Value>::computeQualities(bool normalization,
		vector< vector <double> > values) {
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
			entValues[0][j][k] = entropyReduction<double>(sumValues[0][j][k], 0);
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

template<typename Value>
void LPAggreg<Value>::computeQualities(bool normalization,
		vector< vector <vector<double> > > values) {
	//Init and allocation
	int n = getSize();
	int m = values[0].size();
	int l = values[0][0].size();
	double **** sumValues = new double***[n];
	double **** entValues = new double***[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double**[n];
		entValues[i] = new double**[n];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j<n; j++){
			sumValues[i][j] = new double*[m];
			entValues[i][j] = new double*[m];
			qualities[i].push_back(new Quality(0,0));
			eval.incrQCounter(2);
			for (int k = 0; k<m; k++){
				sumValues[i][j][k] = new double[l];
				entValues[i][j][k] = new double[l];
			}
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < m; k++){
			for (int o = 0; o < l; o++){
				sumValues[0][j][k][o] = values[j][k][o];
				entValues[0][j][k][o] = entropyReduction<double>(sumValues[0][j][k][o], 0);
				eval.incrQCounter(2);
			}
		}
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			for (int k =0; k< m; k++){
				for (int o = 0; o < l; o++){
					sumValues[i][j][k][o] = sumValues[i - 1][j][k][o] + sumValues[0][i + j][k][o];
					entValues[i][j][k][o] = entValues[i - 1][j][k][o] + entValues[0][i + j][k][o];
					qualities[i][j]->addToGain(entropyReduction(sumValues[i][j][k][o], entValues[i][j][k][o]));
					qualities[i][j]->addToLoss(divergence(i + 1, sumValues[i][j][k][o], entValues[i][j][k][o]));
					eval.incrQCounter(4);
				}
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
			for (int k=0; k<m; k++){
				delete[] sumValues[i][j][k];
				delete[] entValues[i][j][k];
			}
			delete[] sumValues[i][j];
			delete[] entValues[i][j];
		}
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

template<typename Value>
void LPAggreg<Value>::deleteQualities() {
	for (unsigned int i = 0; i < qualities.size(); i++) {
		for (unsigned int j = 0; j < qualities[i].size(); j++) {
			if (&qualities[i][j] != 0)
				delete qualities[i][j];
		}
		qualities[i].clear();
	}
	qualities.clear();
}

template<typename Value>
int LPAggreg<Value>::sizeReduction(int size) {
	return size - 1;
}

template<typename Value>
void LPAggreg<Value>::computeBestCuts(float parameter) {
	int n = getSize();
	bestCuts = new int[n];
	double * bestQuality = new double[n];
	bestCuts[0] = 0; //WRITE
	bestQuality[0] = 0; //WRITE	int n = getSize();
	for (int i = 0; i < n; i++) {
		bestPartitions.push_back(-1); //WRITE
		eval.incrBPCounter();
	}
	fillPartition(n - 1, 0);
	eval.incrBCCounter(2);
	for (int i = 1; i < n; i++) {
		long currentCut = 0; //WRITE
		double currentQuality = parameter * qualities[i][0]->getGain() //WRITE
		- (1 - parameter) * qualities[i][0]->getLoss();
		eval.incrBCCounter(2);
		for (int k = 1; k < i + 1; k++) { //WRITE
			double quality = bestQuality[k - 1]
					+ parameter * qualities[i - k][k]->getGain()
					- (1 - parameter) * qualities[i - k][k]->getLoss();
			eval.incrBCCounter();
			if (quality > currentQuality) { //TODO have replaced >= by > ; to verify
				currentCut = k; //WRITE*2
				currentQuality = quality;
				eval.incrBCCounter(2);
			}
			bestCuts[i] = currentCut; //WRITE*2
			bestQuality[i] = currentQuality;
			eval.incrBCCounter(2);
		}
	}
	delete[] bestQuality;
}

template<typename Value>
void LPAggreg<Value>::deleteBestCuts() {
	delete[] bestCuts;
}

template<typename Value>
void LPAggreg<Value>::computeBestPartitions() {
	int n = getSize();
	for (int i = 0; i < n; i++) {
		bestPartitions.push_back(-1); //WRITE
		eval.incrBPCounter();
	}
	fillPartition(n - 1, 0);
}

template<typename Value>
void LPAggreg<Value>::deleteBestPartitions() {
	bestPartitions.clear();
}

template<typename Value>
int LPAggreg<Value>::fillPartition(int i, int p) {
	int c = bestCuts[i]; //WRITE
	eval.incrBPCounter();
	if (c > 0) {
		p = fillPartition(c - 1, p); //WRITE
		eval.incrBPCounter();
	}
	for (int k = c; k < i + 1; k++) {
		bestPartitions[k] = p; //WRITE
		eval.incrBPCounter();
	}
	return p + 1;
}

template<typename Value>
void LPAggreg<Value>::setSize(int size) {
	this->size=size;
}

template<typename Value>
void LPAggreg<Value>::computeBestQualities(float threshold) {
	Quality *bestQualityParam0 = new Quality();
	Quality *bestQualityParam1 = new Quality();
	computeBestCuts(0);
	computeBestQuality(bestQualityParam0);
	deleteBestCuts();
	parameters.push_back(0);
	qualityList.push_back(bestQualityParam0);
	computeBestCuts(1);
	computeBestQuality(bestQualityParam1);
	deleteBestCuts();
	addBestQualities(0, 1, bestQualityParam0, bestQualityParam1, threshold);
	parameters.push_back(1);
	qualityList.push_back(bestQualityParam1);
	for (unsigned int i = qualityList.size() - 1; i > 0; i--) {
		if ((qualityList[i]->getGain() == qualityList[i - 1]->getGain())
				&& (qualityList[i]->getLoss() == qualityList[i - 1]->getLoss())) {
			delete qualityList[i];
			qualityList.erase(qualityList.begin() + i);
			parameters.erase(parameters.begin() + i);
		}
	}
}

template<typename Value>
void LPAggreg<Value>::computeBestQuality(Quality* bestQuality) {
	int n = getSize();
	bestQuality->setGain(0);
	bestQuality->setLoss(0);
	fillQuality(n - 1, bestQuality);
}

template<typename Value>
void LPAggreg<Value>::fillQuality(int i, Quality* bestQuality) {
	int c = bestCuts[i];
	if (c > 0) {
		fillQuality(c - 1, bestQuality);
	}
	bestQuality->addToGain(qualities[i - c][c]->getGain());
	bestQuality->addToLoss(qualities[i - c][c]->getLoss());
}

template<typename Value>
void LPAggreg<Value>::addBestQualities(float parameter1, float parameter2,
		Quality* bestQuality1, Quality* bestQuality2, float threshold) {
	if (!(((bestQuality1->getGain() == bestQuality2->getGain())
			&& (bestQuality1->getLoss() == bestQuality2->getLoss()))
			|| (parameter2 - parameter1 <= threshold))) {
		float parameter = parameter1 + ((parameter2 - parameter1) / 2);
		Quality *bestQuality = new Quality();
		computeBestCuts(parameter);
		computeBestQuality(bestQuality);
		deleteBestCuts();
		addBestQualities(parameter1, parameter, bestQuality1, bestQuality,
				threshold);
		parameters.push_back(parameter);
		qualityList.push_back(bestQuality);
		addBestQualities(parameter, parameter2, bestQuality, bestQuality2,
				threshold);
	}
}

template<typename Value>
void LPAggreg<Value>::deleteQualityList() {
	for (unsigned int i = 0; i < qualityList.size(); i++)
		delete qualityList[i];
	qualityList.clear();
}

template<typename Value>
void LPAggreg<Value>::deleteParameters() {
	parameters.clear();
}

template<typename Value>
LPAggreg<Value>::LPAggreg(Value values): size(0), qualities(vector< vector<Quality*> >()), bestCuts(0), bestPartitions(vector<int>()), parameters(vector<float>()), qualityList(vector<Quality*>()) {
	this->values=values;
}

template<typename Value>
LPAggreg<Value>::LPAggreg():
		size(0), qualities(vector< vector<Quality*> >()), bestCuts(0), bestPartitions(vector<int>()), parameters(vector<float>()), qualityList(vector<Quality*>()) {
}

template<typename Value>
LPAggreg<Value>::~LPAggreg() {
	deleteQualities();
	deleteBestPartitions();
	deleteParameters();
	deleteQualityList();
}

template<typename Value>
void LPAggreg<Value>::setValues(const Value& values) {
	this->values = values;
}

template<typename Value>
int LPAggreg<Value>::getSize() const {
	return getSize(this->values);
}


template<typename Value>
int LPAggreg<Value>::getSize(vector<double> values) {
	return values.size();
}

template<typename Value>
int LPAggreg<Value>::getSize(vector<vector<double> > values) {
	return values.size();
}

template<typename Value>
int LPAggreg<Value>::getSize(vector<vector<vector<double> > > values) {
	return values.size();
}

template<typename Value>
void LPAggreg<Value>::computeQualities(bool normalization) {
	deleteQualities();
	eval.resetQCounter();
	eval.startQTimer();
	computeQualities(normalization, this->values);
	eval.stopQTimer();
}

template<typename Value>
vector<int> LPAggreg<Value>::getParts(float parameter) {
	deleteBestPartitions();
	eval.resetBCCounter();
	eval.startBCTimer();
	computeBestCuts(parameter);
	eval.stopBCTimer();
	eval.resetBPCounter();
	eval.startBPTimer();
	computeBestPartitions();
	eval.stopBPTimer();
	deleteBestCuts();
	return bestPartitions;
}

template<typename Value>
vector<float> LPAggreg<Value>::getParameters(float threshold) {
	deleteParameters();
	deleteQualityList();
	computeBestQualities(threshold);
	return parameters;

}

template<typename Value>
const vector<Quality*>& LPAggreg<Value>::getQualityList() const {
	return qualityList;
}

template<typename Value>
int LPAggreg<Value>::getQualityDuration() {
	return eval.getQDuration();
}

template<typename Value>
int LPAggreg<Value>::getBestCutDuration() {
	return eval.getBCDuration();
}

template<typename Value>
int LPAggreg<Value>::getBestPartitionDuration() {
	return eval.getBPDuration();
}

template<typename Value>
int LPAggreg<Value>::getQualityCount() {
	return eval.getQCount();
}

template<typename Value>
int LPAggreg<Value>::getBestCutCount() {
	return eval.getBCCount();
}

template<typename Value>
int LPAggreg<Value>::getBestPartitionCount() {
	return eval.getBPCount();
}



