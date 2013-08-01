/*
 * Complexity.cpp
 *
 *  Created on: 2 août 2013
 *      Author: dosimont
 */

#include "Complexity.h"

inline double entropy(double val) {
	return val * log(val) / log(2);
}


double entropyReduction(double val, double ent) {
	if (val > 0)
		return entropy(val) - ent;
	else
		return 0;
}

double divergence(int size, double value, double ent) {
	return value * log(size) / log(2)  - entropyReduction(value, ent);
}


