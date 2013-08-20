/*
 * ScalarNodeLPAggreg.cpp
 *
 *  Created on: 19 août 2013
 *      Author: dosimont
 */

#include "ScalarNodeLPAggreg.h"

ScalarNodeLPAggreg::ScalarNodeLPAggreg(): NodeLPAggreg(), value(0){
	// TODO Auto-generated constructor stub
	
}

ScalarNodeLPAggreg::ScalarNodeLPAggreg(int id, double value=0): NodeLPAggreg(id), value(value){

}

ScalarNodeLPAggreg::ScalarNodeLPAggreg(ScalarNodeLPAggreg* parent, int id=0, double value=0): NodeLPAggreg(parent, id), value(value){
	parent->addChild(this);
}

ScalarNodeLPAggreg::~ScalarNodeLPAggreg() {
	// TODO Auto-generated destructor stub
}

double ScalarNodeLPAggreg::getValue() const {
	return value;
}

void ScalarNodeLPAggreg::setValue(double value) {
	if (!hasChild()){
		this->value = value;
	}
}

void ScalarNodeLPAggreg::computeQuality() {
	if (!hasChild()){
		entSum=entropyReduction(value, 0);
		size=1;
		eval->incrQCounter(2);
	}else{
		value=0;
		entSum=0;
		size=0;
		eval->incrQCounter(3);
		for CHILDS{
			CHILD->computeQuality();
			value+=static_cast<ScalarNodeLPAggreg*>(CHILD)->getValue();
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		quality->setGain(entropyReduction(value, entSum));
		quality->setLoss(divergence(size, value, entSum));
		eval->incrQCounter(2);
	}
}

