/*******************************************************************************
 *
 * This library is a C++ implementation of an algorithm designed by Robin
 * Lamarche-Perrin. This algorithm enables to aggregate sets of scalar or vector
 * data, according aggregation gain & information loss ratio parameter.
 * More information in "Robin Lamarche-Perrin, Yves Demazeau and Jean-Marc
 * Vincent. The Best-partitions Problem: How to Build Meaningful Agregations?
 * Research report RR-LIG-XXX, Laboratoire d’Informatique de Grenoble, France,
 * Feb. 2013. (forthcoming)"
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

/*Author : Damien Dosimont <damien.dosimont@imag.fr>*/

/*LPAggreg header file
 *
 * Virtual class that contains methods enabling to perform LP aggregation computation
 * and get aggregated parts, a list of relevant parameters obtained by dichotomy and
 * their associated quality measures
 *
 * computeQualities(bool normalization) method is virtual and need to be implemented
 * in child classes
 */

#ifndef LPAGGREG_H_
#define LPAGGREG_H_

#include <iostream>
#include <vector>
#include <math.h>
#include "Quality.h"
#include "Timer.h"

using namespace std;

class LPAggreg { //ABC
	private:

		/*Number of vector of scalar of input matrix*/
		int size;
		Timer timer;

	protected:

		/*Matrix that contains quality measures for each aggregate*/
		vector< vector<Quality*> > qualities;

		/*Tab that contains best cuts for current parameter*/
		int * bestCuts;

		/*Vector that contains best partitions for current parameter*/
		vector<int> bestPartitions;

		/*Vector that contains a list of relevant parameters obtained
		 * by dichomoty computation
		 */
		vector<float> parametersD;

		/*Vector that contains qualities related to parametersD list*/
		vector<Quality*> qualitiesD;

	protected:
		/*This method has to be overridden. It computes quality matrix.
		 * bool normalization: if true, quality measures are normalized
		 */
		virtual void computeQualities(bool normalization)=0;

		/*Deallocate quality matrix*/
		void deleteQualities();

		/*Entropy formula method*/
		inline double entropy(double value);

		/*Entropy reduction formula method*/
		double entropyReduction(double value, double ent);

		/*Size reduction formula method*/
		int sizeReduction(int size);

		/*Divergence formula method*/
		double divergence(int size, double value, double ent);

		/*Compute best cuts for a given parameter p*/
		void computeBestCuts(float parameter);

		/*Deallocate bestCuts pointer*/
		void deleteBestCuts();

		/*Compute aggregation best partitions*/
		void computeBestPartitions();

		/*Delete bestPartitions pointer*/
		void deleteBestPartitions();

		/*Fill partitions TODO params*/
		int fillPartition(int i, int p);

		/*Define aggregation matrix size (number of vectors/scalars*/
		void setSize(int size);

		/*Compute best qualities (and parameter list) by dichotomy for a given threshold*/
		void computeBestQualities(float threshold);

		/*Compute best quality*/
		void computeBestQuality(Quality *bestQuality);

		/*Fill quality vector TODO params*/
		void fillQuality(int i, Quality *bestQuality);

		/*Add best qualities*/
		void addBestQualities(float parameter1, float parameter2, Quality *bestQuality1, Quality *bestQuality2, float threshold);

		/*Deallocate quality list*/
		void deleteQualitiesD();

		/*Deallocate parameters list*/
		void deleteParameters();
	public:

		/*Constructor*/
		LPAggreg();

		/*Destructor*/
		virtual ~LPAggreg();
		int getSize() const;
		void init(bool normalization);
		vector<int> getParts(float parameter);
		vector<float> getParameters(float threshold);
		const vector<Quality*>& getQualities() const {
			return qualitiesD;
		}
		time_t getQualityDuration();
		time_t getBestCutDuration();
		time_t getBestPartitionDuration();
};

#endif /* LPAGGREG_H_ */
