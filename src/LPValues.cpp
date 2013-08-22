/*
 * LPValues.cpp
 *
 *  Created on: 22 août 2013
 *      Author: dosimont
 */

#include "LPValues.h"

template<int Dimension, typename Type>
LPValues<Dimension, Type>::LPValues() {
	// TODO Auto-generated constructor stub
	
}

template<int Dimension, typename Type>
LPValues<Dimension, Type>::~LPValues() {
	// TODO Auto-generated destructor stub
}

template<typename Type>
LPValues<0, Type>::LPValues(): value(0)
{
}

template<typename Type>
LPValues<0, Type>::LPValues(Type value)
{
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
LPValues<1, Type>::LPValues()
{
	this->values=vector<Type>();
}

template<typename Type>
vector<Type> LPValues<1, Type>::getValues() const
{
	return this->values;
}

template<typename Type>
void LPValues<1, Type>::setValue(int i, Type value)
{
	this->values[i]=value;
}

template<typename Type>
void LPValues<1, Type>::push_back(Type value)
{
	this->values.push_back(value);
}

template<typename Type>
LPValues<1, Type>::~LPValues()
{
}

template<typename Type>
LPValues<2, Type>::LPValues()
{
	this->values=vector< vector<Type> >();
}

template<typename Type>
vector< vector<Type> > LPValues<2, Type>::getValues() const
{
	return this->values;
}

template<typename Type>
void LPValues<2, Type>::setValue(int i, int j, Type value)
{
	values[i][j]=value;
}

template<typename Type>
void LPValues<2, Type>::addVector()
{
	this->values.push_back(vector<Type>());
}

template<typename Type>
void LPValues<2, Type>::push_back(int i, Type value)
{
	this->values[i].push_back(value);
}

template<typename Type>
void LPValues<2, Type>::push_back(Type value)
{
	this->values[this->values.size()-1].push_back(value);
}

template<typename Type>
LPValues<2, Type>::~LPValues()
{
}

template<typename Type>
LPValues<3, Type>::LPValues()
{
	this->values=vector< vector<Type> >();
}

template<typename Type>
vector<vector<vector<Type> > > LPValues<3, Type>::getValues() const
{
}

template<typename Type>
void LPValues<3, Type>::setValue(int i, int j, int k, Type value)
{
}

template<typename Type>
inline void LPValues<3, Type><Type>::addMatrix()
{
}

template<typename Type>
inline void LPValues<3, Type><Type>::addVector()
{
}

template<typename Type>
inline void LPValues<3, Type><Type>::addVector(int i)
{
}

template<typename Type>
inline void LPValues<3, Type><Type>::push_back(int i, int j, Type value)
{
}

template<typename Type>
inline void LPValues<3, Type><Type>::push_back(Type value)
{
}

template<typename Type>
inline LPValues<3, Type><Type>::~LPValues()
{
}

