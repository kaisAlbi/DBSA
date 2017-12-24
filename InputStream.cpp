//
//  InputStream.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "InputStream.hpp"
#include "Stream.cpp"
#define MAX_ITEMS 100

class InputStream: public Stream {    
    bool EOS;
    
    // private getters
    bool getStopSignal();
    
    // private reads
    void read1();
    void read2();
    void read3();
    void read4();
    
public:
    // constructors
    InputStream();
    InputStream(int B);
    
    // setters
    void reachedEOS();
    
    // required functions
    void open(std::string);
    void read_next();
    bool end_of_stream();
};

// constructors
InputStream::InputStream() {
    this->EOS = false;
}

InputStream::InputStream(int B) {
    InputStream();
    this->B = B;
    this->current_read = B;
}

// setters
void InputStream::reachedEOS() {
    this->EOS = true;
}

// required functions (DUPLICATED CODE on 1 & 3 DUE TO ERRORS)
void InputStream::open(std::string file_to_open) {
    switch (this->getUsedMethod()) {
        case 1:
            std::cout << "opening file : " << file_to_open << std::endl;
            this->file = file_to_open;
            this->fd = ::open(file_to_open.c_str(), O_RDONLY);
            std::cout << "obtained FD : " << getFD() << std::endl;
            break;
            
        case 2:
            std::cout << "opening with method 2" << std::endl;
            this->pFile = fopen(file_to_open.c_str(), "rb");
            break;
        
        case 3:
            std::cout << "opening file : " << file_to_open << std::endl;
            this->file = file_to_open;
            this->fd = ::open(file_to_open.c_str(), O_RDONLY);
            std::cout << "obtained FD : " << getFD() << std::endl;
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
