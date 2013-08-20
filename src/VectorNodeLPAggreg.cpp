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
void VectorNodeLPAggreg::computeQuality(int index) {
	if (!hasChild()){
		entSum=entropyReduction(value[index], 0);
		size=1;
		eval->incrQCounter(2);
	}else{
		value[index]=0;
		entSum=0;
		size=0;
		eval->incrQCounter(3);
		for CHILDS{
			static_cast<VectorNodeLPAggreg*>(CHILD)->computeQuality(index);
			value[index]+=static_cast<VectorNodeLPAggreg*>(CHILD)->getValue()[index];
			entSum+=CHILD->getEntSum();
			size+=CHILD->getSize();
			eval->incrQCounter(3);
		}
		if (index==0){
			quality->setGain(0);
			quality->setLoss(0);
		}
		quality->addToGain(entropyReduction(value[index], entSum));
		quality->addToLoss(divergence(size, value[index], entSum));
		eval->incrQCounter(2);
	}
}

void VectorNodeLPAggreg::computeQuality() {
	for (int i=0; i<value.size(); i++)
		computeQuality(i);
}



