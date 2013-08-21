/*
 * Complexity.h
 *
 *  Created on: 2 août 2013
 *      Author: dosimont
 */

#ifndef COMPLEXITY_H_
#define COMPLEXITY_H_

#include <math.h>

template <typename T> T entropy(T val);
template <typename T> T entropyReduction(T val, T ent);
template <typename T> T divergence(int size, T value, T ent);

#endif /* COMPLEXITY_H_ */
