/*
 * Compromise.h
 *
 *  Created on: 23 févr. 2014
 *      Author: dosimont
 */

#ifndef COMPROMISE_H_
#define COMPROMISE_H_

#include "Quality.h"

class Compromise {
	private:
		double value;
		double gain;
		double loss;



	public:
		Compromise();
		Compromise(const Compromise &C);
		Compromise(double value, double gain, double loss);
		Compromise(double value, Quality quality);
		virtual ~Compromise();
		double getGain() const;
		void setGain(double gain);
		double getLoss() const;
		void setLoss(double loss);
		double getValue() const;
		void setValue(double value);
		Compromise& operator= (const Compromise &C);
		Compromise& operator+= (const Compromise &C);

};

Compromise operator+ (const Compromise &C1, const Compromise &C2);

#endif /* COMPROMISE_H_ */
