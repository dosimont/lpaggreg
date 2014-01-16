/*
 * DLPAggreg2.h
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#ifndef DLPAGGREG2_H_
#define DLPAGGREG2_H_

#include "DLPAggreg.h"

class DLPAggreg2: public DLPAggreg {
	private:
		vector<double> values;
		double** sumValue;
		double** microInfo;
		vector<vector<Quality*>> qualities;

	private:
		void computeQuality();

	public:
		DLPAggreg2();
		virtual ~DLPAggreg2();
		DLPAggreg2(int id, vector<double> values);
		DLPAggreg2(DLPAggreg2* parent, int id, vector<double> values);
		void computeQualities(bool normalization);
		const vector<double>& getValues() const;
		void setValues(const vector<double>& values);
};

#endif /* DLPAGGREG2_H_ */
