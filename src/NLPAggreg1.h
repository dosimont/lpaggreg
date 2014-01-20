/*
 * NLPAggreg1.h
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#ifndef NLPAGGREG1_H_
#define NLPAGGREG1_H_

#include "NLPAggreg.h"

class NLPAggreg1: public NLPAggreg {
	private:
		
		double values;

	private:
		void computeQuality();

	public:
		NLPAggreg1();
		virtual ~NLPAggreg1();
		NLPAggreg1(int id, double values);
		NLPAggreg1(NLPAggreg1* parent, int id, double values);
		void computeQualities(bool normalization);
		double getValues() const;
		void setValues(double values);
};

#endif /* NLPAGGREG1_H_ */
