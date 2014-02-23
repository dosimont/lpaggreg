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
		Compromise(Compromise *C);
		Compromise(double value, double gain, double loss);
		Compromise(double value, Quality quality);
		virtual ~Compromise();
		double getGain() const;
		void setGain(double gain);
		double getLoss() const;
		void setLoss(double loss);
		double getValue() const;
		void setValue(double value);
		void set(Compromise C);
		Compromise& operator= (const Compromise &C);
		Compromise& operator+= (const Compromise &C);
		Compromise& operator+= (Compromise *C);

};

Compromise operator+ (Compromise C1, Compromise C2);
bool operator> (Compromise C1, Compromise C2);
bool operator== (Compromise C1, Compromise C2);

Compromise * max(Compromise *C1, Compromise *C2);

#endif /* COMPROMISE_H_ */
