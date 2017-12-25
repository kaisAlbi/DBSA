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
#include "MultiWayMerge.hpp"

using namespace std;

int main(){
    /*
     B must be equal in i_stream and o_stream
     */
    //InputStream i_stream;
    InputStream i_stream = InputStream(1024);
    InputStream i_stream2 = InputStream(1024);
    //OutputStream o_stream;
    OutputStream o_stream = OutputStream(1024);
    OutputStream o_stream2 = OutputStream(1024);
    
    
    // testing output stream
    o_stream.setUsedMethod(1);
    o_stream.create("new_file.dat");
    o_stream.write(10000);
    o_stream.write(60000);
    o_stream.close();
    
    o_stream2.setUsedMethod(1);
    o_stream2.create("new_file2.dat");
    o_stream2.write(8000);
    o_stream2.write(70000);
    o_stream2.close();
    
    // testing input stream
    i_stream.setUsedMethod(1);
    i_stream.open("new_file.dat");
    i_stream.read_next();
    i_stream.read_next();
    i_stream.read_next();
    
    //bool end = i_stream.end_of_stream();
    i_stream.close();
    
    // file_gen test
    fileGen(10, "test.txt");
    
    // merge tests
    i_stream.open("new_file.dat");
    i_stream2.open("new_file2.dat");
    
    std::list<InputStream> list_of_streams;
    list_of_streams.push_back(i_stream);
    list_of_streams.push_back(i_stream2);
    
    multiway_merge(list_of_streams);
    i_stream.close();
    i_stream2.close();
    
    i_stream.open("mergesort.dat");
    i_stream.read_next();
    i_stream.read_next();
    i_stream.read_next();
    i_stream.read_next();
    
    return 1;
}
