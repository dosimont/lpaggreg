/*
 * DLPAggreg2.h
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#ifndef DLPAGGREG2_H_
#define DLPAGGREG2_H_

#include "DLPAggreg.h"
#define DCHILD1 static_cast<DLPAggreg1*>(DCHILD)

class DLPAggreg1: public DLPAggreg {
	private:
		vector<double> values;
		double** sumValue;
		double** microInfo;

	private:
		void computeQualities();

	public:
		DLPAggreg1();
		virtual ~DLPAggreg1();
		DLPAggreg1(int id);
		DLPAggreg1(int id, const vector<double>& values);
		DLPAggreg1(DLPAggreg1* parent, int id, const vector<double>& values);
		void computeQualities(bool normalization);
		const vector<double>& getValues() const;
		void setValues(const vector<double>& values);
		double** getMicroInfo() const;
		double** getSumValue() const;
};

#endif /* DLPAGGREG2_H_ */
