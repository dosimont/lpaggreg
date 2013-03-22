/*
 * Quality.cpp
 *
 *  Created on: 21 mars 2013
 *      Author: dosimont
 */

#include "Quality.h"

Quality::Quality() :
	gain(0), loss(0)
{
}

double Quality::getGain() const {
	return gain;
}

void Quality::setGain(double gain) {
	this->gain = gain;
}

double Quality::getLoss() const {
	return loss;
}

Quality::Quality(double gain, double loss):
	gain(gain), loss(loss){
}

void Quality::setLoss(double loss) {
	this->loss = loss;
}

Quality::~Quality() {
}

void Quality::addToGain(double gain) {
	this->gain+=gain;
}

void Quality::addToLoss(double loss) {
	this->loss+=loss;
}
