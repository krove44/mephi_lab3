#pragma once
#include <cstddef>
#include <concepts>
#include <utility>
#include "../Exception/VectorException.h"
#include <cmath>

template<typename T>
concept number = requires (T t) {
    {t + t} -> std::same_as<T>;
    {t - t} -> std::same_as<T>;
    {t * t} -> std::same_as<T>;
};

template<typename Container>
concept vectorizable = requires (Container c, size_t idx) {
    {c[idx]};//-> c::value_type;
    {c.GetLenght()} -> std::convertible_to<size_t>;
    {c.begin()};
    {c.end()};

};

template <template <typename> class Container, number T>
requires vectorizable<Container<T>>
class Vec {
private:
    Container<T> data_;
public:
    Vec() : data_(2) {
        data_.Append(T{});
        data_.Append(T{});
    };
    explicit Vec(const Container<T>& c) : data_(c) {};
    Vec(size_t size) : data_(size){};

    Vec operator+(const Vec& other) const {
        if (data_.GetLenght() != other.data_.GetLenght()) {
            throw SizeMismatchException(data_.GetLenght(), other.data_.GetLenght());
        }
        auto pairs = zip(data_, other.data_);
        auto sums = map(pairs, [](std::pair<T,T> p) {
            return p.first + p.second;
        });
        return Vec(sums);
    }

    Vec operator-(const Vec& other) const {
        if (data_.GetLenght() != other.data_.GetLenght()) {
            throw SizeMismatchException(data_.GetLenght(), other.data_.GetLenght());
        }
        auto pairs = zip(data_, other.data_);
        auto sums = map(pairs, [](std::pair<T,T> p) {
            return p.first - p.second;
        });
        return Vec(sums);
    }

    size_t GetLenght() const {
        return data_.GetLenght();
    }

    T& operator[](size_t index){
        return data_[index];
    };
    
    const T& operator[](size_t index) const {
        return data_[index];
    };

    Vec operator*(const T& scalar) const {
        Vec new_vec(*this);
        for(size_t i = 0; i < new_vec.GetLenght(); i++) {
            new_vec[i]*= scalar;
        };
        return new_vec;
    };

    friend Vec operator*(T scalar, const Vec& v) {
        return v * scalar;
    }

    T dot(const Vec& other) const {
        if (data_.GetLenght() != other.data_.GetLenght()) {
            throw SizeMismatchException(data_.GetLenght(), other.data_.GetLenght());
        }
        T result = {};
        for (size_t i = 0; i < data_.GetLenght(); ++i) {
            result += data_[i] * other.data_[i];
        }
        return result;
    };

    double norm() const {
        return std::sqrt(static_cast<double>(dot(*this)));
    }  

    Container<std::pair<T,T>> zip(const Container<T>& a, const Container<T>& b) const {
        if (a.GetLenght() != b.GetLenght()) {
            throw SizeMismatchException(a.GetLenght(), b.GetLenght());
        }

        Container<std::pair<T,T>> result;
        for (size_t i = 0; i < a.GetLenght(); ++i) {
            result.Append({a.Get(i), b.Get(i)});
        }
        return result;
    };

    template<typename F>
    auto map(const Container<std::pair<T,T>>& seq, F func) const {
        Container<T> result;
        for (size_t i = 0; i < seq.GetLenght(); ++i) {
            result.Append(func(seq.Get(i)));
        }
        return result;
    }

};


