#pragma once
#include <cmath>
#include <initializer_list>
#include "Vector.h"

template <template <typename> class Container, number T, size_t Dim>
requires vectorizable<Container<T>>
class Matrix {
private:
    Container<Vec<Container, T, Dim>> data_;

public:
    Matrix(std::initializer_list<std::initializer_list<T>> rows) {
        for (auto& row : rows) {
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
};