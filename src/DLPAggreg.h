/*
 * DLPAggreg.h
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#ifndef DLPAGGREG_H_
#define DLPAGGREG_H_

#include <iostream>
#include <vector>
#include "Quality.h"
#include "Complexity.h"
#include "Eval.h"

#define DCHILDS (unsigned int i_child=0; i_child<childNodes.size(); i_child++)
#define NDCHILDS(n) (unsigned int i_child=0; i_child<n->childNodeSize(); i_child++)
#define DCHILD childNodes[i_child]
#define NDCHILD(n) n->getChildNodes()[i_child]

using namespace std;

class DLPAggreg {
	protected:
		int id;
		int rank;
		DLPAggreg *parent;
		vector<DLPAggreg*> childNodes;
		Quality *quality;
		int size;
		int value_size;
		Eval *eval;

	public:
		DLPAggreg();
		DLPAggreg(DLPAggreg* parent, int id);
		virtual ~DLPAggreg();
		DLPAggreg* getParent();
		Quality* getQuality();
		int getSize() const;
		void setQuality(Quality *quality);
		bool hasChild();
		bool hasParent();
		void addChild(DLPAggreg* child);
		void setParent(DLPAggreg* parent);
		const vector<DLPAggreg*>& getChildNodes() const;
		int getId() const;
		void setId(int id);
		void normalize(double maxGain = 0, double maxLoss = 0);
		double computeAggregation(float parameter);
		void computeBestPartitions();
		//int fillBestPartitions(vector<int>*bestPartition, int p);
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
		bool ownsNode(DLPAggreg* node);
		unsigned int childNodeSize();
};

#endif /* DLPAGGREG_H_ */
