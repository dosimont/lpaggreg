/*
 * VectorNodeLPAggreg.cpp
 *
 *  Created on: 19 août 2013
 *      Author: dosimont
 */

#include "VectorNodeLPAggreg.h"

/*
 * VectorNodeLPAggreg.cpp
 *
 *  Created on: 19 août 2013
 *      Author: dosimont
 */

#include "VectorNodeLPAggreg.h"

VectorNodeLPAggreg::VectorNodeLPAggreg(): NodeLPAggreg(), value(0){
	// TODO Auto-generated constructor stub
	
}

VectorNodeLPAggreg::VectorNodeLPAggreg(int id, vector<double> value): NodeLPAggreg(id), value(value){

}

VectorNodeLPAggreg::VectorNodeLPAggreg(VectorNodeLPAggreg* parent, int id, vector<double> value): NodeLPAggreg(parent, id), value(value){
	parent->addChild(this);
}

const vector<double>& VectorNodeLPAggreg::getValue() const {
	return value;
}


VectorNodeLPAggreg::~VectorNodeLPAggreg() {
	// TODO Auto-generated destructor stub
}

void VectorNodeLPAggreg::setValue(vector<double> value) {
	if (!hasChild()){
		this->value = value;
	}
}
//TODO vectoriser
void VectorNodeLPAggreg::computeQuality() {
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
			value+=static_cast<VectorNodeLPAggreg*>(CHILD)->getValue();
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		quality->setGain(entropyReduction(value, entSum));
		quality->setLoss(divergence(size, value, entSum));
		eval->incrQCounter(2);
	}
}



