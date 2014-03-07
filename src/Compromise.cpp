/*
 * Compromise.cpp
 *
 *  Created on: 23 févr. 2014
 *      Author: dosimont
 */

#include "Compromise.h"

Compromise::Compromise():value(0), gain(0), loss(0) {
	// TODO Auto-generated constructor stub
	
}

double Compromise::getGain() const {
	return gain;
}

void Compromise::setGain(double gain) {
	this->gain = gain;
}

double Compromise::getLoss() const {
	return loss;
}

void Compromise::setLoss(double loss) {
	this->loss = loss;
}

double Compromise::getValue() const {
	return value;
}

Compromise::Compromise(double value, double gain, double loss): value(value), gain(gain), loss(loss) {
}

Compromise::Compromise(double value, Quality quality): value(value), gain(quality.getGain()), loss(quality.getLoss()) {
}

void Compromise::setValue(double value) {
	this->value = value;
}

Compromise::~Compromise() {
	// TODO Auto-generated destructor stub
}

Compromise::Compromise(const Compromise& C): value(C.getValue()), gain(C.getGain()), loss(C.getLoss()) {
}

Compromise::Compromise(Compromise* C):
	value(C->getValue()),
	gain(C->getGain()),
	loss(C->getLoss()){
}

void Compromise::set(Compromise C) {
	this->setValue(C.getValue());
	this->setGain(C.getGain());
	this->setLoss(C.getLoss());
}

void Compromise::add(Compromise C) {
	this->setValue(value+C.getValue());
	this->setGain(gain+C.getGain());
	this->setLoss(loss+C.getLoss());
}

bool Compromise::isGreater(Compromise C) {
	bool sup=getValue()>C.getValue();
	bool equal=getValue()==C.getValue();
	bool sgain=getGain()>C.getGain();
	bool egain=getGain()==C.getGain();
	bool sloss=getLoss()>C.getLoss();
	return (sup)||(equal&&sgain)||(equal&&egain&&sloss);
}

bool Compromise::isEqual(Compromise C) {
	bool equal=getValue()==C.getValue();
	bool egain=getGain()==C.getGain();
	bool eloss=getLoss()==C.getLoss();
	return (equal&&egain&&eloss);
}

void Compromise::setGreatest(Compromise C1, Compromise C2) {
	if (C1.isGreater(C2))
		this->set(C1);
	else
		this->set(C2);
}
