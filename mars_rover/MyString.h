#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <limits>
#include <tuple>

class MyString {
private:
    char* ptr;         
    size_t size_;      
    size_t capacity_;  

public:
    MyString();
    MyString(const char* cstr);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);

    void clear();
    void resize(size_t n);
    bool empty() const;
    const char& front() const;
    const char& at(size_t pos) const;
    size_t find(const MyString& str, size_t pos = 0) const;
    size_t size() const;
    size_t capacity() const;
    size_t length() const;

    const char* data() const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);

    MyString& operator+=(const MyString& other);

};

#endif // MYSTRING_H
