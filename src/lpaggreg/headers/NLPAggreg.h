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

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include "Quality.h"
#include "Complexity.h"
#include "Eval.h"
#include "Configuration.h"
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
		vector<float> parameters;
		vector<Quality*> qualityList;

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
		vector<int> * getAggregation(float parameter);
		double getQualityDuration(); //ms
		double getBestCutDuration(); //ms
		double getBestPartitionDuration(); //ms
		long getQualityCount();
		long getBestCutCount();
		long getBestPartitionCount();
		int getRank() const;
		void setRank(int rank);
		bool ownsNode(NLPAggreg* node);
		unsigned int childNodeSize();
		void deleteParameters();

		void computeBestQualities(float threshold);
		void computeBestQuality(Quality *bestQuality);
		void fillQuality(Quality *bestQuality);
		void addBestQualities(float parameter1, float parameter2,
				Quality *bestQuality1, Quality *bestQuality2, float threshold);
		void deleteQualityList();
		vector<float> getParameters(float threshold);
		const vector<Quality*>& getQualityList() const;
};

#endif /* NODE_H_ */
