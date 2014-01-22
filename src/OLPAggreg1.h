/*
 * OLPAggreg1.h
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#ifndef OLPAGGREG1_H_
#define OLPAGGREG1_H_

#include "OLPAggreg.h"

using namespace std;

class OLPAggreg1: public OLPAggreg {
	private:
		vector<double> values;

	private:
		void computeQualitiesSpe(bool normalization);

	public:
		OLPAggreg1();
		OLPAggreg1(const vector<double>& values);
		virtual ~OLPAggreg1();
		void setValues(const vector<double>& values);
		unsigned int getSize();
		void computeQualities(bool normalization);
};

#endif /* OLPAGGREG1_H_ */
