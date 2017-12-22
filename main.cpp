//
//  main.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "main.hpp"
#include "InputStream.cpp"
#include "OutputStream.cpp"
#include "diskFiles/fileGen.cpp"

using namespace std;

int main(){
    InputStream i_stream;
    OutputStream o_stream;
    
    
    // testing output stream
    o_stream.create("new_file.bin");
    o_stream.write(104);
    o_stream.close();
    
    // testing input stream
    i_stream.open("new_file.bin");
    i_stream.read_next();
    //i_stream.read_next();
    bool end = i_stream.end_of_stream();
    
    // file_gen test
    fileGen(10, "test.txt");
    
    return 1;
}
