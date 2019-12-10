// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <map>
#include <stdint.h>

using std::int64_t;
using std::atomic_size_t;
using std::map;

template <typename T>

class SharedPtr {
public:
    SharedPtr();
    explicit SharedPtr(T* ptr);
    explicit SharedPtr(const SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    ~SharedPtr();
    auto operator=(const SharedPtr& r) -> SharedPtr&;
    auto operator=(SharedPtr&& r) -> SharedPtr&;

    // проверяет, указывает ли указатель на объект
    explicit operator bool() const;

    auto operator*() const -> T&;
    auto operator->() const -> T*;
    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void p_swap(SharedPtr& r);

    auto use_count() const -> size_t;

    T* p_obj;

    static map<int64_t , size_t> ptr_map;
};

#endif // INCLUDE_HEADER_HPP_
