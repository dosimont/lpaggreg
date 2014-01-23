/*
 * Configuration.h
 *
 *  Created on: 23 janv. 2014
 *      Author: dosimont
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define EVAL

#ifdef EVAL
#define EVALQC_ eval.incrQCounter()
#define EVALQC(n) eval.incrQCounter(n)
#define EVALBCC_ eval->incrBPCounter()
#define EVALBCC(n) eval.incrBPCounter(n)
#define EVALBPC_ eval.incrBPCounter()
#define EVALBPC(n) eval.incrBPCounter(n)
#define EVALQCP_ eval->incrQCounter()
#define EVALQCP(n) eval->incrQCounter(n)
#define EVALBCCP_ eval->incrBPCounter()
#define EVALBCCP(n) eval->incrBPCounter(n)
#define EVALBPCP_ eval->incrBPCounter()
#define EVALBPCP(n) eval->incrBPCounter(n)
#endif


#endif /* CONFIGURATION_H_ */
