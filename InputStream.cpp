//
//  InputStream.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "InputStream.hpp"

class InputStream {
    std::list<uint32_t> stream;
    std::string _file;
    bool _EOS;
    
    int _used_method;
    
    void _read1();
    void _read2();
    void _read3();
    void _read4();
    
public:
    // constructors
    InputStream();
    
    // getters
    std::string getOpenFile();
    int getUsedMethod();
    
    // setters
    void setOpenFile(std::string);
    void reachedEOS();
    void setUsedMethod(int);
    
    // required functions
    void open();
    void read_next();
    bool end_of_stream();
};

// constructors
InputStream::InputStream() {
    this->setOpenFile("none");
    this->_EOS = false;
    this->_used_method = 1;
}

// getters
std::string InputStream::getOpenFile() {
    return this->_file;
}

int InputStream::getUsedMethod() {
    return this->_used_method;
}

// setters
void InputStream::setOpenFile(std::string open_file) {
    this->_file = open_file;
}

void InputStream::reachedEOS() {
    this->_EOS = true;
}

void InputStream::setUsedMethod(int method_number) {
    this->_used_method = (method_number % 4) + 1;
}

// required functions
void InputStream::open() {
    std::cout << "opening file" << std::endl;
}

void InputStream::_read1() {
    char* buffer;
    int file_descriptor = 0;
    size_t to_count = 32;
    
    // FORM : ssize_t read(int fd, void *buf, size_t count);
    //ssize_t read_bytes = read(file_descriptor, buffer, to_count);
    //std::cout << "buffer : " << buffer << std::endl;
    std::cout << "1 : read !" << std::endl;
}

void InputStream::_read2() {
    char* buffer;
    size_t size = 32;
    size_t to_count = 1;
    FILE* stream;
    
    // FORM : size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
}

void InputStream::_read3() {
    // read1 + buffer of size B (increase buffer 32 bits to upwards)
}

void InputStream::_read4() {
    // memory mapping
}

void InputStream::read_next() {
    std::cout << "reading next 32-bit" << std::endl;
    
    switch (this->getUsedMethod()) {
        case 1:
            this->_read1();
            break;
        case 2:
            this->_read2();
            break;
        case 3:
            this->_read3();
            break;
        case 4:
            this->_read4();
            break;
    }
}

bool InputStream::end_of_stream() {
    return this->_EOS;
}
