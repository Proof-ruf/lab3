// Copyright 2018 Your Name <your_email>

#include <header.hpp>

template<typename T>
SharedPtr<T>::SharedPtr() {
    p_obj = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr(T *ptr) {
    p_obj = ptr;
    ptr_map[static_cast<long long>(p_obj)]++;
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &r) {
    p_obj = r.p_obj;
    ptr_map[static_cast<long long>(p_obj)]++;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr &&r) {
    p_obj = r.p_obj;
    ptr_map[static_cast<long long>(p_obj)]++;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    ptr_map[static_cast<long long>(p_obj)]--;
    if (ptr_map[static_cast<long long>(p_obj)] == 0) {
        ptr_map.erase(static_cast<long long>(p_obj));
        delete p_obj;
    }
}

template<typename T>
auto SharedPtr<T>::operator=(const SharedPtr &r) -> SharedPtr & {
    if (p_obj != r.p_obj) {
        reset(r.p_obj);
    }
    return *this;
}

template<typename T>
auto SharedPtr<T>::operator=(SharedPtr &&r) -> SharedPtr & {
    if (p_obj != r.p_obj) {
        reset(r.p_obj);
    }
    return *this;
}

// проверяет, указывает ли указатель на объект
template<typename T>
SharedPtr<T>::operator bool() const {
    if (!p_obj) {
        return false;
    } else {
        return true;
    }
}

template<typename T>
auto SharedPtr<T>::operator*() const -> T & {
    return *p_obj;
}

template<typename T>
auto SharedPtr<T>::operator->() const -> T * {
    return p_obj;
}

template<typename T>
auto SharedPtr<T>::get() -> T * {
    return *p_obj;
}

template<typename T>
void SharedPtr<T>::reset() {
    ~SharedPtr();
    this->SharedPtr();
}

template<typename T>
void SharedPtr<T>::reset(T *ptr) {
    ~SharedPtr();
    this->SharedPtr(ptr);
}

template<typename T>
void SharedPtr<T>::swap(SharedPtr &r) {
    T *tmp = p_obj;
    p_obj = r.p_obj;
    r.p_obj = tmp;
}

// возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
template<typename T>
auto SharedPtr<T>::use_count() const -> size_t {
    return ptr_map[static_cast<long long>(p_obj)];
}
