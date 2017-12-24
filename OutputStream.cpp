//
//  OutputStream.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "OutputStream.hpp"
#include "Stream.hpp"
#define MAX_ITEMS 100

class OutputStream: public Stream {
    
    void write1(int32_t);
    void write2(int32_t);
    void write3(int32_t);
    void write4(int32_t);

public:
    // constructor
    OutputStream();
    OutputStream(int B);
    
    // required functions
    void create(std::string);
    void write(int32_t);
};

// constructor
OutputStream::OutputStream(){
}

OutputStream::OutputStream(int B){
    OutputStream();
    this->B = B;
    this->current_read = 0;
}

// required functions
void OutputStream::create(std::string file_name) {
    std::cout << "creating file withe file name : " << file_name << std::endl;
    switch (this->getUsedMethod()) {
        case 1:
            this->fd = ::open(file_name.c_str(), O_WRONLY | O_CREAT);
            std::cout << "obtained FD" << this->fd << std::endl;
            break;
            
        case 2:
            this->pFile = fopen(file_name.c_str(), "wb");
            break;
        
        case 3:
            this->fd = ::open(file_name.c_str(), O_WRONLY | O_CREAT);
            std::cout << "obtained FD" << this->fd << std::endl;
            break;
    }
}

void OutputStream::write1(int32_t value) {
    std::cout << "write (1): " << value << std::endl;
    ::write(this->getFD(), &value, sizeof(value));
}

void OutputStream::write2(int32_t value) {
    std::cout << "write (2): " << value << std::endl;
    fwrite(&value, sizeof(value), 1, this->getPFile());
}

void OutputStream::write3(int32_t value) {
    // execute buffered write
    this->getBuffer()[this->getCurrentRead()] = value;
    std::cout << "write (3): " << this->getBuffer()[this->getCurrentRead()] << std::endl;;
    this->increaseRead();
    
    if(this->getCurrentRead() == this->getB()){
        // write new buffer
        std::cout << "writing buffer to file" << std::endl;
        int32_t res;
        ::write(this->getFD(), (void*)this->getBuffer(), this->getB()*sizeof(res));
        this->current_read = 0;
    }
}

void OutputStream::write4(int32_t value) {
}

void OutputStream::write(int32_t value) {
    switch (this->getUsedMethod()) {
        case 1:
            std::cout << "method 1 chosen .. " << std::endl;
            this->write1(value);
            break;
        case 2:
            std::cout << "method 2 chosen .. " << std::endl;
            this->write2(value);
            break;
        case 3:
            this->write3(value);
            break;
        case 4:
            this->write4(value);
            break;
    }
}

