/*
 * LPAggregationAlgorithm.h
 *
 *  Created on: 26 févr. 2013
 *      Author: dosimont
 */

#ifndef LPAGGREGATIONALGORITHM_H_
#define LPAGGREGATIONALGORITHM_H_

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class LPAggregationAlgorithm {
	private:
		float parameter;
		bool normalization;
		int size;
	protected:
		float ** loss;
		float ** gain;
		float ** bestCuts;
		vector<float> bestPartitions;

	public:
		LPAggregationAlgorithm(float parameter, bool normalization);
		LPAggregationAlgorithm();
		virtual ~LPAggregationAlgorithm();
		float getParameter();
		void setParameter(float gainLossRatio);
		virtual void computeQualities();
		inline float entropy(float value);
		float entropyReduction(float value, float ent);
		float divergence(int size, float value, float ent);
		bool isNormalization() const;
		void setNormalization(bool normalization);
		int getSize() const;
		void setSize(int size);
		void computeBestCuts();
		void computeBestPartitions();
		vector<float> process();
		int fillPartition(int i, int j, int p);
};

#endif /* LPAGGREGATIONALGORITHM_H_ */
