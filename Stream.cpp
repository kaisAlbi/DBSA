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
    int32_t buffer[MAX_ITEMS];
    
    int B;
    int used_method;
    int current_read;
    
    // private getters
    int getFD();
    FILE* getPFile();
    int32_t* getBuffer();
    int getCurrentRead();
    
    // private setters
    void increaseRead();
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
}

// private getters
int Stream::getFD(){
    return this->fd;
}

FILE* Stream::getPFile(){
    return this->pFile;
}

int32_t* Stream::getBuffer(){
    return this->buffer;
}

int Stream::getCurrentRead(){
    return this->current_read;
}

// private setters
void Stream::increaseRead(){
    this->current_read++;
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
    switch (getUsedMethod()) {
        case 1|3:
            ::close(this->getFD());
            break;
            
        case 2:
            fclose(this->getPFile());
            break;
    }
}
