/*
 * ILPAggreg.h
 *
 *  Created on: 26 août 2013
 *      Author: dosimont
 */

#ifndef LPAGGREG
#define LPAGGREG

#include <iostream>
#include <vector>
#include <math.h>
#include "Quality.h"
#include "Eval.h"
#include "Complexity.h"


using namespace std;

template <typename Value>
class LPAggreg {

	protected:

		/*Number of vector of scalar of input matrix*/
		int size;

		/*Matrix that contains quality measures for each aggregate*/
		vector< vector<Quality*> > qualities;

		/*Tab that contains best cuts for current parameter*/
		int * bestCuts;

		/*Vector that contains best partitions for current parameter*/
		vector<int> bestPartitions;

		/*Vector that contains a list of relevant parameters obtained
		 * by dichomoty computation
		 */
		vector<float> parameters;

		/*Vector that contains qualities related to parameter list*/
		vector<Quality*> qualityList;

		/*Eval class for time and counter measurements*/
		Eval eval;

		Value values;

	public:

		/*Deallocate quality matrix*/
		void deleteQualities();

		/*Size reduction formula method*/
		int sizeReduction(int size);

		/*Compute best cuts for a given parameter p*/
		void computeBestCuts(float parameter);

		/*Deallocate bestCuts pointer*/
		void deleteBestCuts();

		/*Compute aggregation best partitions*/
		void computeBestPartitions();

		/*Delete bestPartitions pointer*/
		void deleteBestPartitions();

		/*Fill partitions*/
		int fillPartition(int i, int p);

		/*Define aggregation matrix size (number of vectors/scalars*/
		void setSize(int size);

		/*Compute best qualities (and parameter list) by dichotomy for a given threshold*/
		void computeBestQualities(float threshold);

		/*Compute best quality*/
		void computeBestQuality(Quality *bestQuality);

		/*Fill quality vector*/
		void fillQuality(int i, Quality *bestQuality);

		/*Add best qualities*/
		void addBestQualities(float parameter1, float parameter2, Quality *bestQuality1, Quality *bestQuality2, float threshold);

		/*Deallocate quality list*/
		void deleteQualityList();

		/*Deallocate parameters list*/
		void deleteParameters();

		void computeQualitiesSpe(bool normalization);

	public:

		/*Constructor*/
		LPAggreg();
		LPAggreg(Value values);

		/*Destructor*/
		virtual ~LPAggreg();

		unsigned int getSize();
		void setValues(const Value& values);
		void computeQualities(bool normalization);
		vector<int> getParts(float parameter);
		vector<float> getParameters(float threshold);
		const vector<Quality*>& getQualityList() const;
		int getQualityDuration(); //ms
		int getBestCutDuration(); //ms
		int getBestPartitionDuration(); //ms
		int getQualityCount();
		int getBestCutCount();
		int getBestPartitionCount();

};

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
			if (quality > currentQuality) {
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
LPAggreg<Value>::LPAggreg():
		size(0), qualities(vector< vector<Quality*> >()), bestCuts(0), bestPartitions(vector<int>()), parameters(vector<float>()), qualityList(vector<Quality*>()), eval(Eval()) {
}

template<typename Value>
LPAggreg<Value>::~LPAggreg() {
	deleteQualities();
	deleteBestPartitions();
	deleteParameters();
	deleteQualityList();
}

template<typename Value>
void LPAggreg<Value>::computeQualities(bool normalization) {
	deleteQualities();
	eval.resetQCounter();
	eval.startQTimer();
	computeQualitiesSpe(normalization);
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

template<>
void LPAggreg< vector<double> >::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	int n = this->getSize();
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
		sumValues[0][j] = this->values[j];//WRITE
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

template<>
void LPAggreg< vector< vector<double> > >::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	int n = this->getSize();
	int m = this->values[0].size();
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
			sumValues[0][j][k] = this->values[j][k];
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

template<>
void LPAggreg< vector <vector< vector<double> > > >::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	int n = this->getSize();
	int m = this->values[0].size();
	int l = this->values[0][0].size();
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
				sumValues[0][j][k][o] = this->values[j][k][o];
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
LPAggreg<Value>::LPAggreg(Value values):
size(0), qualities(vector< vector<Quality*> >()), bestCuts(0), bestPartitions(vector<int>()), parameters(vector<float>()), qualityList(vector<Quality*>()), eval(Eval())
{
	this->values=values;
}

template<typename Value>
LPAggreg<Value>::~LPAggreg() {
}

template<typename Value>
void LPAggreg<Value>::setValues(const Value& values) {
	this->values=values;
}

template<typename Value>
unsigned int LPAggreg<Value>::getSize() {
	return this->values.size();
}


#endif /* LPAGGREG */
