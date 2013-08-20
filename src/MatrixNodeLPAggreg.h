/*
 * MatrixNodeLPAggreg.h
 *
 *  Created on: 20 août 2013
 *      Author: dosimont
 */

#ifndef MATRIXNODELPAGGREG_H_
#define MATRIXNODELPAGGREG_H_

#include "NodeLPAggreg.h"

class MatrixNodeLPAggreg: public NodeLPAggreg {
	private:
		vector<vector<double>> value;
	public:
		MatrixNodeLPAggreg();
		MatrixNodeLPAggreg(int id, vector<vector<double>> value);
		MatrixNodeLPAggreg(MatrixNodeLPAggreg* parent, int id, vector<vector<double>> value);
		void computeQuality();
		void computeQuality(int i, int j);
		virtual ~MatrixNodeLPAggreg();
		const vector<vector<double> >& getValue() const;
		void setValue(vector<vector<double>> value);
};

#endif /* MATRIXNODELPAGGREG_H_ */
