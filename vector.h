#pragma once
#include "submodule/DynamicArray.h"
#include <cstddef>
#include <utility>
#include "Exception.h"
#include "span"


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

        Iterator operator+(int n) {
            Iterator copy(cur + n);
            return copy;
            } 
            
        Iterator operator-(int n) {
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

        bool operator==(const Iterator& other){
            return cur == other.cur;
            };

        bool operator!=(const Iterator& other){
            return cur != other.cur;
            };

        T& operator*() {
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

    Vector() : sp_{}, size_{}{};
    Vector(size_t size) : sp_(size), size_(size){};
    Vector(std::span<const T> data) : sp_(data.size()), size_(data.size()) {
        size_t j = 0;
        for (const T& i : data) {
            sp_[j++] = i;
        }
    };
    Vector(const Vector<T>& other) : sp_(other.sp_), size_(other.size_){};
    Vector(Vector<T>&& other) : sp_(std::move(other.sp_)), size_(std::move(size_)){}; 

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

    T& operator[](size_t index) {
        return sp_[index];
    }
    
    const T& operator[](size_t index) const {
        return sp_[index];
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

};