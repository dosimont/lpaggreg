/*
 * OLPAggreg3.h
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#ifndef OLPAGGREG3_H_
#define OLPAGGREG3_H_

#include "OLPAggreg.h"

class OLPAggreg3 : public OLPAggreg{

	private:
		vector<vector <vector<double> > >values;

	private:
		void computeQualitiesSpe(bool normalization);

	public:
		OLPAggreg3();
		OLPAggreg3(vector<vector <vector<double> > >values);
		virtual ~OLPAggreg3();
		void setValues(const vector<vector<vector<double> > >& values);
		unsigned int getSize();
};

#endif /* OLPAGGREG3_H_ */
