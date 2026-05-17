#pragma once
#include <algorithm>
#include <cstddef>
#include <concepts>
#include <initializer_list>
#include <utility>
#include <cmath>
#include <span>
#include <complex.h>


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

template <template <typename> class Container, number T, size_t DIM>
requires vectorizable<Container<T>>
class Vec {
private:
    Container<T> data_;
    constexpr static const size_t dim_ = DIM;
public:
    Vec() {
        for (size_t i = 0; i < DIM; i++) {
            data_.Append(T{});
        }
    };
    Vec(const Container<T>& c) : data_(c) {};
    Vec (Container<T>&& c) : data_(std::move(c)){}
    Vec (std::initializer_list<T> e) : data_{e}{}
    explicit Vec(size_t size) : data_(size){};
    Vec(std::span<const T> data) {
        for (size_t i = 0; i < data.size(); i++) {
            data_.Append(data[i]);
        }
    };


    Vec operator+(const Vec& other) const {
        // auto p = std::views::zip(data_, other.data_) ;
        // for (auto [first, second]: p) {
        //     std::cout << first << second <<  std::endl;
        // }
        // auto p =  std::views::zip(data_, other.data_) | std::ranges::transform([](auto el) {
        //     auto [first, second] = el;
        //     return first + second;
        // });
        // return Vec(p);
        auto pairs = zip(data_, other.data_);
        auto sums = map(pairs, [](std::pair<T,T> p) {
            return p.first + p.second;
        });
        return Vec(sums);
    }

    Vec operator-(const Vec& other) const {
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

    T dot(const Vec& other) const {
        T result = {};
        for (size_t i = 0; i < data_.GetLenght(); ++i) {
            result += data_[i] * other.data_[i];
        }
        return result;
    };

    auto norm() const {
        double result = 0.0;
        for (size_t i = 0; i < data_.GetLenght(); ++i) {
            result += std::abs(data_[i]) * std::abs(data_[i]);
        }
        return std::sqrt(result);
    }  

    Container<std::pair<T,T>> zip(const Container<T>& a, const Container<T>& b) const {
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


