#pragma once
#include "../submodule/DynamicArray.h"
#include <cmath>
#include <cstddef>
#include <utility>
#include "../Exception/VectorException.h"
#include "span"
#include <iostream>


template<typename T>
class Vector {
private:
    DynamicArray<T> sp_;
    size_t size_;

class Iterator {
        T* cur;
        friend class Vector<T>;
    public:
        explicit Iterator(T* ptr) : cur(ptr) {};

        Iterator operator+(int n) const {
            Iterator copy(cur + n);
            return copy;
            } 
            
        Iterator operator-(int n) const {
            Iterator copy(cur - n);
            return copy;
            }
        
        Iterator& operator++() {
            ++cur;
            return *this; 
            } 

        Iterator& operator--() {
            --cur;
            return *this;
            } 

        Iterator operator++(int) {
            Iterator old = *this;
            cur++;
            return old;
            } 

        Iterator operator--(int) {
            Iterator old = *this;
            cur--;
            return old;
            }

        bool operator==(const Iterator& other) const {
            return cur == other.cur;
            };

        bool operator!=(const Iterator& other) const {
            return cur != other.cur;
            };

        T& operator*() const {
            return *cur;
        }
    };

public:
    Iterator begin() {
        return Iterator(&sp_[0]);
    }
    Iterator end() {
        return Iterator(&sp_[0] + size_);
    }

    const Iterator begin() const {
        return Iterator(const_cast<T*>(&sp_[0]));
    }
    const Iterator end() const {
        return Iterator(const_cast<T*>(&sp_[0] + size_));
    }

    Vector() : sp_{}, size_{}{};
    Vector(size_t size) : sp_(size), size_(size){};
    Vector(std::span<const T> data) : sp_(data.size()), size_(data.size()) {
        size_t j = 0;
        for (const T& i : data) {
            sp_[j++] = i;
        }
    };
    Vector(const Vector<T>& other) : sp_(other.sp_), size_(other.size_){};
    Vector(Vector<T>&& other) : sp_(std::move(other.sp_)), size_(std::move(other.size_)){}; 

    size_t size() const {
        return size_;
    }
    
    Vector<T>* push_back(T item) {
        if (size_ == sp_.GetSize()){
            sp_.Resize(size_ == 0 ? 1 : 2 * size_);
        }
        sp_[size_] = item;
        size_++;
        return this;
    }

    double norm() {
        double ans{};
        for(T& i : *this) {
            ans += std::abs(i)*std::abs(i);
        }
        return sqrt(ans);
    }

    T dot(const Vector<T>& other){
        if (size_ == other.size_){
            T ans{};
            for (size_t i = 0; i < size_; i++) {
                ans += sp_[i]*other[i];
            }
            return ans;
        }
        throw SizeMismatchException(size_, other.size_);
    };

    T& operator[](size_t index) {
        return sp_[index];
    }
    
    const T& operator[](size_t index) const {
        return sp_[index];
    }

    bool operator==(const Vector<T>& other){
        if (this == &other) {
            return true;
        }
        else if (size_ == other.size_){
            for (size_t i = 0; i < size_; i++) {
                if(sp_[i] != other[i]){
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    Vector<T> operator+(const Vector<T>& other) {
        if (size_ == other.size_){
            Vector<T> new_vector(*this);
            size_t j = 0;
            for(T& i: new_vector) {
                i += other[j++];
            }
            return new_vector;
        }
        throw SizeMismatchException(size_, other.size_);
    };

    Vector<T> operator*(T scalar) {
        Vector<T> new_vector(*this);
        for(T& i : new_vector) {
            i *= scalar;
        }
        return new_vector;
    };

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
    os << "[";
    for (auto i = v.begin(); i != (v.end() - 1); ++i) {
        os << *i << ", ";
    }
    os << *(v.end() - 1);
    os << "]";
    return os;
}