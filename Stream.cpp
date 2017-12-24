//
//  Stream.cpp
//
//
//  Created by Tanguy d'Hose on 24/12/17.
//

#include "Stream.hpp"
#define MAX_ITEMS 100

class Stream {
protected:
    int fd;
    FILE* pFile;
    std::string file;
    int32_t* mapped_data;
    int32_t buffer[MAX_ITEMS];
    
    int B;
    int used_method;
    int current_read;
    int total_mappings;
    
    // private getters
    int getFD();
    FILE* getPFile();
    int32_t* getMappedData();
    int32_t* getBuffer();
    int getCurrentRead();
    int getTotalMappings();
    
    // private setters
    void increaseRead();
    void increaseMappings();
    void setMappedData(int32_t*);
public:
    // constructors
    Stream();
    
    // getters
    std::string getOpenFile();
    int getUsedMethod();
    int getB();
    
    // setters
    void setOpenFile(std::string);
    void setUsedMethod(int);
    
    // additonnal / required
    void close();
};
// constructors
Stream::Stream(){
    this->setOpenFile("none");
    this->used_method = 1;
    this->total_mappings = 0;
}

// private getters
int Stream::getFD(){
    return this->fd;
}

FILE* Stream::getPFile(){
    return this->pFile;
}

int32_t* Stream::getMappedData() {
    return this->mapped_data;
}

int32_t* Stream::getBuffer(){
    return this->buffer;
}

int Stream::getCurrentRead(){
    return this->current_read;
}

int Stream::getTotalMappings(){
    return this->total_mappings;
}

// private setters
void Stream::increaseRead(){
    this->current_read++;
}

void Stream::increaseMappings(){
    this->total_mappings++;
}

void Stream::setMappedData(int32_t* new_mapping){
    this->mapped_data = new_mapping;
}

// getters
std::string Stream::getOpenFile(){
    return this->file;
}

int Stream::getUsedMethod() {
    return this->used_method;
}

int Stream::getB() {
    return this->B;
}

// setters
void Stream::setOpenFile(std::string new_file){
    this->file = new_file;
}

void Stream::setUsedMethod(int new_method){
    if(new_method < 1){
        new_method = 1;
    }
    else if(new_method > 4){
        new_method = 4;
    }
    this->used_method = new_method;
}

// additional / required
void Stream::close(){
    std::cout << "closing stream" << std::endl;
    if(this->getUsedMethod() == 2){
        fclose(this->getPFile());
    }
    else {
        ::close(this->getFD());
    }
    
    if(this->getUsedMethod() == 4){
        munmap(this->getMappedData(), this->getB()*sizeof(size_t));
    }
}
