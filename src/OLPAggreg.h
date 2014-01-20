/*
 * OLPAggreg.h
 *
 *  Created on: 10 oct. 2013
 *      Author: dosimont
 */

#ifndef OLPAGGREG_H_
#define OLPAGGREG_H_

#include <math.h>
#include "Quality.h"
#include "Eval.h"
#include "Complexity.h"
#include <vector>

using namespace std;

class OLPAggreg { //ABC

	protected:
		
		/*Number of vector of scalar of input matrix*/
		int size;

		/*Matrix that contains quality measures for each aggregate*/
		vector<vector<Quality*> > qualities;

		/*Tab that contains best cuts for current parameter*/
		int * bestCuts;

		/*Vector that contains best partitions for current parameter*/
		vector<int> bestPartitions;

		/*Vector that contains a list of relevant parameters obtained
		 * by dichomoty computation
		 */
		vector<float> parameters;

		/*Vector that contains qualities related to parameter list*/
		vector<Quality*> qualityList;

		/*Eval class for time and counter measurements*/
		Eval eval;

	protected:
		
		/*Deallocate quality matrix*/
		void deleteQualities();

		/*Size reduction formula method*/
		int sizeReduction(int size);

		/*Compute best cuts for a given parameter p*/
		void computeBestCuts(float parameter);

		/*Deallocate bestCuts pointer*/
		void deleteBestCuts();

		/*Compute aggregation best partitions*/
		void computeBestPartitions();

		/*Delete bestPartitions pointer*/
		void deleteBestPartitions();

		/*Fill partitions*/
		int fillPartition(int i, int p);

		/*Define aggregation matrix size (number of vectors/scalars*/
		void setSize(int size);

		/*Compute best qualities (and parameter list) by dichotomy for a given threshold*/
		void computeBestQualities(float threshold);

		/*Compute best quality*/
		void computeBestQuality(Quality *bestQuality);

		/*Fill quality vector*/
		void fillQuality(int i, Quality *bestQuality);

		/*Add best qualities*/
		void addBestQualities(float parameter1, float parameter2,
				Quality *bestQuality1, Quality *bestQuality2, float threshold);

		/*Deallocate quality list*/
		void deleteQualityList();

		/*Deallocate parameters list*/
		void deleteParameters();

	public:
		
		/*Constructor*/
		OLPAggreg();

		/*Destructor*/
		virtual ~OLPAggreg();
		vector<int> getParts(float parameter);
		vector<float> getParameters(float threshold);
		const vector<Quality*>& getQualityList() const;
		int getQualityDuration(); //ms
		int getBestCutDuration(); //ms
		int getBestPartitionDuration(); //ms
		int getQualityCount();
		int getBestCutCount();
		int getBestPartitionCount();
		unsigned int getSize();
		
};

#endif /* OLPAGGREG_H_ */
