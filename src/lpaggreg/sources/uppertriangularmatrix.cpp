#include "uppertriangularmatrix.h"

template<typename T>
lpaggreg::UpperTriangularMatrix<T>::UpperTriangularMatrix()
{

}

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

template<typename T>
lpaggreg::UpperTriangularMatrix<double>::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){matrix=vector<T>(elements, 0);}

template<typename T>
lpaggreg::UpperTriangularMatrix<lpaggreg::Quality<lp_quality_type>>::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){matrix=vector<T>(elements, Quality<lp_quality_type>());}
