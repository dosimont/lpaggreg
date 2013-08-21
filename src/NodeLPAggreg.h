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

template <typename Value>
class NodeLPAggreg{
	private:
		typedef Value values;
		int id;
		int rank;
		NodeLPAggreg<Value> *parent;
		vector<NodeLPAggreg<Value>*> childNodes;
		Quality *quality;
		bool aggregated;
		int size;
		double entSum;
		Eval *eval;
		vector<int> *bestPartitions;


	public:
		NodeLPAggreg();
		NodeLPAggreg(int id, Value values);
		NodeLPAggreg(NodeLPAggreg<Value>* parent, int id, Value values);
		virtual ~NodeLPAggreg<Value>();
		Value getValue();
		void setValue(Value value);
		NodeLPAggreg<Value>* getParent();
		Quality* getQuality();
		void setQuality(Quality *quality);
		void computeQuality();
		void computeQuality(double value);
		void computeQuality(vector<double> values);
		void computeQuality(vector< vector<double> > values);
		void computeQuality_Vector(int index);
		void computeQuality_Matrix(int i, int j);
		bool hasChild();
		bool hasParent();
		void addChild(NodeLPAggreg<Value>* child);
		void setParent(NodeLPAggreg<Value>* parent);
		const vector<NodeLPAggreg<Value>*>& getChildNodes() const;
		bool isAggregated() const;
		int getId() const;
		void setId(int id);
		double getEntSum() const;
		int getSize() const;
		void normalize(double maxGain=0, double maxLoss=0);
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
		bool ownsNode(NodeLPAggreg<Value>* node);
		unsigned int childNodeSize();
};

#endif /* NODE_H_ */
