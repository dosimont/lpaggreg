/*
 * Quality.h
 *
 *  Created on: 21 mars 2013
 *      Author: dosimont
 */

#ifndef QUALITY_H_
#define QUALITY_H_

class Quality {
	private:
		double gain;
		double loss;
	public:
		Quality();
		Quality(double gain, double loss);
		virtual ~Quality();
		double getGain() const;
		void setGain(double gain);
		double getLoss() const;
		void setLoss(double loss);
		void addToGain(double gain);
		void addToLoss(double loss);
};

#endif /* QUALITY_H_ */
