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
    //InputStream i_stream;
    InputStream i_stream = InputStream(2);
    //OutputStream o_stream;
    OutputStream o_stream = OutputStream(2);
    
    
    // testing output stream
    o_stream.setUsedMethod(3);
    o_stream.create("new_file.dat");
    o_stream.write(9000);
    o_stream.write(20000);
    //o_stream.write(40000);
    o_stream.close();
    
    // testing input stream
    i_stream.setUsedMethod(3);
    i_stream.open("new_file.dat");
    i_stream.read_next();
    i_stream.read_next();
    //bool end = i_stream.end_of_stream();
    //i_stream.close();
    
    // file_gen test
    fileGen(10, "test.txt");
    
    return 1;
}
