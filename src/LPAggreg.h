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

#ifndef LPAGGREG_H_
#define LPAGGREG_H_

#include <iostream>
#include <vector>
#include <math.h>
#include "Quality.h"

using namespace std;

class LPAggreg { //ABC
	private:
		//float parameter;
		int size;
	protected:
		vector< vector<Quality*> > qualities;
		//int ** bestCuts;
		int * bestCuts;
		vector<int> bestPartitions;
		vector<float> parametersD;
		vector<Quality*> qualitiesD;

	protected:
		virtual void computeQualities(bool normalization)=0;
		void deleteQualities();
		inline double entropy(double value);
		double entropyReduction(double value, double ent);
		int sizeReduction(int size);
		double divergence(int size, double value, double ent);
		void computeBestCuts(float parameter);
		void deleteBestCuts();
		void computeBestPartitions();
		void deleteBestPartitions();
		int fillPartition(int i, int p);
		void setSize(int size);
		void computeBestQualities(float threshold);
		void computeBestQuality(Quality *bestQuality);
		void fillQuality(int i, Quality *bestQuality);
		void addBestQualities(float parameter1, float parameter2, Quality *bestQuality1, Quality *bestQuality2, float threshold);
		void deleteQualitiesD();
		void deleteParameters();
	public:
		LPAggreg();
		virtual ~LPAggreg();
		int getSize() const;
		void init(bool normalization);
		vector<int> process(float parameter);
		vector<float> dichotomy(float threshold);
		const vector<Quality*>& getQualitiesD() const {
			return qualitiesD;
		}
};

#endif /* LPAGGREG_H_ */
