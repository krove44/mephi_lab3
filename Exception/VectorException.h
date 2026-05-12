#pragma once
#include <string>
#include <format>

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
        : VectorException(std::format("Vector size mismatch: {} != {}", a, b)) {}
};
