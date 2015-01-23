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

#ifndef DLPAGGREG1_H_
#define DLPAGGREG1_H_

#include "DLPAggreg.h"
#define DCHILD1 static_cast<DLPAggreg1*>(DCHILD)

class DLPAggreg1: public DLPAggreg {
	private:
		vector<double> values;
		double** sumValue;
		double** microInfo;

	private:
		void computeQualities();

	public:
		DLPAggreg1();
		virtual ~DLPAggreg1();
		DLPAggreg1(int id);
		DLPAggreg1(int id, const vector<double>& values);
		DLPAggreg1(DLPAggreg1* parent, int id, int weight);
		DLPAggreg1(DLPAggreg1* parent, int id, const vector<double>& values);
		void computeQualities(bool normalization);
		const vector<double>& getValues() const;
		void setValues(const vector<double>& values);
		double** getMicroInfo() const;
		double** getSumValue() const;
};

#endif /* DLPAGGREG1_H_ */
