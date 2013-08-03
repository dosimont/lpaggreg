/*
 * Node.h
 *
 *  Created on: 25 juil. 2013
 *      Author: dosimont
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include "Quality.h"
#include "Complexity.h"
#include "Eval.h"
#define CHILDS (unsigned int i=0; i<childNodes.size(); i++)
#define CHILD childNodes[i]

using namespace std;

class NodeLPAggreg{
	private:
		int id;
		int rank;
		double value;
		NodeLPAggreg *parent;
		vector<NodeLPAggreg*> childNodes;
		Quality *quality;
		bool aggregated;
		int size;
		double entSum;
		Eval *eval;
		vector<int> *bestPartitions;


	public:
		NodeLPAggreg();
		NodeLPAggreg(int id, int value);
		NodeLPAggreg(NodeLPAggreg* parent, int id, int value);
		virtual ~NodeLPAggreg();
		void addChild(NodeLPAggreg* child);
		NodeLPAggreg* getParent();
		Quality* getQuality();
		void setQuality(Quality *quality);
		void computeQuality();
		bool hasChild();
		bool hasParent();
		void setParent(NodeLPAggreg* parent);
		const vector<NodeLPAggreg*>& getChildNodes() const;
		bool isAggregated() const;
		int getId() const;
		void setId(int id);
		double getValue() const;
		void setValue(double value);
		double getEntSum() const;
		int getSize() const;
		void normalize(double maxGain, double maxLoss);
		double computeAggregation(float parameter);
		void computeBestPartitions();
		int fillBestPartitions(vector<int>*bestPartition, int p);
		void setAggregated(bool aggregated);
		Eval* getEval();
		void setEval(Eval* eval);
		void init(bool normalization);
		vector<int> * getAggregation(float parameter);
		int getQualityDuration(); //ms
		int getBestCutDuration(); //ms
		int getBestPartitionDuration(); //ms
		int getQualityCount();
		int getBestCutCount();
		int getBestPartitionCount();
		int getRank() const;
		void setRank(int rank);
};

#endif /* NODE_H_ */
