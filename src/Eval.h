/*
 * Timer.h
 *
 *  Created on: 20 juin 2013
 *      Author: dosimont
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <cstdlib>
#include <sys/time.h>

class Eval {
		
	private:
		timeval timeQ1, timeQ2, timeBC1, timeBC2, timeBP1, timeBP2;
		int counterQ, counterBC, counterBP;

	public:
		Eval();
		void startQTimer();
		void stopQTimer();
		void startBCTimer();
		void stopBCTimer();
		void startBPTimer();
		void stopBPTimer();
		int getQDuration(); //ms
		int getBCDuration(); //ms
		int getBPDuration(); //ms
		void resetQCounter();
		void resetBCCounter();
		void resetBPCounter();
		void resetCounters();
		void incrQCounter(int i = 1);
		void incrBCCounter(int i = 1);
		void incrBPCounter(int i = 1);
		int getQCount();
		int getBCCount();
		int getBPCount();
		virtual ~Eval();
};

#endif /* TIMER_H_ */
