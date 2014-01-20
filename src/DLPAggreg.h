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
#include <algorithm>
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
		vector<vector<Quality*>> qualities;
		double ** optimalCompromise;
		vector<vector<DLPCut*>> optimalCuts;
		vector<int> optimalPartitions;
		double ** pIC;
		int nodeSize;
		int valueSize;
		int * partCounter;
		Eval *eval;

	public:
		DLPAggreg();
		DLPAggreg(DLPAggreg* parent, int id);
		virtual ~DLPAggreg();
		DLPAggreg* getParent();
		int getNodeSize() const;
		bool hasChild();
		bool hasParent();
		void addChild(DLPAggreg* child);
		void setParent(DLPAggreg* parent);
		const vector<DLPAggreg*>& getChildNodes() const;
		int getId() const;
		void setId(int id);
		void normalize(double maxGain = 0, double maxLoss = 0);
		void computeBestPartitions();
		void computeBestCut(float parameter);
		int fillPartition(int start, int end, int *counter);
		Eval* getEval();
		void setEval(Eval* eval);
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
		double sumOptimalCompromise(int i, int j);
		double computePIC(float parameter, int i, int j);
		double** getOptimalCompromise() const;
		const vector<vector<DLPCut*> >& getOptimalCuts() const;
		double** getPIC() const;
		const vector<vector<Quality*> >& getQualities() const;
		int getValueSize() const;
};

#endif /* DLPAGGREG_H_ */
