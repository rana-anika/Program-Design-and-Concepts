#include "MyString.h"

MyString::MyString() : ptr(new char[1]), size_(0), capacity_(1) {
    ptr[0] = '\0';
}

MyString::MyString(const char* cstr) {
    size_ = 0;
    while (cstr[size_] != '\0') {
        size_++;
    }
    capacity_ = size_ + 1;
    ptr = new char[capacity_];
    for (size_t i = 0; i < size_; i++) {
        ptr[i] = cstr[i];
    }
    ptr[size_] = '\0';
}

MyString::MyString(const MyString& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    ptr = new char[capacity_];
    for (size_t i = 0; i < size_; i++) {
        ptr[i] = other.ptr[i];
    }
    ptr[size_] = '\0';
}

MyString::~MyString() {
    delete[] ptr;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] ptr;
        size_ = other.size_;
        capacity_ = other.capacity_;
        ptr = new char[capacity_];
        for (size_t i = 0; i < size_; i++) {
            ptr[i] = other.ptr[i];
        }
        ptr[size_] = '\0';
    }
    return *this;
}

void MyString::clear() {
    size_ = 0;
    ptr[0] = '\0';
}

void MyString::resize(size_t n) {
    if (n > capacity_) {
        char* newPtr = new char[n + 1];
        for (size_t i = 0; i < size_; i++) {
            newPtr[i] = ptr[i];
        }
        delete[] ptr;
        ptr = newPtr;
        capacity_ = n + 1;
    }
    size_ = n;
    ptr[size_] = '\0';
}

bool MyString::empty() const {
    return size_ == 0;
}

const char& MyString::front() const {
    if (empty()) {
        throw std::out_of_range("Cannot access front on an empty string");
    }
    return ptr[0];
}

const char& MyString::at(size_t pos) const {
    if (pos >= size_) {
        throw std::out_of_range("Position is out of range");
    }
    return ptr[pos];
}

size_t MyString::find(const MyString& str, size_t pos) const {
    if (pos >= size_) {
        return std::string::npos;
    }
    for (size_t i = pos; i <= size_ - str.size_; i++) {
        bool match = true;
        for (size_t j = 0; j < str.size_; j++) {
            if (ptr[i + j] != str.ptr[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return std::string::npos;
}

size_t MyString::size() const {
    return size_;
}

size_t MyString::capacity() const {
    return capacity_;
}

size_t MyString::length() const {
    return size_;
}

const char* MyString::data() const {
    return ptr;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.ptr;
    return os;
}

MyString& MyString::operator+=(const MyString& other) {
    size_t newSize = size_ + other.size_;
    if (newSize + 1 > capacity_) {
       
        char* newPtr = new char[newSize + 1];
        for (size_t i = 0; i < size_; i++) {
            newPtr[i] = ptr[i];
        }
        delete[] ptr;
        ptr = newPtr;
        capacity_ = newSize + 1;
    }

 
    for (size_t i = 0; i < other.size_; i++) {
        ptr[size_ + i] = other.ptr[i];
    }

    size_ = newSize;
    ptr[size_] = '\0';

    return *this;
}
