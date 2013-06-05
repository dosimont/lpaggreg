/*
 * VLPAggregWrapper.h
 *
 *  Created on: 5 juin 2013
 *      Author: dosimont
 */

#ifndef VLPAGGREGWRAPPER_H_
#define VLPAGGREGWRAPPER_H_

#include "LPAggregWrapper.h"
#include "VectorLPAggreg.h"

class VLPAggregWrapper: public LPAggregWrapper {

	private:

		/*VectorLPAggreg class interfaced with*/
		VectorLPAggreg aggregator;

		/*Algo input values*/
		vector< vector<double> > values;

	public:

		VLPAggregWrapper();
		virtual ~VLPAggregWrapper();

		/*Create a new empty vector in the input matrix, at the end of the matrix*/
		void newVector();

		/*Add a new element to the last positioned vector*/
		void addToVector(double element);

		/*Add a new element to the vector with index "index"*/
		void addToVector(double element, int index);

		/*Algo step 1 : compute qualities*/
		void computeQualities(bool normalization);

		/*Algo step 2 : compute parts for a parameter*/
		void computeParts(float parameter);

		/*Algo step 2 : compute relevant parameter list by using dichotomy*/
		void computeDichotomy(float threshold);

		/*Get the vector number*/
		int getVectorNumber();

		/*Get the vector size*/
		int getVectorSize();
};

#endif /* VLPAGGREGWRAPPER_H_ */
