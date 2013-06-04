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

/*ScalarLPAggreg header file
 *
 * Class that enables to perform LP aggregation on scalars. Inherits from
 * virtual LPAggreg class.
 */

#ifndef SCALARLPAGGREG_H_
#define SCALARLPAGGREG_H_

#include <vector>
#include "LPAggreg.h"
#include <iostream>

using namespace std;

class ScalarLPAggreg: public LPAggreg {
	private:

		/*Values used as input*/
		vector<double> values;

	protected:

		/*Override LPAggreg virtual method. Perform quality computation.
		 * bool normalization : if true, normalize quality measures*/
		void computeQualities(bool normalization);

	public:

		/*Constructor with values*/
		ScalarLPAggreg(vector<double> values);

		/*Constructor*/
		ScalarLPAggreg();

		/*Set input values*/
		void setValues(const vector<double>& values);
};

#endif /* SCALARLPAGGREG_H_ */
