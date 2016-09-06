#ifndef UPPERTRIANGULARMATRIX_H
#define UPPERTRIANGULARMATRIX_H

#include <vector>
#include <memory>
#include "quality.h"
#include "tradeoff.h"

using namespace std;

namespace lpaggreg{

    template<typename T> class UpperTriangularMatrix
    {
    private:
        int size;
        int elements;
    public:
        UpperTriangularMatrix(unsigned int size);
        UpperTriangularMatrix(unsigned int size, T value);
        /*T &operator()(unsigned int i, unsigned int j) const;*/
        T operator()(unsigned int i, unsigned int j);
        void operator()(unsigned int i, unsigned int j, T value);
        /*T &operator[](unsigned int i) const;*/
        T operator[](unsigned int i);
        vector<T> matrix;
        int getElements() const;
        int getSize() const;
    };

    template<>
    UpperTriangularMatrix<double>::UpperTriangularMatrix(unsigned int size);

    template<>
    UpperTriangularMatrix<int>::UpperTriangularMatrix(unsigned int size);

    template<>
    UpperTriangularMatrix<lp_quality_type>::UpperTriangularMatrix(unsigned int size);

    template<>
    UpperTriangularMatrix<shared_ptr<lpaggreg::Quality> >::UpperTriangularMatrix(unsigned int size);

    template<>
    UpperTriangularMatrix<shared_ptr<lpaggreg::Tradeoff> >::UpperTriangularMatrix(unsigned int size);


}

#endif // UPPERTRIANGULARMATRIX_H
