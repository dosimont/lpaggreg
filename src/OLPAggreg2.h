/*
 * OLPAggreg2.h
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#ifndef OLPAGGREG2_H_
#define OLPAGGREG2_H_

#include "OLPAggreg.h"

class OLPAggreg2: public OLPAggreg {
		
	private:
		vector<vector<double> > values;

	private:
		void computeQualitiesSpe(bool normalization);

	public:
		OLPAggreg2();
		OLPAggreg2(vector<vector<double> > values);
		virtual ~OLPAggreg2();
		void setValues(const vector<vector<double> >& values);
		unsigned int getSize();
		void computeQualities(bool normalization);
};

#endif /* OLPAGGREG2_H_ */
