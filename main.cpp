//
//  main.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "main.hpp"
#include "InputStream.cpp"
#include "OutputStream.cpp"

using namespace std;

int main(){
    InputStream i_stream;
    OutputStream o_stream;
    
    // testing input stream
    i_stream.open();
    i_stream.read_next();
    bool end = i_stream.end_of_stream();
    
    // testing output stream
    o_stream.create("new_file");
    o_stream.write(104);
    o_stream.close();
    
    return 1;
}
