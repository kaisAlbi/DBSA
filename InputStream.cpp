//
//  InputStream.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "InputStream.hpp"
#define MAX_ITEMS 100

class InputStream {
    std::list<int32_t> stream;
    std::string _file;
    int _fd;
    FILE* pFile;
    int32_t buffer[MAX_ITEMS];
    bool _EOS;
    bool _stop;
    
    int _used_method;
    int B;
    
    // private getters
    int _getFD();
    bool _getStopSignal();
    FILE* _getPFile();
    int32_t* _getBuffer();
    
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
    InputStream(int B);
    
    // getters
    std::string getOpenFile();
    int getUsedMethod();
    int getB();
    
    // setters
    void setOpenFile(std::string);
    void reachedEOS();
    void setUsedMethod(int);
    
    // required functions
    void open(std::string);
    void read_next();
    bool end_of_stream();
    
    void close();
};

// constructors
InputStream::InputStream() {
    this->setOpenFile("none");
    this->_EOS = false;
    this->_stop = false;
    this->_used_method = 1;
}

InputStream::InputStream(int B) {
    InputStream();
    this->B = B;
}

// private getters
int InputStream::_getFD() {
    return _fd;
}

bool InputStream::_getStopSignal() {
    return _stop;
}

FILE* InputStream::_getPFile() {
    return pFile;
}

int32_t* InputStream::_getBuffer() {
    return buffer;
}

// getters
std::string InputStream::getOpenFile() {
    return this->_file;
}

int InputStream::getUsedMethod() {
    return this->_used_method;
}

int InputStream::getB() {
    return this->B;
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
    if(method_number < 1){
        method_number = 1;
    }
    else if(method_number > 4){
        method_number = 4;
    }
    this->_used_method = method_number;
}

// required functions
void InputStream::open(std::string file_to_open) {
    switch (this->getUsedMethod()) {
        case 1 | 3:
            std::cout << "opening file : " << file_to_open << std::endl;
            this->_file = file_to_open;
            this->_fd = ::open(file_to_open.c_str(), O_RDONLY);
            std::cout << "obtained FD : " << _getFD() << std::endl;
            break;
            
        case 2:
            std::cout << "opening with method 2" << std::endl;
            this->pFile = fopen(file_to_open.c_str(), "rb");
            break;
    }
}

void InputStream::_read1() {
    /*
     read using unistd read function
     */
    int32_t res;
    read(this->_getFD(), &res, sizeof(res));
    std::cout << "read (1): " << res << std::endl;
}

void InputStream::_read2() {
    /*
     read using stdio fread function
     */
    int32_t res;
    size_t status;
    fread(&res, sizeof(res), 1, this->_getPFile());
    std::cout << "read (2): " << res << std::endl;
}

void InputStream::_read3() {
    // read1 + buffer of size B (increase buffer 32 bits to upwards)
    int32_t res;
    read(this->_getFD(), (void*)this->_getBuffer(), this->getB()*sizeof(res));
    std::cout << "read (3): ";
    
    for(int i = 0; i < this->getB(); i++){
        std::cout << this->_getBuffer()[i] << " ";
    }
    std::cout << std::endl;
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

void InputStream::close() {
    ::close(this->_getFD());
}
