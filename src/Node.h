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

using namespace std;

class Node {
	private:
		double value;
		vector<Node> children;

	public:
		Node();
		virtual ~Node();
		const vector<Node>& getChildren() const;
		void setChildren(const vector<Node>& children);
		double getValue() const;
		void setValue(double value);
};

/* namespace std */
#endif /* NODE_H_ */
