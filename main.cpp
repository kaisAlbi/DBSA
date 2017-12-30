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

// addtional requirements
#include <random>
#include <queue>
#include <ctime>

#define ELEM_PER_PAGE 1024
#define MAX_STREAMS 30

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

int32_t value_generator_32bit(){
    // random device & seed
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // define boundaries and distribution
    int32_t int32min = std::numeric_limits<int32_t>::min();
    int32_t int32max = std::numeric_limits<int32_t>::max();
    std::uniform_int_distribution<int32_t> distribution(int32min,int32max);
    
    return distribution(gen);
}

int max_streams(){
    int i = 0;
    std::ofstream *f;
    std::queue<std::ofstream*> stream_queue;
    
    // find max stream limit on OS
    do {
        f = new std::ofstream(std::to_string(i++));
        stream_queue.push(f);
    } while (*f << std::flush && i <= MAX_STREAMS);
    --i;
    
    // close all files
    while (!stream_queue.empty()) {
        f = stream_queue.front();
        f->close();
        stream_queue.pop();
    }
    
    // remove created files
    for(int j = 0; j < i; j++){
        remove(std::to_string(j).c_str());
    }
    
    return i;
}

void IO_benchmark(int wanted_str, int file_size, int stream_operations, int read_method = 1, int write_method = 1, int buffer_p = 1){
    int max_str = max_streams();
    int streams = min(wanted_str, max_str);
    
    int half = streams / 2;
    std::queue <std::shared_ptr<InputStream> > reading_streams;
    std::queue <std::shared_ptr<OutputStream> > writing_streams;
    
    // make half of the files reading files
    for(int i = 0; i < half; i++){
        file_generator("IO_benchmark/stream" + std::to_string(i) + ".dat", file_size);
        InputStream new_r_stream = InputStream(buffer_p * ELEM_PER_PAGE);
        new_r_stream.setUsedMethod(read_method);
        new_r_stream.open("IO_benchmark/stream" + std::to_string(i) + ".dat");
        reading_streams.push(std::make_shared<InputStream>(new_r_stream));
    }
    
    // make half of the files writing files
    for(int i = half; i < streams; i++){
        OutputStream new_w_stream = OutputStream(buffer_p * ELEM_PER_PAGE);
        new_w_stream.setUsedMethod(write_method);
        new_w_stream.create("IO_benchmark/stream" + std::to_string(i) + ".dat");
        writing_streams.push(std::make_shared<OutputStream>(new_w_stream));
    }
    
    // execute stream operations
    clock_t begin = clock();
    int32_t read;
    for(int i = 0; i < stream_operations && i < file_size; i++){
        // execute reads
        for(int j = 0; j < half; j++){
            read = reading_streams.front()->read_next();
            auto temp = reading_streams.front();
            reading_streams.pop();
            reading_streams.push(temp);
        }
        
        // execute writes
        int32_t val;
        for(int j = half; j < streams; j++){
            val = value_generator_32bit();
            writing_streams.front()->write(val);
            auto temp = writing_streams.front();
            writing_streams.pop();
            writing_streams.push(temp);
        }
    }
    clock_t end = clock();
    
    // close benchmarking files
    for(int j = 0; j < half; j++){
        reading_streams.front()->close();
        auto temp = reading_streams.front();
        reading_streams.pop();
        reading_streams.push(temp);
    }
    
    for(int j = half; j < streams; j++){
        writing_streams.front()->close();
        auto temp = writing_streams.front();
        writing_streams.pop();
        writing_streams.push(temp);
    }
    
    // remove created benchmarking files
    for(int i = 0; i < streams; i++){
        remove(("IO_benchmark/stream" + std::to_string(i) + ".dat").c_str());
    }
    
    // print exec time
    double elapsed_time = double(end-begin) / CLOCKS_PER_SEC;
    std::cout << "time elapsed : " << elapsed_time << " seconds" << std::endl;
}

int main(){
    /*
     B must be equal in i_stream and o_stream; multiple of 1024 for method 4
     */
    //InputStream i_stream;
    InputStream i_stream = InputStream(1024);
    InputStream i_stream2 = InputStream(1024);
    //OutputStream o_stream;
    OutputStream o_stream = OutputStream(1024);
    OutputStream o_stream2 = OutputStream(1024);
    
    IO_benchmark(10, 1024, 1000, 4, 4);
    
    // testing output stream (-> used method / writes)
    /*
    o_stream.setUsedMethod(3);
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
    /*
    external_merge("test_files/test.dat", 800, 3);
    
    i_stream.open("test_files/merge_result.dat");
    for(int i = 0; i < 1025; i++){
        i_stream.read_next();
    }
     */
    
    return 1;
}
