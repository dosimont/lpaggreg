/*
 * Compromise.cpp
 *
 *  Created on: 23 févr. 2014
 *      Author: dosimont
 */

#include "Tradeoff.h"

Tradeoff::Tradeoff():value(0), gain(0), loss(0) {
	// TODO Auto-generated constructor stub
	
}

double Tradeoff::getGain() const {
	return gain;
}

void Tradeoff::setGain(double gain) {
	this->gain = gain;
}

double Tradeoff::getLoss() const {
	return loss;
}

void Tradeoff::setLoss(double loss) {
	this->loss = loss;
}

double Tradeoff::getValue() const {
	return value;
}

Tradeoff::Tradeoff(double value, double gain, double loss): value(value), gain(gain), loss(loss) {
}

Tradeoff::Tradeoff(double value, Quality quality): value(value), gain(quality.getGain()), loss(quality.getLoss()) {
}

void Tradeoff::setValue(double value) {
	this->value = value;
}

Tradeoff::~Tradeoff() {
	// TODO Auto-generated destructor stub
}

Tradeoff::Tradeoff(const Tradeoff& C): value(C.getValue()), gain(C.getGain()), loss(C.getLoss()) {
}

Tradeoff::Tradeoff(Tradeoff* C):
	value(C->getValue()),
	gain(C->getGain()),
	loss(C->getLoss()){
}

void Tradeoff::set(Tradeoff C) {
	this->setValue(C.getValue());
	this->setGain(C.getGain());
	this->setLoss(C.getLoss());
}

void Tradeoff::add(Tradeoff C) {
	this->setValue(value+C.getValue());
	this->setGain(gain+C.getGain());
	this->setLoss(loss+C.getLoss());
}

bool Tradeoff::isGreater(Tradeoff C) {
	bool sup=getValue()>C.getValue();
	bool equal=getValue()==C.getValue();
	bool sgain=getGain()>C.getGain();
	bool egain=getGain()==C.getGain();
	bool sloss=getLoss()<C.getLoss();
	return (sup)||(equal&&sgain)||(equal&&egain&&sloss);
}

bool Tradeoff::isEqual(Tradeoff C) {
	bool equal=getValue()==C.getValue();
	bool egain=getGain()==C.getGain();
	bool eloss=getLoss()==C.getLoss();
	return (equal&&egain&&eloss);
}

void Tradeoff::setGreatest(Tradeoff C1, Tradeoff C2) {
	if (C1.isGreater(C2))
		this->set(C1);
	else
		this->set(C2);
}
