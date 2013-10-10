/*
 * Complexity.h
 *
 *  Created on: 2 août 2013
 *      Author: dosimont
 */

#ifndef COMPLEXITY_H_
#define COMPLEXITY_H_

#include <math.h>

double entropy(double val);
double entropyReduction(double val, double ent);
double divergence(int size, double value, double ent);

static const double ln = log(2);

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

#endif /* COMPLEXITY_H_ */
