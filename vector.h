#pragma once
#include "submodule/DynamicArray.h"


template<typename T>
class Vector : public DynamicArray {
private:
    DynamicArray<T> sp_;
    size_t size_;
public:

    Vector() : sp_{}, size_{};


    Vector(size_t size




};