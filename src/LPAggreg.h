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
#include "ILPAggreg.h"

using namespace std;


template <typename Value>
class LPAggreg: public ILPAggreg{
	protected:

		Value values;

	private:

		void computeQualitiesSpe(bool normalization);

	public:

		/*Constructor*/
		LPAggreg();
		LPAggreg(Value values);
		/*Destructor*/
		virtual ~LPAggreg();
		void setValues(const Value& values);
		unsigned int getSize();
};

//template<>
//class LPAggreg< vector<double> >: public ILPAggreg{
//	protected:
//
//		/*Number of vector of scalar of input matrix*/
//		vector<double> values;
//
//	private:
//
//		void computeQualitiesSpe(bool normalization);
//
//	public:
//
//		/*Constructor*/
//		LPAggreg();
//		LPAggreg(vector<double> values);
//		/*Destructor*/
//		virtual ~LPAggreg();
//		void setValues(const vector<double>& values);
//		int getSize();
//};
//
//template<>
//class LPAggreg< vector< vector<double> > >: public ILPAggreg{
//	protected:
//
//		/*Number of vector of scalar of input matrix*/
//		vector <vector<double> > values;
//
//	private:
//
//		void computeQualitiesSpe(bool normalization);
//
//	public:
//
//		/*Constructor*/
//		LPAggreg();
//		LPAggreg(vector <vector<double> > values);
//		/*Destructor*/
//		virtual ~LPAggreg();
//		void setValues(const vector <vector<double> >& values);
//		int getSize();
//};
//
//template<>
//class LPAggreg< vector <vector< vector<double> > > >: public ILPAggreg{
//	protected:
//
//		/*Number of vector of scalar of input matrix*/
//		vector <vector <vector<double> > > values;
//
//	private:
//
//		void computeQualitiesSpe(bool normalization);
//
//	public:
//
//		/*Constructor*/
//		LPAggreg();
//		LPAggreg(vector <vector <vector<double> > > values);
//		/*Destructor*/
//		virtual ~LPAggreg();
//		void setValues(const vector <vector <vector<double> > >& values);
//		int getSize();
//};



//template<>
//LPAggreg< vector<double> >::LPAggreg()
//{
//	ILPAggreg();
//}

//template<>
//LPAggreg< vector<double> >::LPAggreg(vector<double> values): values(values)
//{
//	ILPAggreg();
//}
//
//template<>
//LPAggreg< vector<double> >::~LPAggreg()
//{
//}
//
//template<>
//void LPAggreg< vector<double> >::setValues(const vector<double>& values)
//{
//	this->values=values;
//}
//
//template<>
//int LPAggreg< vector<double> >::getSize()
//{
//	return this->values.size();
//}
//
//template<>
//LPAggreg< vector< vector<double> > >::LPAggreg()
//{
//	ILPAggreg();
//}
//
//template<>
//LPAggreg< vector< vector<double> > >::LPAggreg(vector<vector<double> > values): values(values)
//{
//	ILPAggreg();
//}
//
//template<>
//LPAggreg< vector< vector<double> > >::~LPAggreg()
//{
//}
//
//template<>
//void LPAggreg< vector< vector<double> > >::setValues(const vector<vector<double> >& values)
//{
//	this->values=values;
//}
//
//template<>
//int LPAggreg< vector< vector<double> > >::getSize()
//{
//	return this->values.size();
//}
//
//template<>
//LPAggreg< vector <vector< vector<double> > > >::LPAggreg(): values(values)
//{
//	ILPAggreg();
//}
//
//template<>
//LPAggreg< vector <vector< vector<double> > > >::LPAggreg(vector<vector<vector<double> > > values): values(values)
//{
//	ILPAggreg();
//}
//
//template<>
//LPAggreg< vector <vector< vector<double> > > >::~LPAggreg()
//{
//}
//
//template<>
//void LPAggreg< vector <vector< vector<double> > > >::setValues(const vector<vector<vector<double> > >& values)
//{
//	this->values=values;
//}
//
//template<>
//int LPAggreg< vector <vector< vector<double> > > >::getSize()
//{
//	return this->values.size();
//}


#endif /* LPAGGREG_H_ */

#include "LPAggreg.tpp"
