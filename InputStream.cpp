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
    int file_end;
    
    // private getters
    bool getStopSignal();
    
    // private setters
    void increaseWrite();
    
    // private reads
    int32_t read1();
    int32_t read2();
    int32_t read3();
    int32_t read4();
    
public:
    // constructors
    InputStream();
    InputStream(int B);
    
    // setters
    void reachedEOS();
    
    // required functions
    void open(std::string);
    int32_t read_next();
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

// private setters
void InputStream::increaseWrite() {
    Stream::increaseRead();
    if(this->file_end == sizeof(int32_t)*this->current_read){
        this->reachedEOS();
    }
}

// setters
void InputStream::reachedEOS() {
    this->EOS = true;
}

// required functions (DUPLICATED CODE on 1 & 3 DUE TO ERRORS)
void InputStream::open(std::string file_to_open) {
    if(this->getUsedMethod() == 2){
        std::cout << "opening with method 2" << std::endl;
        this->pFile = fopen(file_to_open.c_str(), "rb");
        fseek(this->getPFile(), 0, SEEK_END);
        this->file_end = ftell(this->getPFile());
        fseek(this->getPFile(), 0, SEEK_SET);
    }
    else {
        std::cout << "opening file : " << file_to_open << std::endl;
        this->file = file_to_open;
        this->fd = ::open(file_to_open.c_str(), O_RDONLY);
        std::cout << "obtained FD : " << getFD() << std::endl;
        
        this->file_end = (int)lseek(this->getFD(), 0, SEEK_END);
        lseek(this->getFD(), 0, SEEK_SET);
    }
    
    // clear info of previous streams
    this->total_mappings = 0;
    this->current_read = 0;
    this->EOS = false;
}

int32_t InputStream::read1() {
    /*
     read using unistd read function
     */
    int32_t res;
    read(this->getFD(), &res, sizeof(res));
    std::cout << "read (1): " << res << std::endl;
    this->increaseWrite();
    
    return res;
}

int32_t InputStream::read2() {
    /*
     read using stdio fread function
     */
    int32_t res;
    size_t status;
    fread(&res, sizeof(res), 1, this->getPFile());
    std::cout << "read (2): " << res << std::endl;
    this->increaseWrite();
    
    return res;
}

int32_t InputStream::read3() {
    /*
     read1 + buffer of size B
     */
    int32_t res;
    if(this->getCurrentRead() == this->getB()){
        std::cout << "loading new buffer" << std::endl;
        int32_t res;
        read(this->getFD(), (void*)this->getBuffer(), this->getB()*sizeof(res));
        this->current_read = 0;
    }
    res = this->getBuffer()[this->getCurrentRead()];
    std::cout << "read (3): " << res << std::endl;
    this->increaseWrite();
    
    return res;
}

int32_t InputStream::read4() {
    // memory mapping (minimum B : 1024);
    if(this->getCurrentRead() == this->getB()){
        munmap(this->getMappedData(), this->getB()*sizeof(size_t));
        std::cout << "creating new mapping" << std::endl;
        // execute new mapping
        off_t offset= (off_t) this->getTotalMappings() * this->getB() * sizeof(int32_t);
        std::cout << "current offset : " << offset << std::endl;
        int32_t* map = (int32_t*)mmap(0, this->getB()*sizeof(size_t), PROT_READ, MAP_SHARED, this->getFD(), offset);
        
        // update data
        this->setMappedData(map);
        this->current_read = 0;
        this->increaseMappings();
    }
    int32_t res = this->getMappedData()[this->getCurrentRead()];
    std::cout << "read (4): " << res << std::endl;
    this->increaseWrite();
    
    return res;
}

int32_t InputStream::read_next() {
    
    int32_t res;
    if(end_of_stream()){
        std::cout << "read impossible, reached end of file" << std::endl;
        res = 0;
    }
    else{
        switch (this->getUsedMethod()) {
            case 1:
                res = this->read1();
                break;
            case 2:
                res = this->read2();
                break;
            case 3:
                res = this->read3();
                break;
            case 4:
                res = this->read4();
                break;
        }
    }
    return res;
}

bool InputStream::end_of_stream() {
    return this->EOS;
}
