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

#ifndef LPVALUES_H_
#define LPVALUES_H_

#include <vector>

using namespace std;

template<int Dimension, typename Type>
class LPValues {
	public:
		LPValues();
		virtual ~LPValues();
};

template<typename Type>
class LPValues<0, Type> {
	private:
		Type value;
	public:
		LPValues();
		LPValues(Type value);
		virtual ~LPValues();
		Type getValues() const;
		void setValue(Type value);
};

template<typename Type>
class LPValues<1, Type> {
	private:
		vector<Type> values;
	public:
		LPValues();
		vector<Type> getValues() const;
		void setValue(int i, Type value);
		void push_back(Type value);
		virtual ~LPValues();
};

template<typename Type>
class LPValues<2, Type> {
	private:
		vector<vector<Type> > values;
	public:
		LPValues();
		vector<vector<Type> > getValues() const;
		void setValue(int i, int j, Type value);
		void addVector();
		void push_back(int i, Type value);
		void push_back(Type value);
		virtual ~LPValues();
};

template<typename Type>
class LPValues<3, Type> {
	private:
		vector<vector<vector<Type> > > values;
	public:
		LPValues();
		vector<vector<vector<Type> > > getValues() const;
		void setValue(int i, int j, int k, Type value);
		void addMatrix();
		void addVector();
		void addVector(int i);
		void push_back(int i, int j, Type value);
		void push_back(Type value);
		virtual ~LPValues();
};

template<int Dimension, typename Type>
LPValues<Dimension, Type>::LPValues() {
	// TODO Auto-generated constructor stub
	
}

template<int Dimension, typename Type>
LPValues<Dimension, Type>::~LPValues() {
	// TODO Auto-generated destructor stub
}

template<typename Type>
LPValues<0, Type>::LPValues() :
		value(0) {
}

template<typename Type>
LPValues<0, Type>::LPValues(Type value) {
	this->value(value);
}

template<typename Type>
Type LPValues<0, Type>::getValues() const {
	return value;
}

template<typename Type>
void LPValues<0, Type>::setValue(Type value) {
	this->value = value;
}

template<typename Type>
LPValues<1, Type>::LPValues() {
	this->values = vector<Type>();
}

template<typename Type>
vector<Type> LPValues<1, Type>::getValues() const {
	return this->values;
}

template<typename Type>
void LPValues<1, Type>::setValue(int i, Type value) {
	this->values[i] = value;
}

template<typename Type>
void LPValues<1, Type>::push_back(Type value) {
	this->values.push_back(value);
}

template<typename Type>
LPValues<1, Type>::~LPValues() {
}

template<typename Type>
LPValues<2, Type>::LPValues() {
	this->values = vector<vector<Type> >();
}

template<typename Type>
vector<vector<Type> > LPValues<2, Type>::getValues() const {
	return this->values;
}

template<typename Type>
void LPValues<2, Type>::setValue(int i, int j, Type value) {
	values[i][j] = value;
}

template<typename Type>
void LPValues<2, Type>::addVector() {
	this->values.push_back(vector<Type>());
}

template<typename Type>
void LPValues<2, Type>::push_back(int i, Type value) {
	this->values[i].push_back(value);
}

template<typename Type>
void LPValues<2, Type>::push_back(Type value) {
	this->values[this->values.size() - 1].push_back(value);
}

template<typename Type>
LPValues<2, Type>::~LPValues() {
}

template<typename Type>
LPValues<3, Type>::LPValues() {
	this->values = vector<vector<vector<Type> > >();
}

template<typename Type>
vector<vector<vector<Type> > > LPValues<3, Type>::getValues() const {
	return this->values;
}

template<typename Type>
void LPValues<3, Type>::setValue(int i, int j, int k, Type value) {
	this->values[i][j][k] = value;
}

template<typename Type>
void LPValues<3, Type>::addMatrix() {
	this->values.push_back(vector<vector<Type> >());
}

template<typename Type>
void LPValues<3, Type>::addVector() {
	this->values[this->values.size() - 1].push_back(vector<Type>());
}

template<typename Type>
void LPValues<3, Type>::addVector(int i) {
	this->values[i].push_back(vector<Type>());
}

template<typename Type>
void LPValues<3, Type>::push_back(int i, int j, Type value) {
	this->values[i][j].push_back(value);
}

template<typename Type>
void LPValues<3, Type>::push_back(Type value) {
	unsigned indexi = this->values.size() - 1;
	unsigned indexj = this->values[indexi].size() - 1;
	this->values[indexi][indexj].push_back(value);
}

template<typename Type>
LPValues<3, Type>::~LPValues() {
}

#endif /* LPVALUES_H_ */

