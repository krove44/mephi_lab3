#pragma once
#include <cstddef>
#include "Exception/OptionalException.h"


template<typename T>
class Optional {
private:
    union {
        T value_;
        std::byte dummy_;
    };
    bool hasValue_;
public:
    Optional() : dummy_(), hasValue_(false){}
    Optional(const T& value) : hasValue_(true){
        new (&value_) T(value);
    };
    Optional(Optional&& other) : dummy_(), hasValue_(other.hasValue_) {
        if (hasValue_) {
            new (&value_) T(std::move(other.value_));
            other.value_.~T();
            other.hasValue_ = false;
        }
    }
    ~Optional() {
        if (hasValue_) {
            value_.~T();
        }
    };

    bool has_value() {
        return hasValue_;
    }

    T value() {
        if (!hasValue_) {
            throw OptionalEmpthy("Optional: значения нет!");
        }
        return value_;
    }

    T* operator->() { 
        return &value_;
    }

};
