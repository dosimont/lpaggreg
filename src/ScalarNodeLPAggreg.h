/*
 * ScalarNodeLPAggreg.h
 *
 *  Created on: 19 août 2013
 *      Author: dosimont
 */

#ifndef SCALARNODELPAGGREG_H_
#define SCALARNODELPAGGREG_H_

#include "NodeLPAggreg.h"

class ScalarNodeLPAggreg: public NodeLPAggreg {
	private:
		double value;
	public:
		ScalarNodeLPAggreg();
		ScalarNodeLPAggreg(int id, double value);
		ScalarNodeLPAggreg(ScalarNodeLPAggreg* parent, int id, double value);
		double getValue() const;
		void setValue(double value);
		void computeQuality();
		virtual ~ScalarNodeLPAggreg();
};

#endif /* SCALARNODELPAGGREG_H_ */
