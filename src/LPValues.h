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



#endif /* LPVALUES_H_ */
