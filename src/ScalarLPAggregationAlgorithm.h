/*
 * ScalarLPAggregationAlgorithm.h
 *
 *  Created on: 26 févr. 2013
 *      Author: dosimont
 */

#ifndef SCALARLPAGGREGATIONALGORITHM_H_
#define SCALARLPAGGREGATIONALGORITHM_H_

#include <vector>
#include "LPAggregationAlgorithm.h"
#include <iostream>

using namespace std;

class ScalarLPAggregationAlgorithm: public LPAggregationAlgorithm {
	private:
		vector<float> values;

	public:
		ScalarLPAggregationAlgorithm(vector<float> values, float parameter,
				bool normalization);
		virtual ~ScalarLPAggregationAlgorithm();
		void computeQualities();
		
};

#endif /* SCALARLPAGGREGATIONALGORITHM_H_ */
