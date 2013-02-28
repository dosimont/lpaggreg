/*
 * VectorLPAggregationAlgorithm.h
 *
 *  Created on: 27 févr. 2013
 *      Author: dosimont
 */

#ifndef VECTORLPAGGREGATIONALGORITHM_H_
#define VECTORLPAGGREGATIONALGORITHM_H_

#include <vector>
#include "LPAggregationAlgorithm.h"
#include <iostream>

class VectorLPAggregationAlgorithm: public LPAggregationAlgorithm{
	private:
		vector< vector<float> > values;
	public:
		VectorLPAggregationAlgorithm(vector< vector<float> > values, float parameter,
				bool normalization);
		virtual ~VectorLPAggregationAlgorithm();
		void computeQualities();
};

#endif /* VECTORLPAGGREGATIONALGORITHM_H_ */
