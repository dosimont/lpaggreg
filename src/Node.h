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
#include <Quality.h>

using namespace std;

class Node {
	private:
		double value;
		Node *parent;
		vector<Node*> childNodes;
		vector<double> childValues;
		Quality *quality;

	public:
		Node();
		virtual ~Node();
		void addChild(Node *child);
		void addChild(double child);
		void updateParents();
		double getValue();
		vector<Node*> getChildNodes(int i);
		vector<double> getChildValues(int i);
		int getChildNodesNumber();
		int getChildValuesNumber();
		Node* getParent();
		Quality* getQuality();
		void setQuality(Quality *quality);
		bool hasChild();
		void setParent(Node* parent);
};

#endif /* NODE_H_ */
