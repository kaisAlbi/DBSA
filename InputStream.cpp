//
//  InputStream.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "InputStream.hpp"
#define MAX_ITEMS 100

class InputStream {
    int fd;
    FILE* pFile;
    std::string file;
    int32_t buffer[MAX_ITEMS];
    
    bool EOS;
    bool stop;
    
    int B;
    int used_method;
    int current_read;
    
    // private getters
    int getFD();
    bool getStopSignal();
    FILE* getPFile();
    int32_t* getBuffer();
    int getCurrentRead();
    
    // private setters
    void flagStart();
    void flagStop();
    void increaseRead();
    
    // private reads
    void read1();
    void read2();
    void read3();
    void read4();
    
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
    this->EOS = false;
    this->stop = false;
    this->used_method = 1;
}

InputStream::InputStream(int B) {
    InputStream();
    this->B = B;
    this->current_read = B;
}

// private getters
int InputStream::getFD() {
    return fd;
}

bool InputStream::getStopSignal() {
    return stop;
}

FILE* InputStream::getPFile() {
    return pFile;
}

int32_t* InputStream::getBuffer() {
    return buffer;
}

int InputStream::getCurrentRead() {
    return current_read;
}

// getters
std::string InputStream::getOpenFile() {
    return this->file;
}

int InputStream::getUsedMethod() {
    return this->used_method;
}

int InputStream::getB() {
    return this->B;
}

// private setters
void InputStream::flagStart() {
    stop = false;
}

void InputStream::flagStop() {
    stop = true;
}

void InputStream::increaseRead() {
    current_read++;
}

// setters
void InputStream::setOpenFile(std::string open_file) {
    this->file = open_file;
}

void InputStream::reachedEOS() {
    this->EOS = true;
}

void InputStream::setUsedMethod(int method_number) {
    if(method_number < 1){
        method_number = 1;
    }
    else if(method_number > 4){
        method_number = 4;
    }
    this->used_method = method_number;
}

// required functions
void InputStream::open(std::string file_to_open) {
    switch (this->getUsedMethod()) {
        case 1 | 3:
            std::cout << "opening file : " << file_to_open << std::endl;
            this->file = file_to_open;
            this->fd = ::open(file_to_open.c_str(), O_RDONLY);
            std::cout << "obtained FD : " << getFD() << std::endl;
            break;
            
        case 2:
            std::cout << "opening with method 2" << std::endl;
            this->pFile = fopen(file_to_open.c_str(), "rb");
            break;
    }
}

void InputStream::read1() {
    /*
     read using unistd read function
     */
    int32_t res;
    read(this->getFD(), &res, sizeof(res));
    std::cout << "read (1): " << res << std::endl;
}

void InputStream::read2() {
    /*
     read using stdio fread function
     */
    int32_t res;
    size_t status;
    fread(&res, sizeof(res), 1, this->getPFile());
    std::cout << "read (2): " << res << std::endl;
}

void InputStream::read3() {
    /*
     read1 + buffer of size B
     */
    if(this->getCurrentRead() == this->getB()){
        std::cout << "loading new buffer" << std::endl;
        int32_t res;
        read(this->getFD(), (void*)this->getBuffer(), this->getB()*sizeof(res));
        
        this->current_read = 0;
    }
    std::cout << "read (3): " << this->getBuffer()[this->getCurrentRead()];
    this->increaseRead();
    std::cout << std::endl;
}

void InputStream::read4() {
    // memory mapping
}

void InputStream::read_next() {
    flagStart();
    
    switch (this->getUsedMethod()) {
        case 1:
            this->read1();
            break;
        case 2:
            this->read2();
            break;
        case 3:
            this->read3();
            break;
        case 4:
            this->read4();
            break;
    }
}

bool InputStream::end_of_stream() {
    return this->EOS;
}

void InputStream::close() {
    ::close(this->getFD());
}
