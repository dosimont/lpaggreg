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
#define CHILDS (unsigned int i_child=0; i_child<childNodes.size(); i_child++)
#define NCHILDS(n) (unsigned int i_child=0; i_child<n->childNodeSize(); i_child++)
#define CHILD childNodes[i_child]
#define NCHILD(n) n->getChildNodes()[i_child]

using namespace std;

class NLPAggreg {
		
	protected:
		int id;
		int rank;
		NLPAggreg *parent;
		vector<NLPAggreg*> childNodes;
		Quality *quality;
		bool aggregated;
		int size;
		double entSum;
		Eval *eval;
		vector<int> *bestPartitions;

	public:
		NLPAggreg();
		NLPAggreg(NLPAggreg* parent, int id);
		virtual ~NLPAggreg();
		NLPAggreg* getParent();
		Quality* getQuality();
		void setQuality(Quality *quality);
		bool hasChild();
		bool hasParent();
		void addChild(NLPAggreg* child);
		void setParent(NLPAggreg* parent);
		const vector<NLPAggreg*>& getChildNodes() const;
		bool isAggregated() const;
		int getId() const;
		void setId(int id);
		double getEntSum() const;
		int getSize() const;
		void normalize(double maxGain = 0, double maxLoss = 0);
		double computeAggregation(float parameter);
		void computeBestPartitions();
		int fillBestPartitions(vector<int>*bestPartition, int p);
		void setAggregated(bool aggregated);
		Eval* getEval();
		void setEval(Eval* eval);
		void computeQualities(bool normalization);
		vector<int> * getAggregation(float parameter);
		int getQualityDuration(); //ms
		int getBestCutDuration(); //ms
		int getBestPartitionDuration(); //ms
		int getQualityCount();
		int getBestCutCount();
		int getBestPartitionCount();
		int getRank() const;
		void setRank(int rank);
		bool ownsNode(NLPAggreg* node);
		unsigned int childNodeSize();
};

/*
 * Node.cpp
 *
 *  Created on: 25 juil. 2013
 *      Author: dosimont
 */

#endif /* NODE_H_ */
