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

#endif /* COMPLEXITY_H_ */
