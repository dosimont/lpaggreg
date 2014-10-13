/*******************************************************************************
 *
 * This library is a C++ implementation of several algorithms that enables
 * to aggregate set of data according: an ordered dimension (OLP), a
 * hierarchy (NLP), or both (DLP). OLP and NLP scalar versions (1) have been
 * designed by Robin Lamarche-Perrin. OLP and NLP vector versions (2, 3) and
 * DLP (1, 2) have been designed by Damien Dosimont and are a generalization
 * of Robin Lamarche-Perrin works.
 *
 * Related works:
 * http://magma.imag.fr/content/robin-lamarche-perrin
 * http://moais.imag.fr/membres/damien.dosimont/research.html
 *
 *
 * (C) Copyright (February 28th 2013) Damien Dosimont. All rights reserved.
 *
 * Damien Dosimont <damien.dosimont@imag.fr>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 *******************************************************************************/

#include "Eval.h"

Eval::Eval() :
		counterQ(0), counterBC(0), counterBP(0) {
}

void Eval::startQTimer() {
#ifdef LINUX
	gettimeofday(&timeQ1, NULL);
#endif
}

void Eval::stopQTimer() {
#ifdef LINUX
	gettimeofday(&timeQ2, NULL);
#endif
}

void Eval::startBCTimer() {
#ifdef LINUX
	gettimeofday(&timeBC1, NULL);
#endif
}

void Eval::stopBCTimer() {
#ifdef LINUX
	gettimeofday(&timeBC2, NULL);
#endif
}

void Eval::startBPTimer() {
#ifdef LINUX
	gettimeofday(&timeBP1, NULL);
#endif
}

void Eval::stopBPTimer() {
#ifdef LINUX
	gettimeofday(&timeBP2, NULL);
#endif
}

double Eval::getQDuration() {
#ifdef LINUX
	return ((double) (timeQ2.tv_sec - timeQ1.tv_sec) * 1000.0)
			+ ((double) (timeQ2.tv_usec - timeQ1.tv_usec) / 1000.0);
#endif
	return 0;
}

double Eval::getBCDuration() {
#ifdef LINUX
	return ((double) (timeBC2.tv_sec - timeBC1.tv_sec) * 1000.0)
			+ ((double) (timeBC2.tv_usec - timeBC1.tv_usec) / 1000.0);
#endif
	return 0;
}

double Eval::getBPDuration() {
#ifdef LINUX
	return ((double) (timeBP2.tv_sec - timeBP1.tv_sec) * 1000.0)
			+ ((double) (timeBP2.tv_usec - timeBP1.tv_usec) / 1000.0);
#endif
	return 0;
}

void Eval::resetQCounter() {
	counterQ = 0;
}

void Eval::resetBCCounter() {
	counterBC = 0;
}

void Eval::resetBPCounter() {
	counterBP = 0;
}

void Eval::resetCounters() {
	resetQCounter();
	resetBCCounter();
	resetBPCounter();
}

void Eval::incrQCounter(int i) {
	counterQ += i;
}

void Eval::incrBCCounter(int i) {
	counterBC += i;
}

void Eval::incrBPCounter(int i) {
	counterBP += i;
}

long Eval::getQCount() {
	return counterQ;
}

long Eval::getBCCount() {
	return counterBC;
}

long Eval::getBPCount() {
	return counterBP;
}

Eval::~Eval() {
}

