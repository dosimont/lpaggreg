#include "uppertriangularmatrix.h"

template<typename T>
int lpaggreg::UpperTriangularMatrix<T>::getElements() const
{
    return elements;
}

template<typename T>
int lpaggreg::UpperTriangularMatrix<T>::getSize() const
{
    return size;
}

template<typename T>
lpaggreg::UpperTriangularMatrix<T>::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){matrix=vector<T>(elements);}

template<>
lpaggreg::UpperTriangularMatrix<double>::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){matrix=vector<double>(elements, 0);}

template<>
lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality<lp_quality_type> > >::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){matrix=vector<shared_ptr<lpaggreg::Quality<lp_quality_type> > >(elements, shared_ptr<lpaggreg::Quality<lp_quality_type> >(new Quality<lp_quality_type>()));}

template<typename T>
T lpaggreg::UpperTriangularMatrix<T>::operator()(unsigned int i, unsigned int j) {return matrix[(j-i)*size-(j-i)*((j-i)-1)/2+i];}


template<typename T>
void lpaggreg::UpperTriangularMatrix<T>::operator()(unsigned int i, unsigned int j, T value)
{
    matrix[(j-i)*size-(j-i)*((j-i)-1)/2+i]=value;
}

template<typename T>
T lpaggreg::UpperTriangularMatrix<T>::operator[](unsigned int i) {return matrix[i];}

/*template<typename T>
T &lpaggreg::UpperTriangularMatrix<T>::operator[](unsigned int i) const{return matrix[i];}

template<typename T>
T &lpaggreg::UpperTriangularMatrix<T>::operator()(unsigned int i, unsigned int j) const{return matrix[(j-i)*size-(j-i)*((j-i)-1)/2+i];}*/

template class lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality<lp_quality_type> > >;

template class
lpaggreg::UpperTriangularMatrix<double>;
