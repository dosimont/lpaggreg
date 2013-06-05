/*
 * VLPAggregWrapper.h
 *
 *  Created on: 5 juin 2013
 *      Author: dosimont
 */

#ifndef VLPAGGREGWRAPPER_H_
#define VLPAGGREGWRAPPER_H_

#include "LPAggregWrapper.h"
#include "MatrixLPAggreg.h"

class MLPAggregWrapper: public LPAggregWrapper {

	private:

		/*VectorLPAggreg class interfaced with*/
		MatrixLPAggreg aggregator;

		/*Algo input values*/
		vector< vector< vector <double> > > values;

	public:

		MLPAggregWrapper();
		virtual ~MLPAggregWrapper();

		void newMatrix();

		/*Add a new element to the last positioned in the matrix i*/
		void addToMatrix(double element, int i);

		/*Add a new element to the vector with index j in the matrix i*/
		void addToMatrix(double element, int i, int j);

		/*Create a new empty vector in the input cubic matrix, at the end of the last positioned matrix*/
		void newVector();

		/*Add a new element to the last positioned vector in the current matrix*/
		void addToVector(double element);

		/*Add a new element to the vector with index "index" in the last positioned matrix*/
		void addToVector(double element, int index);

		/*Algo step 1 : compute qualities*/
		void computeQualities(bool normalization);

		/*Algo step 2 : compute parts for a parameter*/
		void computeParts(float parameter);

		/*Algo step 2 : compute relevant parameter list by using dichotomy*/
		void computeDichotomy(float threshold);

		/*Get the matrix number*/
		int getMatrixNumber();

		/*Get the matrix size*/
		int getMatrixSize();

		/*Get the vector size*/
		int getVectorSize();
};

#endif /* VLPAGGREGWRAPPER_H_ */
