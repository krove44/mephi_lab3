#pragma once
#include <string>

class FuncListException : public std::exception {
private:
    std::string message_;
public:
    explicit FuncListException(const std::string& message) : message_(message) {}
    
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

class FuncListEmpthy : public FuncListException {
public:
    explicit FuncListEmpthy()
        : FuncListException("FuncList is Empthy") {}
};