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
#include "DLPCut.h"

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
		vector<vector<Quality*> > qualities;
		double ** optimalCompromises;
		vector<vector<DLPCut*> > optimalCuts;
		vector<int> optimalPartitions;
		double ** pIC;
		int nodeSize;
		int valueSize;
		Eval *eval;

	public:
		/*Constructors/Destructors*/
		DLPAggreg();
		DLPAggreg(int id);
		DLPAggreg(DLPAggreg* parent, int id);
		virtual ~DLPAggreg();

		//delete
		void deleteChildNodes();
		void deleteQualities();
		void clean();
		void deleteEval();

		/*Node Management*/

		//Parent
		DLPAggreg* getParent();
		bool hasParent();
		void setParent(DLPAggreg* parent);

		//Childs

		int getNodeSize() const;
		void addChild(DLPAggreg* child);
		bool hasChild();
		const vector<DLPAggreg*>& getChildNodes() const;
		bool ownsNode(DLPAggreg* node);
		unsigned int childNodeSize();

		//Id
		int getId() const;
		void setId(int id);

		//Rank
		int getRank() const;
		void setRank(int rank);

		/*Evaluation stuffs*/

		//Eval
		Eval* getEval();
		void setEval(Eval* eval);

		//Counter getters
		int getQualityCount();
		int getBestCutCount();
		int getBestPartitionCount();

		//Timer getters
		int getQualityDuration(); //ms
		int getBestCutDuration(); //ms
		int getBestPartitionDuration(); //ms

		/*DLP algo*/

		//Quality Computation//
		//->To implement//
		void normalize(double maxGain = 0, double maxLoss = 0);

		//Best Cut Computation
		void computeBestCut(double parameter);
		double sumOptimalCompromise(int i, int j);
		double computePIC(double parameter, int i, int j);

		//Best Partition Computation

		void computeBestPartitions();
		void fillPartition(int start, int end, int *counter);
		void setPartitions(int start, int end, int value);


		//BC & BP
		void computeAggregation(double parameter);

		//Getters and setters
		int getValueSize() const;
		const vector<vector<Quality*> > & getQualities() const;
		double** getOptimalCompromises() const;
		const vector<vector<DLPCut*> > & getOptimalCuts() const;
		double** getPIC() const;
		const vector<int>& getOptimalPartitions() const;
};

#endif /* DLPAGGREG_H_ */
