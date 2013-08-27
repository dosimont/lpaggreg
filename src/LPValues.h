/*
 * LPValues.h
 *
 *  Created on: 22 août 2013
 *      Author: dosimont
 */

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
		vector< vector<Type> > values;
	public:
		LPValues();
		vector< vector<Type> > getValues() const;
		void setValue(int i, int j, Type value);
		void addVector();
		void push_back(int i, Type value);
		void push_back(Type value);
		virtual ~LPValues();
};

template<typename Type>
class LPValues<3, Type> {
	private:
		vector< vector< vector <Type> > >values;
	public:
		LPValues();
		vector< vector< vector<Type> > > getValues() const;
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
	this->values=vector <vector< vector<Type> > >();
}

template<typename Type>
vector<vector<vector<Type> > > LPValues<3, Type>::getValues() const
{
	return this->values;
}

template<typename Type>
void LPValues<3, Type>::setValue(int i, int j, int k, Type value)
{
	this->values[i][j][k]=value;
}

template<typename Type>
void LPValues<3, Type>::addMatrix()
{
	this->values.push_back(vector< vector<Type> >());
}

template<typename Type>
void LPValues<3, Type>::addVector()
{
	this->values[this->values.size()-1].push_back(vector<Type>());
}

template<typename Type>
void LPValues<3, Type>::addVector(int i)
{
	this->values[i].push_back(vector<Type>());
}

template<typename Type>
void LPValues<3, Type>::push_back(int i, int j, Type value)
{
	this->values[i][j].push_back(value);
}

template<typename Type>
void LPValues<3, Type>::push_back(Type value)
{
	unsigned indexi=this->values.size()-1;
	unsigned indexj=this->values[indexi].size()-1;
	this->values[indexi][indexj].push_back(value);
}

template<typename Type>
LPValues<3, Type>::~LPValues()
{
}



#endif /* LPVALUES_H_ */

#include "LPValues.tpp"
