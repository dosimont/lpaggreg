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

#ifndef VECTORWRAPPER_H_
#define VECTORWRAPPER_H_

#include "VectorLPAggreg.h"
#include <vector>

class LPAggregWrapper {
	private:
		VectorLPAggreg aggregator;
		vector< vector<double> > values;
		vector<int> parts;
		vector<float> parameters;



	public:
		LPAggregWrapper();
		virtual ~LPAggregWrapper();
		void newVector();
		void addToVector(double element);
		void addToVector(double element, int index);
		void computeQualities(bool normalization);
		void computeParts(float parameter);
		void computeDichotomy(float threshold);
		int getPart(int index);
		int getPartsNumber();
		int getVectorsNumber();
		int getVectorSize();
		float getParameter(int index);
		int getParametersNumber();

};

#endif /* VECTORWRAPPER_H_ */
