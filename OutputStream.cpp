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
    if(this->getUsedMethod() == 2){
        this->pFile = fopen(file_name.c_str(), "wb");
    }
    else {
        this->fd = ::open(file_name.c_str(), O_RDWR | O_CREAT |O_SYNC, (mode_t)0600);
        std::cout << "obtained FD : " << this->fd << std::endl;
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
    // memory mapping (minimum B : 1024);
    
    // case : init
    if(this->getCurrentRead() == 0 && this->getTotalMappings() == 0){
        int32_t* map = (int32_t*)mmap(0, this->getB()*sizeof(size_t), PROT_WRITE, MAP_SHARED, this->getFD(), 0);
        this->setMappedData(map);
    }
    // case : further
    if(this->getCurrentRead() == this->getB()){
        std::cout << "creating new mapping" << std::endl;
        munmap(this->getMappedData(), this->getB()*sizeof(size_t));
        
        // execute new mapping
        off_t offset= (off_t) this->getTotalMappings() * this->getB() * sizeof(int32_t);
        std::cout << "current offset : " << offset << std::endl;
        int32_t* map = (int32_t*)mmap(0, this->getB()*sizeof(size_t), PROT_WRITE, MAP_SHARED, this->getFD(), offset);
        
        // update data
        this->setMappedData(map);
        this->current_read = 0;
        this->increaseMappings();
    }

    std::cout << "write (4): " << value << std::endl;
    this->getMappedData()[this->getCurrentRead()] = value;
    this->increaseRead();
}

void OutputStream::write(int32_t value) {
    switch (this->getUsedMethod()) {
        case 1:
            this->write1(value);
            break;
        case 2:
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

