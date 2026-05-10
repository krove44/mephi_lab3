#pragma once
#include <memory>
#include <iostream>

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
        return root_->head;
    }

    FuncList tail() const {
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