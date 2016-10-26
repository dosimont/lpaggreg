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

template<typename T>
lpaggreg::UpperTriangularMatrix<T>::UpperTriangularMatrix(unsigned int size, T value):size(size), elements(((size+1)*size/2)){matrix=vector<T>(elements, value);}

template<>
lpaggreg::UpperTriangularMatrix<double>::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){matrix=vector<double>(elements, 0);}

template<>
lpaggreg::UpperTriangularMatrix<int>::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){matrix=vector<int>(elements, 0);}

template<>
lpaggreg::UpperTriangularMatrix<lp_quality_type>::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){matrix=vector<lp_quality_type>(elements, 0);}

template<>
lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality > >::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){
    matrix=vector<shared_ptr<lpaggreg::Quality > >();
    for (int i=0; i<elements; i++){
        matrix.push_back(shared_ptr<lpaggreg::Quality>(new Quality));
    }
}

template<>
lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Tradeoff > >::UpperTriangularMatrix(unsigned int size):size(size), elements(((size+1)*size/2)){
    matrix=vector<shared_ptr<lpaggreg::Tradeoff > >();
    for (int i=0; i<elements; i++){
        matrix.push_back(shared_ptr<lpaggreg::Tradeoff>(new Tradeoff));
    }
}


template<typename T>
T lpaggreg::UpperTriangularMatrix<T>::operator()(unsigned int i, unsigned int j) {
    return matrix[(j-i)*size-(j-i)*((j-i)-1)/2+i];
}


template<typename T>
void lpaggreg::UpperTriangularMatrix<T>::operator()(unsigned int i, unsigned int j, T value)
{
    matrix[(j-i)*size-(j-i)*((j-i)-1)/2+i]=value;
}

template<typename T>
T lpaggreg::UpperTriangularMatrix<T>::operator[](unsigned int i) {return matrix[i];}

template class lpaggreg::UpperTriangularMatrix<double>;

template class lpaggreg::UpperTriangularMatrix<int>;

template class lpaggreg::UpperTriangularMatrix<lp_quality_type>;

template class lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Quality > >;

template class lpaggreg::UpperTriangularMatrix<shared_ptr<lpaggreg::Tradeoff > >;
