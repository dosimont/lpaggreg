/*******************************************************************************
 *
 * This library is a C++ implementation of several algorithms that enables
 * to aggregate set of data according: an ordered dimension (OLP), a
 * hierarchy (NLP), or both (DLP). OLP and NLP scalar versions (1) have been
 * designed by Robin Lamarche-Perrin. OLP and NLP vector versions (2, 3) and
 * DLP (1, 2) have been designed by Damien Dosimont and are a generalization
 * of Robin Lamarche-Perrin works.
 *
 * Related works:
 * http://magma.imag.fr/content/robin-lamarche-perrin
 * http://moais.imag.fr/membres/damien.dosimont/research.html
 *
 *
 * (C) Copyright (February 28th 2013) Damien Dosimont. All rights reserved.
 *
 * Damien Dosimont <damien.dosimont@imag.fr>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 *******************************************************************************/

#ifndef DLPAGGREG_H_
#define DLPAGGREG_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include "Quality.h"
#include "Complexity.h"
#include "Eval.h"
#include "DLPCut.h"
#include "Configuration.h"

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
		double ** bestCompromises;
		vector<vector<DLPCut*> > bestCuts;
		vector<int> bestPartitions;
		vector<float> parameters;
		vector<Quality*> qualityList;
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
		void deleteBestCuts();
		void clean();
		void deleteEval();
		void deleteParameters();

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
		void cleanChilds();

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
		void computeBestCuts(double parameter);
		double sumBestCompromises(int i, int j);
		double computePIC(double parameter, int i, int j);

		//Best Partition Computation

		void computeBestPartitions();
		void fillPartition(int start, int end, int *counter);
		void setPartitions(int start, int end, int value);

		//Dichotomy
		void computeBestQualities(float threshold);
		void computeBestQuality(Quality *bestQuality);
		void fillQuality(int start, int end, Quality *bestQuality);
		void addBestQualities(float parameter1, float parameter2,
				Quality *bestQuality1, Quality *bestQuality2, float threshold);
		void deleteQualityList();
		const vector<float>& getParameters(float threshold);
		const vector<Quality*>& getQualityList() const;


		//BC & BP
		void computeAggregation(double parameter);
		bool hasFullAggregation();

		//Getters and setters
		int getValueSize() const;
		const vector<vector<Quality*> > & getQualities() const;
		double** getBestCompromises() const;
		const vector<vector<DLPCut*> > & getBestCuts() const;
		double** getPIC() const;
		const vector<int>& getBestPartitions() const;
};

#endif /* DLPAGGREG_H_ */
