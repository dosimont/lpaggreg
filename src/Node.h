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
#define CHILDS (unsigned int i=0; i<childNodes.size(); i++)
#define CHILD childNodes[i]

using namespace std;

class Node{
	private:
		int id;
		double value;
		Node *parent;
		vector<Node*> childNodes;
		Quality *quality;
		bool aggregated;
		int size;
		double entSum;


	public:
		Node();
		Node(Node* parent, int id);
		virtual ~Node();
		void addChild(Node* child);
		void updateParents();
		Node* getParent();
		Quality* getQuality();
		void setQuality(Quality *quality);
		void computeQuality();
		bool hasChild();
		void setParent(Node* parent);
		const vector<Node*>& getChildNodes() const;
		bool isAggregated() const;
		int getId() const;
		void setId(int id);
		double getValue() const;
		void setValue(double value);
		double getEntSum() const;
		int getSize() const;
		void normalize(double maxGain, double maxLoss);
		double computeAggregation(float parameter);
		vector<int> * computeBestPartitions();
		int fillBestPartitions(vector<int>*bestPartition, int p);
		void setAggregated(bool aggregated);
};

#endif /* NODE_H_ */
