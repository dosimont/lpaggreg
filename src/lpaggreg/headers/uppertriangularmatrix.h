#ifndef UPPERTRIANGULARMATRIX_H
#define UPPERTRIANGULARMATRIX_H

#include <vector>
#include "quality.h"

using namespace std;

namespace lpaggreg{

    template<typename T> class UpperTriangularMatrix
    {
    private:
        int size;
        int elements;
    public:
        UpperTriangularMatrix(unsigned int size);
        vector<double> &operator()(unsigned int i, unsigned int j) const{return matrix[(j-i)*size-(j-i)*((j-i)-1)/2+i];}
        vector<double> operator()(unsigned int i, unsigned int j) {return matrix[(j-i)*size-(j-i)*((j-i)-1)/2+i];}
        vector<double> &operator[](unsigned int i) const{return matrix[i];}
        vector<double> operator[](unsigned int i) {return matrix[i];}
        vector<T> matrix;
        int getElements() const;
        int getSize() const;
};
}

#endif // UPPERTRIANGULARMATRIX_H
