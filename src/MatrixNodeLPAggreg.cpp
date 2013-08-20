/*
 * MatrixNodeLPAggreg.cpp
 *
 *  Created on: 20 août 2013
 *      Author: dosimont
 */

#include "MatrixNodeLPAggreg.h"

MatrixNodeLPAggreg::MatrixNodeLPAggreg(): NodeLPAggreg(), value(0){
	// TODO Auto-generated constructor stub
	
}

MatrixNodeLPAggreg::MatrixNodeLPAggreg(int id, vector<vector<double>> value): NodeLPAggreg(id), value(value){

}

MatrixNodeLPAggreg::MatrixNodeLPAggreg(MatrixNodeLPAggreg* parent, int id, vector<vector<double>> value): NodeLPAggreg(parent, id), value(value){
	parent->addChild(this);
}

const vector<vector<double> >& MatrixNodeLPAggreg::getValue() const {
	return value;
}

MatrixNodeLPAggreg::~MatrixNodeLPAggreg() {
	// TODO Auto-generated destructor stub
}

void MatrixNodeLPAggreg::setValue(vector<vector<double>> value) {
	if (!hasChild()){
		this->value = value;
	}
}
//TODO vectoriser
void MatrixNodeLPAggreg::computeQuality(int i, int j) {
	if (!hasChild()){
		entSum=entropyReduction(value[i][j], 0);
		size=1;
		eval->incrQCounter(2);
	}else{
		value[i][j]=0;
		entSum=0;
		size=0;
		eval->incrQCounter(3);
		for CHILDS{
			static_cast<MatrixNodeLPAggreg*>(CHILD)->computeQuality(i,j);
			value[i]+=static_cast<MatrixNodeLPAggreg*>(CHILD)->getValue()[i][j];
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		if (i==0&&j==0){
			quality->setGain(0);
			quality->setLoss(0);
		}
		quality->addToGain(entropyReduction(value[i][j], entSum));
		quality->addToLoss(divergence(size, value[i][j], entSum));
		eval->incrQCounter(2);
	}
}

void MatrixNodeLPAggreg::computeQuality() {
	for (int i=0; i<value.size(); i++)
		for (int j=0; j<value.size(); j++)
			computeQuality(i,j);
}

