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
    
    std::ofstream _outputFile;
    
    void _classicWrite(int32_t);
    void _write1(int32_t);
    void _write2(int32_t);
    void _write3(int32_t);
    void _write4(int32_t);

public:
    // getters
    int getUsedMethod();
    
    // setters
    void setUsedMethod(int);
    
    // required functions
    void create(std::string);
    void write(int32_t);
    void close();
};
// getters
int OutputStream::getUsedMethod() {
    return _used_method;
}

// setters
void OutputStream::setUsedMethod(int new_method) {
    //this->_used_method = (new_method % 4) + 1;
    if(new_method < 1){
        new_method = 1;
    }
    else if(new_method > 4){
        new_method = 4;
    }
    this->_used_method = new_method;
}

// required functions
void OutputStream::create(std::string file_name) {
    std::cout << "creating file withe file name : " << file_name << std::endl;
    _outputFile.open(file_name, std::ios::out | std::ios::binary);
}

// classic write in binary file
void OutputStream::_classicWrite(int32_t value){
    std::cout << "executing classic write .." << std::endl;
	size_t sizeOfInt = sizeof(int32_t); //32 bits
	_outputFile.write(reinterpret_cast<const char *>(&value), 32); 
}

void OutputStream::_write1(int32_t value) {
    this->_classicWrite(value);
}

void OutputStream::_write2(int32_t value) {
}

void OutputStream::_write3(int32_t value) {
}

void OutputStream::_write4(int32_t value) {
}

void OutputStream::write(int32_t value) {
    std::cout << "writing value " << value << " to the stream" << std::endl;
    
    switch (this->getUsedMethod()) {
        case 1:
            std::cout << "method 1 chosen .. " << std::endl;
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

