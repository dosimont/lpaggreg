/*
 * Timer.cpp
 *
 *  Created on: 20 juin 2013
 *      Author: dosimont
 */

#include "Timer.h"

Timer::Timer(): timeQ1(0), timeQ2(0), timeBC1(0), timeBC2(0), timeBP1(0), timeBP2(0) {
}

void Timer::startQualityTimer() {
	timeQ1=time(NULL);
}

void Timer::stopQualityTimer() {
	timeQ2=time(NULL);
}

void Timer::startBestCutTimer() {
	timeBC1=time(NULL);
}

void Timer::stopBestCutTimer() {
	timeBC2=time(NULL);
}

void Timer::startBestPartitionTimer() {
	timeBP1=time(NULL);
}

void Timer::stopBestPartitionTimer() {
	timeBP2=time(NULL);
}

time_t Timer::getQualityDuration() {
	return timeQ2-timeQ1;
}

time_t Timer::getBestCutDuration() {
	return timeBC2-timeBC1;
}

time_t Timer::getBestPartitionDuration() {
	return timeBP2-timeBP1;
}

Timer::~Timer() {
}

