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

#include "DLPAggreg.h"

DLPAggreg::DLPAggreg() :
		id(0), rank(0), parent(0), childNodes(vector<DLPAggreg*>()), qualities(vector<vector<Quality*> >()),
		bestCompromises(vector<vector<Compromise*> >()), bestCuts(vector<vector<DLPCut*> >()), bestPartitions(
						vector<int>()), parameters(vector<double>()), qualityList(
						vector<Quality*>()), pIC(vector<vector<Compromise*> >()), nodeSize(1), valueSize(0), eval(0){
	
}

DLPAggreg::DLPAggreg(DLPAggreg* parent, int id) :
		id(id), rank(0), parent(parent), childNodes(vector<DLPAggreg*>()), qualities(vector<vector<Quality*> >()),
		bestCompromises(vector<vector<Compromise*> >()), bestCuts(vector<vector<DLPCut*> >()), bestPartitions(
						vector<int>()), parameters(vector<double>()), qualityList(
						vector<Quality*>()), pIC(vector<vector<Compromise*> >()), nodeSize(1), valueSize(0), eval(0) {
	parent->addChild(this);
}

DLPAggreg::DLPAggreg(int id) :
		id(id), rank(0), parent(0), childNodes(vector<DLPAggreg*>()), qualities(vector<vector<Quality*> >()),
		bestCompromises(vector<vector<Compromise*> >()), bestCuts(vector<vector<DLPCut*> >()), bestPartitions(
						vector<int>()), parameters(vector<double>()), qualityList(
						vector<Quality*>()), pIC(vector<vector<Compromise*> >()), nodeSize(1), valueSize(0), eval(0) {
}

void DLPAggreg::addChild(DLPAggreg *child) {
	childNodes.push_back(child);
	child->setParent(this);
	child->setRank(rank + 1);
}

DLPAggreg* DLPAggreg::getParent() {
	return parent;
}

DLPAggreg::~DLPAggreg() {
	deleteChildNodes();
	deleteBestCuts();
	deleteQualities();
	deleteQualityList();
	deleteParameters();
	clean();
	if (!hasParent()){

		deleteEval();
	}

}

int DLPAggreg::getId() const {
	return id;
}

void DLPAggreg::setId(int id) {
	this->id = id;
}

const vector<DLPAggreg*>& DLPAggreg::getChildNodes() const {
	return childNodes;
}

int DLPAggreg::getNodeSize() const {
	return nodeSize;
}

void DLPAggreg::setNodeSize(int aWeight) {
	nodeSize = aWeight;
}


void DLPAggreg::setParent(DLPAggreg* parent) {
	this->parent = parent;
}

bool DLPAggreg::hasChild() {
	return !childNodes.empty();
}

void DLPAggreg::normalize(double maxGain, double maxLoss) {
	if (!hasParent()) {
		maxGain = qualities[0][valueSize - 1]->getGain();
		maxLoss = qualities[0][valueSize - 1]->getLoss();
		_EVALQC(2);

	}
	for (int j = 0; j < valueSize; j++) {
		for (int i = 0; i < valueSize - j; i++) {
			if (maxGain != 0) {
				qualities[i][j]->setGain(qualities[i][j]->getGain() / maxGain);
				_EVALQC_;
			}
			if (maxLoss != 0) {
				qualities[i][j]->setLoss(qualities[i][j]->getLoss() / maxLoss);
				_EVALQC_;
			}
			for DCHILDS
			DCHILD->normalize(maxGain, maxLoss);
		}
	}
}

Eval* DLPAggreg::getEval() {
	return eval;
}

bool DLPAggreg::hasParent() {
	return (parent != 0);
}

void DLPAggreg::setEval(Eval* eval) {
	this->eval = eval;
	for DCHILDS
	DCHILD->setEval(eval);
}

void DLPAggreg::computeAggregation(double parameter) {
	if (!hasParent()) {
		_EVALSTARTBC;
		computeBestCuts(parameter);
		_EVALSTOPBC;
		_EVALSTARTBP;
		computeBestPartitions();
		_EVALSTOPBP;
		cleanChilds();
	}
}

void DLPAggreg::computeBestPartitions() {
	bestPartitions.clear();
	for (int i = 0; i < valueSize; i++) {
		bestPartitions.push_back(-1); //WRITE
		_EVALBCC_;
	}
	for DCHILDS
	DCHILD->computeBestPartitions();
	if (!hasParent()){
		int *partCounter=new int;
		*partCounter=0;
		_EVALBCC_;
		fillPartition(0, valueSize - 1, partCounter);
		delete partCounter;
	}
}

void DLPAggreg::fillPartition(int start, int end, int * counter) {
	DLPCut c = *bestCuts[start][end-start]; //WRITE
	_EVALBCC_;
	if (c.isAggregated()){
		setPartitions(c.getCut(), end, *counter);//TODO verificar
		(*counter)++;
		_EVALBPC(2);
		if (c.getCut()>start)
			fillPartition(start, c.getCut()-1, counter);
	}else{
		setPartitions(c.getCut(), end, -1);
		for DCHILDS
		DCHILD->fillPartition(c.getCut(), end, counter);
		if (c.getCut()>start)
			fillPartition(start, c.getCut()-1, counter);
	}
}

void DLPAggreg::setPartitions(int start, int end, int value){
	for (int i=start; i<=end; i++){
		bestPartitions[i]=value;
		_EVALBCC_;
	}
	if (value>-1){
		for DCHILDS
		DCHILD->setPartitions(start, end, value);
	}
}

double DLPAggreg::getQualityDuration() {
	return eval->getQDuration();
}

double DLPAggreg::getBestCutDuration() {
	return eval->getBCDuration();
}

double DLPAggreg::getBestPartitionDuration() {
	return eval->getBPDuration();
}

long DLPAggreg::getQualityCount() {
	return eval->getQCount();
}

long DLPAggreg::getBestCutCount() {
	return eval->getBCCount();
}

long DLPAggreg::getBestPartitionCount() {
	return eval->getBPCount();
}

int DLPAggreg::getRank() const {
	return rank;
}

void DLPAggreg::setRank(int rank) {
	this->rank = rank;
	for DCHILDS
	DCHILD->setRank(rank+1);
}

bool DLPAggreg::ownsNode(DLPAggreg* node) {
	if (this == node)
		return true;
	if (hasChild()) {
		for DCHILDS
		if (DCHILD->ownsNode(node))
		return true;
	}
	return false;
}

const vector<vector<Compromise*> > & DLPAggreg::getBestCompromises() const {
	return bestCompromises;
}

const vector<vector<DLPCut*> >& DLPAggreg::getBestCuts() const {
	return bestCuts;
}

const vector<vector<Compromise*> > & DLPAggreg::getPIC() const {
	return pIC;
}

const vector<vector<Quality*> >& DLPAggreg::getQualities() const {
	return qualities;
}

void DLPAggreg::sumBestCompromises(int i, int j, Compromise * C) {
	for DCHILDS
	C->add(DCHILD->getBestCompromises()[i][j]);
	_EVALBCC(childNodeSize()+1);
}

void DLPAggreg::computePIC(double parameter, int i, int j, Compromise *C) {
	C->setValue(((double) parameter) * qualities[i][j]->getGain()- ((1 - (double) parameter) * qualities[i][j]->getLoss()));
	C->setGain(qualities[i][j]->getGain());
	C->setLoss(qualities[i][j]->getLoss());
}

void DLPAggreg::computeBestCuts(double parameter) {
	bestCompromises = vector<vector<Compromise*> >();
	bestCuts = vector<vector<DLPCut*> >();
	pIC = vector<vector<Compromise*> >();
	int i;
	for (i = 0; i < valueSize; i++) {
		bestCompromises.push_back(vector<Compromise*>());
		pIC.push_back(vector<Compromise*>());
		bestCuts.push_back(vector<DLPCut*>());
		for (int j = 0; j < valueSize; j++) {
			bestCuts[i].push_back(new DLPCut());
			bestCompromises[i].push_back(new Compromise());
			pIC[i].push_back(new Compromise());
			_EVALBCC_;
		}
	}
	if (!hasChild()) {
		for (int k = valueSize - 1; k >= 0; k--) {
			computePIC(parameter, k, 0, pIC[k][0]);
			bestCompromises[k][0]->set(pIC[k][0]);
			bestCuts[k][0]->setAll(k, true);
			_EVALBCC(4);
			for (int j = 1; j < valueSize - k; j++) {
				DLPCut currentCut = DLPCut(k, true);
				computePIC(parameter, k, j, pIC[k][j]);
				Compromise currentCompromise(pIC[k][j]);
				_EVALBCC(4);
				for (int cut = 1; cut <= j; cut++) {
					Compromise compromise(bestCompromises[k][cut - 1]);
					compromise.add(pIC[cut + k][j - cut]);

					_EVALBCC(1);
					if (compromise.isGreater(currentCompromise)) {
						currentCompromise.set(compromise);
						currentCut.setAll(cut + k, true);
						_EVALBCC(3);
					}
				}
				bestCompromises[k][j]->set(currentCompromise);
				bestCuts[k][j]->setAll(currentCut.getCut(),
						currentCut.isAggregated());
				_EVALBCC(3);
			}
		}
	}
	else {
		for DCHILDS
		DCHILD->computeBestCuts(parameter);
		for (int k=valueSize-1; k>=0; k--) {
			computePIC(parameter, k, 0, pIC[k][0]);
			Compromise *s = new Compromise;
			sumBestCompromises(k,0, s);
			bestCompromises[k][0]->setGreatest(pIC[k][0], s);
			bestCuts[k][0]->setAll(k, pIC[k][0]->isEqual(bestCompromises[k][0]));
			delete s;
			_EVALBCC(4);
			for (int j=1; j<valueSize-k; j++) {
				computePIC(parameter, k, j, pIC[k][j]);//replace double by three double: pic, gain, loss
				Compromise *currentCompromise=new Compromise();
				Compromise *t=new Compromise();
				sumBestCompromises(k,j, t);
				currentCompromise->setGreatest(pIC[k][j], t);
				DLPCut currentCut = DLPCut(k, pIC[k][j]->isEqual(currentCompromise));
				delete t;
				_EVALBCC(4);
				for (int cut=1; cut<=j; cut++) {
					Compromise* compromise= new Compromise();
					Compromise* u= new Compromise();
					sumBestCompromises(cut+k, j-cut, u);
					compromise->setGreatest(pIC[cut+k][j-cut], u);
					compromise->add(bestCompromises[k][cut-1]);
					delete u;
					_EVALBCC_;
					if (compromise->isGreater(currentCompromise)){
						currentCompromise->set(compromise);
						Compromise temp(pIC[cut+k][j-cut]);
						temp.add(bestCompromises[k][cut-1]);
						currentCut.setAll(cut+k, temp.isEqual(compromise));
						_EVALBCC(3);
					}
					delete compromise;
				}
				bestCompromises[k][j]->set(currentCompromise);
				delete currentCompromise;
				bestCuts[k][j]->setAll(currentCut.getCut(), currentCut.isAggregated());
				_EVALBCC(3);
			}
		}
	}
}

int DLPAggreg::getValueSize() const {
	return valueSize;
}

unsigned int DLPAggreg::childNodeSize() {
	return childNodes.size();
}

void DLPAggreg::deleteChildNodes(){
	if (hasChild()){
	for DCHILDS
	delete DCHILD;
	childNodes.clear();
	}
}

void DLPAggreg::deleteQualities(){
	for (int i=qualities.size()-1; i>=0; i--) {
		for (int j=qualities[i].size()-1; j>=0; j--) {
			delete qualities[i][j];
		}
		qualities[i].clear();
	}
	qualities.clear();
}



void DLPAggreg::clean(){
	for (int i=pIC.size()-1; i>=0; i--) {
		for (int j=pIC[i].size()-1; j>=0; j--) {
			delete pIC[i][j];
		}
		pIC[i].clear();
	}
	pIC.clear();
	for (int i=bestCompromises.size()-1; i>=0; i--) {
		for (int j=bestCompromises[i].size()-1; j>=0; j--) {
			delete bestCompromises[i][j];
		}
		bestCompromises[i].clear();
	}
	bestCompromises.clear();
}




void DLPAggreg::deleteEval(){
	delete eval;
}

const vector<int>& DLPAggreg::getBestPartitions() const {
	return bestPartitions;
}

void DLPAggreg::computeBestQualities(float threshold) {
	Quality *bestQualityParam0 = new Quality();
	Quality *bestQualityParam1 = new Quality();
	computeBestCuts(0);
	computeBestQuality(bestQualityParam0);
	cleanChilds();
	parameters.push_back(0);
	qualityList.push_back(bestQualityParam0);
	computeBestCuts(1);
	computeBestQuality(bestQualityParam1);
	cleanChilds();
	addBestQualities(0, 1, bestQualityParam0, bestQualityParam1, threshold);
	parameters.push_back(1);
	qualityList.push_back(bestQualityParam1);
	for (unsigned int i = qualityList.size() - 1; i > 0; i--) {
		if (qualityList[i]->compare(*qualityList[i-1])) {
			delete qualityList[i];
			qualityList.erase(qualityList.begin() + i);
			parameters.erase(parameters.begin() + i);
		}
	}
}

void DLPAggreg::computeBestQuality(Quality* bestQuality) {
	bestQuality->setGain(0);
	bestQuality->setLoss(0);
	fillQuality(0, valueSize-1, bestQuality);
}

void DLPAggreg::fillQuality(int start, int end, Quality* bestQuality) {
	DLPCut c = *bestCuts[start][end-start]; //WRITE
	if (c.isAggregated()){
		if (c.getCut()>start)
			fillQuality(start, c.getCut()-1, bestQuality);
		bestQuality->addToGain(qualities[c.getCut()][end-c.getCut()]->getGain());
		bestQuality->addToLoss(qualities[c.getCut()][end-c.getCut()]->getLoss());
	}else{
		for DCHILDS
			DCHILD->fillQuality(c.getCut(), end, bestQuality);

		if (c.getCut()>start)
			fillQuality(start, c.getCut()-1, bestQuality);
	}

}

void DLPAggreg::addBestQualities(float parameter1, float parameter2,
		Quality* bestQuality1, Quality* bestQuality2, float threshold) {
	if ((!(bestQuality1->getGain() == bestQuality2->getGain())
			&& !(bestQuality1->getLoss() == bestQuality2->getLoss())
			&& (parameter2 - parameter1 > threshold))) {
		float parameter = parameter1 + ((parameter2 - parameter1) / 2);
		Quality *bestQuality = new Quality();
		computeBestCuts(parameter);
		computeBestQuality(bestQuality);
		cleanChilds();
		addBestQualities(parameter1, parameter, bestQuality1, bestQuality,
				threshold);
		parameters.push_back(parameter);
		qualityList.push_back(bestQuality);
		addBestQualities(parameter, parameter2, bestQuality, bestQuality2,
				threshold);
	}
}

void DLPAggreg::deleteQualityList() {
	for (unsigned int i = 0; i < qualityList.size(); i++)
		delete qualityList[i];
	qualityList.clear();
}

void DLPAggreg::deleteBestCuts() {
	for (int i=bestCuts.size()-1; i>=0; i--) {
		for (int j=bestCuts[i].size()-1; j>=0; j--) {
			delete bestCuts[i][j];
		}
		bestCuts[i].clear();
	}
	bestCuts.clear();
}

const vector<double>& DLPAggreg::getParameters(float threshold) {
	deleteParameters();
	deleteQualityList();
	computeBestQualities(threshold);
	return parameters;

}

const vector<Quality*>& DLPAggreg::getQualityList() const {
	return qualityList;
}

void DLPAggreg::deleteParameters() {
	parameters.clear();
}

void DLPAggreg::cleanChilds() {
	deleteBestCuts();
	clean();
	if (hasChild()){
	for DCHILDS
	DCHILD->cleanChilds();
	}
}

bool DLPAggreg::hasFullAggregation() {
	for (unsigned int i=0; i<bestPartitions.size(); i++)
		if (bestPartitions[i]==-1)
			return false;
	return true;
}
