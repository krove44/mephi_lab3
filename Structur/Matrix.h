#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include "Vector.h"
#include "..\Exception\MatrixException.h"

template <template <typename> class Container, number T, size_t Dim>
requires vectorizable<Container<T>>
class Matrix {
private:
    Container<Vec<Container, T, Dim>> data_;

public:
    Matrix(const Matrix& other) : data_(other.data_) {};
    //TODO: статический ассерт
    Matrix(std::initializer_list<std::initializer_list<T>> rows) {
        if(rows.size() != Dim){
            throw SizeMismatchException(rows.size(), Dim);
        }

        for (auto& row : rows) {
            if (row.size() != Dim){
                throw SizeMismatchException(rows.size(), Dim);
            }
            data_.Append(Vec<Container, T, Dim>(row));
        }
    }

    Vec<Container, T, Dim>& operator[](size_t row) {
        return data_[row];
    }

    const Vec<Container, T, Dim>& operator[](size_t row) const {
        return data_[row];
    }

    Vec<Container, T, Dim> operator*(const Vec<Container, T, Dim>& v) const {
        Container<T> result;
        for (size_t i = 0; i < Dim; i++) {
            result.Append(data_[i].dot(v));
        }
        return Vec<Container, T, Dim>(result);
    }

    Matrix operator*(const T& scalar) const {
        Matrix new_mat(*this);
        for(size_t i = 0; i < Dim; i++) {
            for (size_t j =0 ; j < Dim; j++){
                new_mat[i][j] *= scalar;
            }
        };
        return new_mat;
    };

    Matrix operator+(const Matrix& other) const {
        Matrix result(*this);
        for (size_t i = 0; i < Dim; i++) {
            for (size_t j = 0; j < Dim; j++) {
                result[i][j] += other[i][j];
            }
        }
        return result;
    }
};