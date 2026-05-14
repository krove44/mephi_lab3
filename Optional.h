#pragma once
#include <stdexcept>

template<typename T>
class Optional {
private:
    T    value_;
    bool hasValue_;
public:
    Optional() : hasValue_(false){}
    Optional(T value) : value_(value), hasValue_(true) {}

    bool has_value() {
        return hasValue_;
    }

    T value() {
        if (!hasValue_) {
            throw std::runtime_error("Optional: значения нет!");
        }
        return value_;
    }

    T value_or(T fallback) {
        if (hasValue_) {
            return value_;
        }
        return fallback;
    }

    T* operator->() { 
        if (!hasValue_) {
            throw std::runtime_error("Optional: значения нет!");
        }
        return &value_;
    }

};