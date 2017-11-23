//
//  InputStream.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "InputStream.hpp"

class InputStream {
    std::list<int32_t> stream;
    std::string _file;
    int _fd;
    bool _EOS;
    bool _stop;
    
    int _used_method;
    
    // private getters
    int _getFD();
    bool _getStopSignal();
    
    // private setters
    void _flagStart();
    void _flagStop();
    
    // private reads
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
    void open(std::string);
    void read_next();
    bool end_of_stream();
};

// constructors
InputStream::InputStream() {
    this->setOpenFile("none");
    this->_EOS = false;
    this->_stop = false;
    this->_used_method = 1;
}

// private getters
int InputStream::_getFD() {
    return _fd;
}

bool InputStream::_getStopSignal() {
    return _stop;
}

// getters
std::string InputStream::getOpenFile() {
    return this->_file;
}

int InputStream::getUsedMethod() {
    return this->_used_method;
}

// private setters
void InputStream::_flagStart() {
    _stop = false;
}

void InputStream::_flagStop() {
    _stop = true;
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
void InputStream::open(std::string file_to_open) {
    std::cout << "opening file : " << file_to_open << std::endl;
    this->_file = file_to_open;
    this->_fd = ::open(file_to_open.c_str(), O_RDONLY);
    std::cout << "obtained FD : " << _getFD() << std::endl;
}

void InputStream::_read1() {
    /*
     read using unistd read function
     */

    char read_ch;
    std::string buffered;
    
    if (ch) {
        buffered += read_ch;
    }
    
    while(read(_getFD(), &read_ch, 1) > -1 and !_getStopSignal()) {
        if(read_ch == '\n'){
            _flagStop();
        }
        else {
            buffered += read_ch;
        }
    }
    
    std::cout << "read method 1 : " << buffered << std::endl;
}

void InputStream::_read2() {
    /*
     read using stdio fread function
     */
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
    _flagStart();
    
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
