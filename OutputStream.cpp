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
    int _fd;
    
    void _write1(int32_t);
    void _write2(int32_t);
    void _write3(int32_t);
    void _write4(int32_t);
    
    // private getters
    int _getFD();

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

// private getters
int OutputStream::_getFD() {
    return _fd;
}

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
    this->_fd = ::open(file_name.c_str(), O_WRONLY | O_CREAT);
    std::cout << "obtained FD" << this->_fd << std::endl;
}

// classic write in binary file
void OutputStream::_write1(int32_t value) {
    ::write(this->_getFD(), &value, sizeof(value));
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
            std::cout << "method 2 chosen .. " << std::endl;
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
    ::close(this->_getFD());
}

