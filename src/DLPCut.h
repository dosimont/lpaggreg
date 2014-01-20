/*
 * DLPPartition.h
 *
 *  Created on: 16 janv. 2014
 *      Author: dosimont
 */

#ifndef DLPCUT_H_
#define DLPCUT_H_

class DLPCut {
	private:
		int cut;
		bool aggregated;

	public:
		DLPCut();
		DLPCut(int partition, bool aggregated);
		virtual ~DLPCut();
		bool isAggregated() const;
		void setAggregated(bool aggregated);
		int getCut() const;
		void setCut(int partition);
		void setAll(int partition, bool aggregated);
};

#endif /* DLPCUT_H_ */
