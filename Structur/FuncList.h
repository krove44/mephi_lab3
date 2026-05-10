#pragma once
#include <cstddef>
#include <memory>
#include <iostream>
#include "../Exception/FuncListException.h"

template<typename T>
class FuncList {
private:
    struct Node {
        T head;
        std::shared_ptr<Node> tail;
        Node(T val, std::shared_ptr<Node> next) : head(val), tail(next) {}
    };

    std::shared_ptr<Node> root_;
    size_t size_;

    FuncList(std::shared_ptr<Node> root, size_t size) : root_(root), size_(size) {}

public:
    FuncList() : root_(nullptr), size_(0) {}

    FuncList prepend(T value) const {
        return FuncList(std::make_shared<Node>(value, root_), size_ + 1);
    }

    T head() const {
        if(root_ == nullptr){
            throw FuncListEmpthy();
        }
        return root_->head;
    }

    FuncList tail() const {
        if(root_ == nullptr){
            throw FuncListEmpthy();
        }
        return FuncList(root_->tail, size_ - 1);
    }

    bool empty() const {
        return root_ == nullptr;
    }

    size_t size() const {
        return size_;
    }

    FuncList concat(const FuncList& other) const {
        if (empty()) {
            return other;
        };
        return tail().concat(other).prepend(head());
    }

    template<typename F>
    FuncList map(F func) const {
        if (empty()) return FuncList();
        return tail().map(func).prepend(func(head()));
    }

    template<typename F>
    FuncList where(F func) const {
        if (empty()) return FuncList();
        FuncList res = tail().where(func);
        if (func(head())) return res.prepend(head());
        return res;
    }

    template<typename F>
    T reduce(F func, T start) const {
        if (empty()) return start;
        return tail().reduce(func, func(head(), start));
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const FuncList<T>& list) {
    os << "[";
    FuncList<T> cur = list;
    while (!cur.empty()) {
        os << cur.head();
        cur = cur.tail();
        if (!cur.empty()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}