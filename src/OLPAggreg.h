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

#ifndef OLPAGGREG_H_
#define OLPAGGREG_H_

#include <math.h>
#include "Quality.h"
#include "Eval.h"
#include "Complexity.h"
#include <vector>
#include "Configuration.h"

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
		double getQualityDuration(); //ms
		double getBestCutDuration(); //ms
		double getBestPartitionDuration(); //ms
		long getQualityCount();
		long getBestCutCount();
		long getBestPartitionCount();
		void normalize(int n);
		unsigned int getSize();
		
};

#endif /* OLPAGGREG_H_ */
