/*
 * Complexity.cpp
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */


#include "Complexity.h"

double entropy(double val) {
	return val * log(val) / ln;
}

double entropyReduction(double val, double ent) {
	if (val > 0)
		return entropy(val) - ent;
	else
		return 0;
}

double divergence(int size, double value, double ent) {
	return value * log(size) / ln - entropyReduction(value, ent);
}


