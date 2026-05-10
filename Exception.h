#pragma once
#include <stdexcept>
#include <string>

class VectorException : public std::exception {
private:
    std::string message_;
public:
    explicit VectorException(const std::string& message) : message_(message) {}
    
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

class SizeMismatchException : public VectorException {
public:
    SizeMismatchException(size_t a, size_t b) 
        : VectorException("Vector size mismatch: " + 
                          std::to_string(a) + " != " + std::to_string(b)) {}
};

class IndexOutOfRangeException : public VectorException {
public:
    explicit IndexOutOfRangeException(size_t index, size_t size)
        : VectorException("Index " + std::to_string(index) + 
                          " out of range [0, " + std::to_string(size-1) + "]") {}
};