/*
 * Configuration.h
 *
 *  Created on: 23 janv. 2014
 *      Author: dosimont
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_


/*Activate Evaluation Counters and Timers*/
//#define EVAL

/*Include sys/time.h library specific to Linux Systems*/
//#define LINUX

/*Use Shannon Entropy to compute Gain instead of SizeReduction*/
#define ENTROPY 1

/*Don't modify from here*/
#if ENTROPY
#define SIZEREDUCTION 0
#else
#define SIZEREDUCTION 1
#endif


#ifdef EVAL
#define EVALQC_ eval.incrQCounter()
#define EVALQC(n) eval.incrQCounter(n)
#define EVALBCC_ eval.incrBCCounter()
#define EVALBCC(n) eval.incrBCCounter(n)
#define EVALBPC_ eval.incrBPCounter()
#define EVALBPC(n) eval.incrBPCounter(n)
#define _EVALQC_ eval->incrQCounter()
#define _EVALQC(n) eval->incrQCounter(n)
#define _EVALBCC_ eval->incrBPCounter()
#define _EVALBCC(n) eval->incrBPCounter(n)
#define _EVALBPC_ eval->incrBPCounter()
#define _EVALBPC(n) eval->incrBPCounter(n)
#define EVALSTARTQ eval.resetQCounter();\
				eval.startQTimer()
#define EVALSTARTBC eval.resetBCCounter();\
				eval.startBCTimer()
#define EVALSTARTBP eval.resetBPCounter();\
				eval.startBPTimer()
#define EVALSTOPQ eval.stopQTimer();
#define EVALSTOPBC eval.stopBCTimer();
#define EVALSTOPBP eval.stopBPTimer();
#define _EVALSTARTQ eval->resetQCounter();\
				eval->startQTimer()
#define _EVALSTARTBC eval->resetBCCounter();\
				eval->startBCTimer()
#define _EVALSTARTBP eval->resetBPCounter();\
				eval->startBPTimer()
#define _EVALSTOPQ eval->stopQTimer();
#define _EVALSTOPBC eval->stopBCTimer();
#define _EVALSTOPBP eval->stopBPTimer();

#else
#define EVALQC_
#define EVALQC(n)
#define EVALBCC_
#define EVALBCC(n)
#define EVALBPC_
#define EVALBPC(n)
#define _EVALQC_
#define _EVALQC(n)
#define _EVALBCC_
#define _EVALBCC(n)
#define _EVALBPC_
#define _EVALBPC(n)
#define EVALSTARTQ
#define EVALSTARTBC
#define EVALSTARTBP
#define EVALSTOPQ
#define EVALSTOPBC
#define EVALSTOPBP
#define _EVALSTARTQ
#define _EVALSTARTBC
#define _EVALSTARTBP
#define _EVALSTOPQ
#define _EVALSTOPBC
#define _EVALSTOPBP
#endif


#endif /* CONFIGURATION_H_ */
