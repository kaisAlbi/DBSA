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
    /*
     B must be equal in i_stream and o_stream
     */
    //InputStream i_stream;
    InputStream i_stream = InputStream(1024);
    //OutputStream o_stream;
    OutputStream o_stream = OutputStream(1024);
    
    
    // testing output stream
    o_stream.setUsedMethod(1);
    o_stream.create("new_file.dat");
    o_stream.write(10000);
    o_stream.write(60000);
    /*
    for(int i = 0; i < 64; i++){
        o_stream.write(10000);
        o_stream.write(20000);
    }
    for(int i = 0; i < 64; i++){
        o_stream.write(30000);
        o_stream.write(40000);
    }
     */
    //o_stream.write(40000);
    o_stream.close();
    
    // testing input stream
    i_stream.setUsedMethod(4);
    i_stream.open("new_file.dat");
    i_stream.read_next();
    i_stream.read_next();
    
    /*
    for(int i = 0; i < 128; i++){
        i_stream.read_next();
        i_stream.read_next();
    }
     */
    
    //bool end = i_stream.end_of_stream();
    //i_stream.close();
    
    // file_gen test
    fileGen(10, "test.txt");
    
    return 1;
}
