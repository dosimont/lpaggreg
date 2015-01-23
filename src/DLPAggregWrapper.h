/*******************************************************************************
 *
 * This library is a C++ implementation of several algorithms that enables
 * to aggregate set of data according: an ordered dimension (OLP), a
 * hierarchy (NLP), or both (DLP). OLP and NLP scalar versions (1) have been
 * designed by Robin Lamarche-Perrin. OLP and NLP vector versions (2, 3) and
 * DLP (1, 2) have been designed by Damien Dosimont and are a generalization
 * of Robin Lamarche-Perrin works.
 *
 * Related works:
 * http://magma.imag.fr/content/robin-lamarche-perrin
 * http://moais.imag.fr/membres/damien.dosimont/research.html
 *
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

#ifndef DWRAPPER_H_
#define DWRAPPER_H_


#include "DLPAggreg2.h"
#include "DLPAggreg1.h"

#include "LPValues.h"
#include <map>
#include <vector>

using namespace std;

class DLPAggregWrapper {
	private:

		/*List of relevant parameters get by dichotomy*/
		vector<double> parameters;

		/*List of associated qualities to parameter list*/
		vector<Quality*> qualities;

		int dimension;

		map<int, LPValues<1, double> > values1;
		map<int, LPValues<2, double> > values2;

		map<int, DLPAggreg*> aggreg;
		DLPAggreg * root;

	public:
		
		/*Constructor*/
		DLPAggregWrapper(int dimension);

		/*Destructor*/
		virtual ~DLPAggregWrapper();

		int newLeaf(int parent, int id, int weight);

		int newNode(int parent, int id);

		int newRoot(int id);

		void validate();

		bool hasFullAggregation(int id);

		/*Get the part with in index "index"*/
		int getPart(int id, int index);

		/*Get the part number*/
		int getPartNumber();

		/*Get the parameter with index "index"*/
		float getParameter(int index);

		/*Get the parameter number*/
		int getParameterNumber();

		/*Get the gain by index*/
		double getGainByIndex(int index);

		/*Get the gain by parameter*/
		double getGainByParameter(double parameter);

		/*Get the loss by index*/
		double getLossByIndex(int index);

		/*Get the loss by parameter*/
		double getLossByParameter(double parameter);

		/*Algo step 1 : compute qualities*/
		void computeQualities(bool normalization);

		/*Algo step 2 : compute parts for a parameter*/
		void computeParts(double parameter);

		/*Algo step 2 : compute relevant parameter list by using dichotomy*/
		void computeDichotomy(float threshold);

//1
		void setValue(int id, int i, double value);
		void push_back(int id, double value);

//2
		void addVector(int id);
		void setValue(int id, int i, int j, double value);
		void push_back(int id, int i, double value);

		DLPAggreg*& getRoot();
};

#endif /* DWRAPPER_H_ */
