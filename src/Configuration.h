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
#define EVALQC eval->incrQCounter()
#define EVALQC(n) eval->incrQCounter(n)
#define EVALBCC eval->incrBPounter()
#define EVALBCC(n) eval->incrBPounter(n)
#define EVALBPC eval->incrBPounter()
#define EVALBPC(n) eval->incrBPounter(n)
#endif


#endif /* CONFIGURATION_H_ */
