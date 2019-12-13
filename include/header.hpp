// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <map>
#include <stdint.h>
#include <iostream>

using std::int64_t;
using std::atomic_size_t;
using std::map;

template <typename T>

class SharedPtr {
public:
    SharedPtr()
    {
        p_obj = nullptr;
    }
    explicit SharedPtr<T>(T* ptr)
    {
        p_obj = ptr;
        ptr_map[reinterpret_cast<int64_t>(p_obj)]++;
    }
    explicit SharedPtr<T>(const SharedPtr& r)
    {
        p_obj = r.p_obj;
        ptr_map[reinterpret_cast<int64_t>(p_obj)]++;
    }
    SharedPtr<T>(SharedPtr&& r)
    {
        p_obj = r.p_obj;
        ptr_map[reinterpret_cast<int64_t>(p_obj)]++;
    }
    ~SharedPtr<T>()
    {
        ptr_map[reinterpret_cast<int64_t>(p_obj)]--;
        if (ptr_map[reinterpret_cast<int64_t>(p_obj)] == 0) {
            ptr_map.erase(reinterpret_cast<int64_t>(p_obj));
            delete p_obj;
        }
    }
    auto operator=(const SharedPtr& r) -> SharedPtr&
    {
        if (p_obj != r.p_obj) {
            reset(r.p_obj);
        }
        return *this;
    }
    auto operator=(SharedPtr&& r) -> SharedPtr&
    {
        if (p_obj != r.p_obj) {
            reset(r.p_obj);
        }
        return *this;
    }

    // проверяет, указывает ли указатель на объект
    explicit operator bool() const
    {
        if (!p_obj) {
            return false;
        } else {
            return true;
        }
    }

    auto operator*() const -> T&
    {
        return *p_obj;
    }
    auto operator->() const -> T*
    {
        return p_obj;
    }
    auto get() -> T*
    {
        return p_obj;
    }
    void reset()
    {
        ptr_map[reinterpret_cast<int64_t>(p_obj)]--;
        if (ptr_map[reinterpret_cast<int64_t>(p_obj)] == 0) {
            ptr_map.erase(reinterpret_cast<int64_t>(p_obj));
            delete p_obj;
        }
        p_obj = nullptr;
    }
    void reset(T* ptr)
    {
        ptr_map[reinterpret_cast<int64_t>(p_obj)]--;
        if (ptr_map[reinterpret_cast<int64_t>(p_obj)] == 0) {
            ptr_map.erase(reinterpret_cast<int64_t>(p_obj));
            delete p_obj;
        }
        p_obj = ptr;
        ptr_map[reinterpret_cast<int64_t>(p_obj)]++;
    }
    void p_swap(SharedPtr& r)
    {
        SharedPtr tmp;
		tmp = *this;
		*this = r;
		r = tmp;
    }

    auto use_count() const -> size_t
    {
        return ptr_map[reinterpret_cast<int64_t>(p_obj)];
    }

    T* p_obj;

    static map<int64_t , atomic_size_t> ptr_map;
};

template <typename T>
map<int64_t, atomic_size_t> SharedPtr<T>::ptr_map{};

#endif // INCLUDE_HEADER_HPP_
