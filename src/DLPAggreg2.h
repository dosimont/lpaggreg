/*
 * DLPaggreg2.h
 *
 *  Created on: 22 janv. 2014
 *      Author: dosimont
 */

#ifndef DLPAGGREG2_H_
#define DLPAGGREG2_H_

#include "DLPAggreg.h"

#define DCHILD2 static_cast<DLPAggreg2*>(DCHILD)

class DLPAggreg2: public DLPAggreg {
	private:
		vector<vector<double> > values;
		double*** sumValue;
		double*** microInfo;
		int valueISize;

	private:
		void computeQualities();

	public:
	public:
		DLPAggreg2();
		virtual ~DLPAggreg2();
		DLPAggreg2(int id);
		DLPAggreg2(int id, const vector<vector<double> >& values);
		DLPAggreg2(DLPAggreg2* parent, int id, const vector<vector<double> >& values);
		void computeQualities(bool normalization);
		const vector<vector <double> >& getValues() const;
		void setValues(const vector<vector<double> >&);
		double*** getMicroInfo() const;
		double*** getSumValue() const;
		int getValueISize() const;
};

#endif /* DLPAGGREG2_H_ */
