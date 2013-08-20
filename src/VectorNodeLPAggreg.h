/*
 * VectorNodeLPAggreg.h
 *
 *  Created on: 19 août 2013
 *      Author: dosimont
 */

#ifndef VECTORNODELPAGGREG_H_
#define VECTORNODELPAGGREG_H_

#include "NodeLPAggreg.h"

class VectorNodeLPAggreg: public NodeLPAggreg {
	private:
		vector<double> value;
	public:
		VectorNodeLPAggreg();
		VectorNodeLPAggreg(int id, vector<double> value);
		VectorNodeLPAggreg(VectorNodeLPAggreg* parent, int id, vector<double> value);
		void computeQuality();
		void computeQuality(int index);
		virtual ~VectorNodeLPAggreg();
		const vector<double>& getValue() const;
		void setValue(vector<double> value);
};

#endif /* VECTORNODELPAGGREG_H_ */
