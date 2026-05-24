#pragma once
#include <string>
#include <format>

class MatrixException : public std::exception {
private:
    std::string message_;
public:
    explicit MatrixException(const std::string& message) : message_(message) {}
    
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

class SizeMismatchException : public MatrixException {
public:
    SizeMismatchException(size_t a, size_t b) 
        : MatrixException(std::format("Matrix size mismatch: {} != {}", a, b)) {}
};
