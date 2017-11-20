//
//  OutputStream.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "OutputStream.hpp"
#include <cstdint>

class OutputStream {
    int _used_method;
    
    void _write1(uint32_t);
    void _write2(uint32_t);
    void _write3(uint32_t);
    void _write4(uint32_t);

public:
    // getters
    int getUsedMethod();
    
    // setters
    void setUsedMethod(int);
    
    // required functions
    void create(std::string);
    void write(uint32_t);
    void close();
};
// getters
int OutputStream::getUsedMethod() {
    return _used_method;
}

// setters
void OutputStream::setUsedMethod(int new_method) {
    this->_used_method = (new_method % 4) + 1;
}

// required functions
void OutputStream::create(std::string file_name) {
    std::cout << "creating file withe file name : " << file_name << std::endl;
}

void OutputStream::_write1(uint32_t value) {
}

void OutputStream::_write2(uint32_t value) {
}

void OutputStream::_write3(uint32_t value) {
}

void OutputStream::_write4(uint32_t value) {
}

void OutputStream::write(uint32_t value) {
    std::cout << "writing value " << value << " to the stream" << std::endl;
    
    switch (this->getUsedMethod()) {
        case 1:
            this->_write1(value);
            break;
        case 2:
            this->_write2(value);
            break;
        case 3:
            this->_write3(value);
            break;
        case 4:
            this->_write4(value);
            break;
    }
}

void OutputStream::close() {
    std::cout << "closing stream" << std::endl;
}

