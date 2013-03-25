/*******************************************************************************
 *
 * This library is a C++ implementation of an algorithm designed by Robin
 * Lamarche-Perrin. This algorithm allows to aggregate sets of scalar or vector
 * data, according aggregation gain & information loss ratio parameter.
 * More information in "R. Lamarche-Perrin & al. - The Best-partitions Problem:
 * How to Build Meaningful Aggregations? in ..."
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
