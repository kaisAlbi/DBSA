//
//  main.cpp
//  DBSA
//
//  Created by Tanguy d'Hose on 20/11/17.
//

#include "main.hpp"
#include "InputStream.cpp"
#include "OutputStream.cpp"
#include "Merge.hpp"
#include <random>

using namespace std;

void file_generator(std::string file_name, int length){
    /*
     Generates binary file of 'length' 32-bit int's withe name 'file_name'
     */
    OutputStream generator_stream = OutputStream(length);
    generator_stream.create(file_name);
    
    // random device & seed
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // define boundaries and distribution
    int32_t int32min = std::numeric_limits<int32_t>::min();
    int32_t int32max = std::numeric_limits<int32_t>::max();
    std::uniform_int_distribution<int32_t> distribution(int32min,int32max);
    
    // write to stream
    int32_t chosen;
    for(int i = 0; i < length; i++){
        chosen = distribution(gen);
        generator_stream.write(chosen);
    }
    
    // close
    generator_stream.close();
}

int main(){
    /*
     B must be equal in i_stream and o_stream; minium 1024 for method 4
     */
    //InputStream i_stream;
    InputStream i_stream = InputStream(1024);
    InputStream i_stream2 = InputStream(1024);
    //OutputStream o_stream;
    OutputStream o_stream = OutputStream(1024);
    OutputStream o_stream2 = OutputStream(1024);
    
    /*
    // testing output stream (-> used method / writes)
    o_stream.setUsedMethod(1);
    o_stream.create("test_files/new_file.dat");
    o_stream.write(10000);
    o_stream.write(60000);
    o_stream.close();
    
    o_stream2.setUsedMethod(1);
    o_stream2.create("test_files/new_file2.dat");
    o_stream2.write(8000);
    o_stream2.write(70000);
    o_stream2.close();
     */
    
    /*
    // testing input stream (-> used method / reads)
    i_stream.setUsedMethod(1);
    i_stream.open("test_files/new_file.dat");
    i_stream.read_next();
    i_stream.read_next();
    i_stream.read_next();
    
    //bool end = i_stream.end_of_stream();
    i_stream.close();
    */
     
    // file_gen test
     /*
    file_generator("test_files/test.dat", 1024);
    i_stream.open("test_files/test.dat");
    for(int i = 0; i < 1024; i++){
        i_stream.read_next();
    }
     */
    
    // merge tests
     /*
    i_stream.open("test_files/new_file.dat");
    i_stream2.open("test_files/new_file2.dat");
    
    std::list<InputStream> list_of_streams;
    list_of_streams.push_back(i_stream);
    list_of_streams.push_back(i_stream2);
    
      
    // multiway merge test
    multiway_merge(list_of_streams);
    i_stream.close();
    i_stream2.close();
    
    i_stream.open("test_files/mergesort0.dat");
    i_stream.read_next();
    i_stream.read_next();
    i_stream.read_next();
    i_stream.read_next();
    */
    
    // external merge test
    external_merge("test_files/test.dat", 800, 3);
    
    i_stream.open("test_files/merge_result.dat");
    for(int i = 0; i < 1025; i++){
        i_stream.read_next();
    }
    
    return 1;
}
