/*
 * Compromise.h
 *
 *  Created on: 23 févr. 2014
 *      Author: dosimont
 */

#ifndef COMPROMISE_H_
#define COMPROMISE_H_

#include "Quality.h"

class Tradeoff {
	private:
		double value;
		double gain;
		double loss;



	public:
        Tradeoff();
        Tradeoff(const Tradeoff &C);
        Tradeoff(Tradeoff *C);
        Tradeoff(double value, double gain, double loss);
        Tradeoff(double value, Quality quality);
        virtual ~Tradeoff();
		double getGain() const;
		void setGain(double gain);
		double getLoss() const;
		void setLoss(double loss);
		double getValue() const;
		void setValue(double value);
        void set(Tradeoff C);
        void add(Tradeoff C);
        bool isGreater(Tradeoff C);
        bool isEqual(Tradeoff C);
        void setGreatest(Tradeoff C1, Tradeoff C2);

};

#endif /* COMPROMISE_H_ */
