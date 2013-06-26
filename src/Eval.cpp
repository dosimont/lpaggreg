/*
 * Timer.cpp
 *
 *  Created on: 20 juin 2013
 *      Author: dosimont
 */

#include "Eval.h"

Eval::Eval(): counterQ(0), counterBC(0), counterBP(0) {
}

void Eval::startQTimer() {
	gettimeofday(&timeQ1,NULL);
}

void Eval::stopQTimer() {
	gettimeofday(&timeQ2, NULL);
}

void Eval::startBCTimer() {
	gettimeofday(&timeBC1,NULL);
}

void Eval::stopBCTimer() {
	gettimeofday(&timeBC2,NULL);
}

void Eval::startBPTimer() {
	gettimeofday(&timeBP1,NULL);
}

void Eval::stopBPTimer() {
	gettimeofday(&timeBP2,NULL);
}

int Eval::getQDuration() {
	return ((timeQ2.tv_sec-timeQ1.tv_sec)*1000)+((timeQ2.tv_usec-timeQ1.tv_usec)/1000);
}

int Eval::getBCDuration() {
	return ((timeBC2.tv_sec-timeBC1.tv_sec)*1000)+((timeBC2.tv_usec-timeBC1.tv_usec)/1000);
}

int Eval::getBPDuration() {
	return ((timeBP2.tv_sec-timeBP1.tv_sec)*1000)+((timeBP2.tv_usec-timeBP1.tv_usec)/1000);
}

void Eval::resetQCounter() {
	counterQ=0;
}

void Eval::resetBCCounter() {
	counterBC=0;
}

void Eval::resetBPCounter() {
	counterBP=0;
}

void Eval::resetCounters() {
	resetQCounter();
	resetBCCounter();
	resetBPCounter();
}

void Eval::incrQCounter(int i) {
	counterQ+=i;
}

void Eval::incrBCCounter(int i) {
	counterBC+=i;
}

void Eval::incrBPCounter(int i) {
	counterBP+=i;
}

int Eval::getQCount() {
	return counterQ;
}

int Eval::getBCCount() {
	return counterBC;
}

int Eval::getBPCount() {
	return counterBP;
}

Eval::~Eval() {
}

