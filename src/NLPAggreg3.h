/*
 * NLPAggreg3.h
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#ifndef NLPAGGREG3_H_
#define NLPAGGREG3_H_

#include "NLPAggreg.h"

class NLPAggreg3: public NLPAggreg {
	private:

		vector< vector<double> > values;

	private:
		void computeQuality();
		void computeQuality_Matrix(int i, int j);

	public:
		NLPAggreg3();
		virtual ~NLPAggreg3();
		NLPAggreg3(int id, vector< vector<double> > values);
		NLPAggreg3(NLPAggreg3* parent, int id, vector< vector<double> > values);
		void computeQualities(bool normalization);
		const vector<vector<double> >& getValues() const;
		void setValues(const vector<vector<double> >& values);
};

#endif /* NLPAGGREG3_H_ */
