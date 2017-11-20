//
//  InputStream.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "InputStream.hpp"

class InputStream {
    std::list<uint32_t> list;
    std::string _file;
    bool _EOS;
    
public:
    // constructors
    InputStream();
    
    // getters
    std::string getOpenFile();
    
    // setters
    void setOpenFile(std::string);
    void reachedEOS();
    
    // required functions
    void open();
    int read_next();
    bool end_of_stream();
};

// constructors
InputStream::InputStream() {
    this->setOpenFile("none");
    this->_EOS = false;
}

// getters
std::string InputStream::getOpenFile() {
    return this->_file;
}

// setters
void InputStream::setOpenFile(std::string open_file) {
    this->_file = open_file;
}

void InputStream::reachedEOS() {
    this->_EOS = true;
}

// required functions
void InputStream::open() {
    std::cout << "opening file" << std::endl;
}

int InputStream::read_next() {
    std::cout << "reading next 32-bit" << std::endl;
    return 0;
}

bool InputStream::end_of_stream() {
    std::cout << "reached end of file ?" << std::endl;
    return false;
}
