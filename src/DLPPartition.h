/*
 * DLPPartition.h
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#ifndef DLPPARTITION_H_
#define DLPPARTITION_H_

class DLPPartition {
	private:
		int partition;
		bool aggregated;

	public:
		DLPPartition();
		DLPPartition(int partition, bool aggregated);
		virtual ~DLPPartition();
		bool isAggregated() const;
		void setAggregated(bool aggregated);
		int getPartition() const;
		void setPartition(int partition);
};

#endif /* DLPPARTITION_H_ */
