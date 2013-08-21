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
#include "Eval.h"
#include "Complexity.h"

using namespace std;


template <typename Value>
class LPAggreg{
	private:

		/*Number of vector of scalar of input matrix*/
		typedef Value values;
		int size;

		/*Matrix that contains quality measures for each aggregate*/
		vector< vector<Quality*> > qualities;

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

		Eval eval;

	private:
		/*This method has to be overridden. It computes quality matrix.
		 * bool normalization: if true, quality measures are normalized
		 */

		void computeQualities(bool normalization, vector<double> values);
		void computeQualities(bool normalization, vector< vector<double> > values);
		void computeQualities(bool normalization, vector< vector < vector<double> > > values);

		int getSize(vector<double> values);
		int getSize(vector< vector <double> > values);
		int getSize(vector< vector < vector<double> > > values);

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
		void deleteQualityList();

		/*Deallocate parameters list*/
		void deleteParameters();

	public:

		/*Constructor*/
		LPAggreg();
		LPAggreg(Value values);
		/*Destructor*/
		virtual ~LPAggreg();
		void setValues(const Value& values);
		int getSize() const;
		void computeQualities(bool normalization);
		vector<int> getParts(float parameter);
		vector<float> getParameters(float threshold);
		const vector<Quality*>& getQualityList() const;
		int getQualityDuration(); //ms
		int getBestCutDuration(); //ms
		int getBestPartitionDuration(); //ms
		int getQualityCount();
		int getBestCutCount();
		int getBestPartitionCount();
};

#endif /* LPAGGREG_H_ */
