/*
 * DLPAggreg2.cpp
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg2.h"

DLPAggreg2::DLPAggreg2(): DLPAggreg(), values(0){
}

DLPAggreg2::DLPAggreg2(int id, vector<double> values): DLPAggreg(0, id){
	setValues(values);
}

DLPAggreg2::DLPAggreg2(DLPAggreg2* parent, int id, vector<double> values): DLPAggreg(parent, id){
	setValues(values);
}

DLPAggreg2::~DLPAggreg2() {
	// TODO Auto-generated destructor stub
}

const vector<double>& DLPAggreg2::getValues() const {
	return values;
}

void DLPAggreg2::computeQuality() {
	if (hasChild){
		size=0;
		for DCHILDS{
			DCHILD->computeQuality();
			size+=DCHILD->getSize();
		}
	}else{
		value_size=values.size();
		size=1;
		value_size=childNodes[0]->getValues().size();
	}
	sumValue=new double*[value_size];
	microInfo=new double*[value_size];
	for (unsigned int i=0; i<value_size; i++){
		sumValue[i]=new double[value_size];
		microInfo[i]=new double[value_size];
		qualities.push_back(vector<Quality*>());
		for (unsigned int j=0; j<value_size; j++)
			qualities[i].push_back(new Quality());
	}
		if(!hasChild){
			for (unsigned int i=0; i<value_size; i++){
				sumValue[i][0]=values[i];
				microInfo[i][0]=entropyReduction(values[i], 0);
			}
			for (unsigned int j=1; j<value_size; j++){
				for (unsigned int i=0; i<value_size-j; j++){
					sumValue[i][j]=sumValue[i][j-1]+sumValue[i+j][0];
					microInfo[i][j]=microInfo[i][j-1]+microInfo[i+j][0];
					qualities[i][j]->setGain(entropyReduction(sumValue[i][j], microInfo[i][j]));
					qualities[i][j]->setLoss(divergence(j+1, sumValue[i][j], microInfo[i][j]));

				}

			}

	}
}

void DLPAggreg2::computeQualities(bool normalization) {
}

void DLPAggreg2::setValues(const vector<double>& values) {
		this->values = values;
}

