/*******************************************************************************
 *
 * This library is a C++ implementation of an algorithm designed by Robin
 * Lamarche-Perrin. This algorithm enables to aggregate sets of scalar or vector
 * data, according aggregation gain & information loss ratio parameter.
 * More information in "Robin Lamarche-Perrin, Yves Demazeau and Jean-Marc
 * Vincent. The Best-partitions Problem: How to Build Meaningful Agregations?
 * Research report RR-LIG-XXX, Laboratoire d’Informatique de Grenoble, France,
 * Feb. 2013. (forthcoming)"
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

/*Author : Damien Dosimont <damien.dosimont@imag.fr>*/

/*LPAggregWrapper header file
 *
 * Class that enables to interface with VectorLPAggreg class.
 * Is an entry point to LPAggregation algorithm
 */

#ifndef WRAPPER_H_
#define WRAPPER_H_


#include "Quality.h"
#include <vector>

using namespace std;

class LPAggregWrapper {
	protected:

		/*Aggregated parts generated by the algo*/
		vector<int> parts;

		/*List of relevant parameters get by dichotomy*/
		vector<float> parameters;

		/*List of associated qualities to parameter list*/
		vector<Quality*> qualities;



	public:

		/*Constructor*/
		LPAggregWrapper();

		/*Destructor*/
		virtual ~LPAggregWrapper();

		/*Algo step 1 : compute qualities*/
		virtual void computeQualities(bool normalization)=0;

		/*Algo step 2 : compute parts for a parameter*/
		virtual void computeParts(float parameter)=0;

		/*Algo step 2 : compute relevant parameter list by using dichotomy*/
		virtual void computeDichotomy(float threshold)=0;

		/*Get the part with in index "index"*/
		int getPart(int index);

		/*Get the part number*/
		int getPartNumber();

		/*Get the parameter with index "index"*/
		float getParameter(int index);

		/*Get the parameter number*/
		int getParameterNumber();

		/*Get the gain by index*/
		double getGainByIndex(int index);

		/*Get the gain by parameter*/
		double getGainByParameter(float parameter);

		/*Get the loss by index*/
		double getLossByIndex(int index);

		/*Get the loss by parameter*/
		double getLossByParameter(float parameter);

};

#endif /* WRAPPER_H_ */
