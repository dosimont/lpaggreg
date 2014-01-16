/*
 * NLPAggreg2.h
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#ifndef NLPAGGREG2_H_
#define NLPAGGREG2_H_

#include "NLPAggreg.h"

class NLPAggreg2: public NLPAggreg {
	private:

		vector<double> values;

	private:
		void computeQuality();
		void computeQuality_Vector(int index);

	public:
		NLPAggreg2();
		virtual ~NLPAggreg2();
		NLPAggreg2(int id, vector<double> values);
		NLPAggreg2(NLPAggreg2* parent, int id, vector<double> values);
		void computeQualities(bool normalization);
		const vector<double>& getValues() const;
		void setValues(const vector<double>& values);
};

#endif /* NLPAGGREG2_H_ */
