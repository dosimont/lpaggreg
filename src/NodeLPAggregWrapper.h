/*
 * NodeLPAggregWrapper.h
 *
 *  Created on: 20 août 2013
 *      Author: dosimont
 */

#ifndef NODELPAGGREGWRAPPER_H_
#define NODELPAGGREGWRAPPER_H_

#include "NodeLPAggreg.h"
#include "Quality.h"
#include <vector>
#include <map>

class NodeLPAggregWrapper {
	private:
		NodeLPAggreg * root;
		vector<NodeLPAggreg *> nodes;
		map<int, bool> aggregatedId;

		/*List of relevant parameters get by dichotomy*/
		vector<float> parameters;

		/*List of associated qualities to parameter list*/
		vector<Quality*> qualities;

	public:
		NodeLPAggregWrapper();
		virtual ~NodeLPAggregWrapper();

		/*Algo step 1 : compute qualities*/
		void computeQualities(bool normalization);

		/*Algo step 2 : compute parts for a parameter*/
		void computeAggregation(float parameter);

		/*Algo step 2 : compute relevant parameter list by using dichotomy*/
		void computeDichotomy(float threshold);

		bool isAggregated(int id);

	private:
		void computeAggregatedId(NodeLPAggreg * node);

//		/*Get the parameter with index "index"*/
//		float getParameter(int index);
//
//		/*Get the parameter number*/
//		int getParameterNumber();
//
//		/*Get the gain by index*/
//		double getGainByIndex(int index);
//
//		/*Get the gain by parameter*/
//		double getGainByParameter(float parameter);
//
//		/*Get the loss by index*/
//		double getLossByIndex(int index);
//
//		/*Get the loss by parameter*/
//		double getLossByParameter(float parameter);

};

#endif /* NODELPAGGREGWRAPPER_H_ */
