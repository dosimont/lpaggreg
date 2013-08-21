/*
 * Complexity.cpp
 *
 *  Created on: 2 août 2013
 *      Author: dosimont
 */

#include "Complexity.h"

template <typename T> T entropy(T val) {
	return val * log(val) / log(2);
}


template <typename T> T entropyReduction(T val, T ent) {
	if (val > 0)
		return entropy(val) - ent;
	else
		return 0;
}

template <typename T> T divergence(int size, T value, T ent) {
	return value * log(size) / log(2)  - entropyReduction(value, ent);
}


