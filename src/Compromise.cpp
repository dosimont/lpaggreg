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

Compromise& Compromise::operator =(const Compromise& C) {
	this->setValue(C.getValue());
	this->setGain(C.getGain());
	this->setLoss(C.getLoss());
	return *this;
}

Compromise& Compromise::operator +=(const Compromise& C) {
	this->setValue(value+C.getValue());
	this->setGain(gain+C.getGain());
	this->setLoss(loss+C.getLoss());
	return *this;
}

Compromise operator +(const Compromise& C1, const Compromise &C2) {
	Compromise copie(C1);
	copie+=C2;
	return copie;
}
