//
// Created by Елена Dmitrievna on 13.10.18.
//

#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include <type_traits>
#include <iostream>

template<typename T>
class optional {
public:
    optional() : isExist(false) {};

    optional(T const &other) {
        new(&data) T(other);
        isExist = true;
    }

    optional(optional const &other) : isExist(other.isExist) {
        if (isExist) {
            new(&data) T(*other);
        }
    }

    optional &operator=(optional const &rhs) {
        optional tmp(rhs);
        swap(tmp, *this);
        return *this;
    }

    void clear() {
        if (isExist) {
            reinterpret_cast<T *>(&data)->~T();
        }
        isExist = false;
    }

    explicit operator bool() const {
        return isExist;
    }

    friend void swap(optional &a, optional &b) {
        if (a.isExist || b.isExist) {
            if (!b.isExist) {
                new(reinterpret_cast<T *>(&b.data)) T(*a);
                a.clear();
                b.isExist = true;
            } else if (!a.isExist) {
                swap(b,a);
            } else {
                std::swap(b.data, a.data);
            }
        }
    }

    T &operator*() {
        return *reinterpret_cast<T *>(&data);
    }

    T const &operator*() const {
        return *reinterpret_cast<const T *>(&data);
    }

    T *operator->() {
        return reinterpret_cast<T *>(&data);
    }

    T const *operator->() const {
        return reinterpret_cast<const T *>(&data);
    }

    friend bool operator==(optional const &lhs, optional const &rhs) {
        if (!lhs.isExist && !rhs.isExist) {
            return true;
        }
        return lhs.isExist && rhs.isExist && (*lhs == *rhs);
    }

    friend bool operator<=(optional const &lhs, optional const &rhs) {
        return !(lhs > rhs);
    }

    friend bool operator>=(optional const &lhs, optional const &rhs) {
        return !(lhs < rhs);
    }

    friend bool operator>(optional const &lhs, optional const &rhs) {
        if (!lhs.isExist) {
            return false;
        }
        return !rhs.isExist || (*lhs > *rhs);
    }

    friend bool operator<(optional const &lhs, optional const &rhs) {
        if (lhs == rhs) {
            return false;
        }
        return lhs <= rhs;
    }

    friend bool operator!=(optional const &lhs, optional const &rhs) {
        return !(lhs == rhs);
    }

    ~optional() {
        clear();
    }


private:
    bool isExist;
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data;
};


#endif //OPTIONAL_OPTIONAL_H
