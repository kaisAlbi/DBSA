//
//  MultiWayMerge.hpp
//
//
//  Created by Tanguy d'Hose on 25/12/17.
//

#ifndef Merge_hpp
#define Merge_hpp

#include <stdio.h>
#include <queue>
#include <fstream>
#include <cmath>
#include <memory>

int32_t find_min(std::queue<int32_t> sorting_queue, int range, int size){
    int32_t min = sorting_queue.front();
    int32_t current;
    for(int i = 1; i < size; i++){
        current = sorting_queue.front();
        sorting_queue.pop();
        if(current < min && i <= range){
            min = current;
        }
        sorting_queue.push(current);
    }
    return min;
}

std::queue<int32_t> reorder(std::queue<int32_t> sorting_queue, int32_t min, int n){
    int32_t current;
    for(int i = 1; i <= n; i++){
        current = sorting_queue.front();
        sorting_queue.pop();
        if(current != min){
            sorting_queue.push(current);
        }
    }
    sorting_queue.push(min);
    return sorting_queue;
}

void multiway_merge(std::list<InputStream> input_streams){
    
    OutputStream sorted_stream;
    sorted_stream.create("test_files/mergesort.dat");
    std::queue<int32_t> sorting_queue;
    
    // get elements into queue
    for(int i = 0; i < input_streams.size(); i++){
        
        // retrieve elements form streams
        InputStream current_stream = input_streams.front();
        std::cout << current_stream.getOpenFile() << std::endl;
        int32_t next = current_stream.read_next();
        while(next != 0){
            sorting_queue.push(next);
            next = current_stream.read_next();
        }
        
        // cycle streams to handle all
        input_streams.push_back(current_stream);
        input_streams.pop_front();
    }
    
    // execute sort
    int size = sorting_queue.size();
    int32_t min;
    for(int i = 0; i < size; i++){
        min = find_min(sorting_queue, size-i, size);
        sorting_queue = reorder(sorting_queue, min, size);
    }
    
    // write sorted queue to stream
    for(int i = 0; i < size; i++){
        sorted_stream.write(sorting_queue.front());
        sorting_queue.pop();
    }
    
    sorted_stream.close();
}

// M = available memory in number of int32_t, d = number of streams for merge
void external_merge(std::string input_file, int M, int d){
    
    // data structures
    std::queue<std::shared_ptr<OutputStream> > file_partitionning;
    InputStream dispatch_stream;
    dispatch_stream.open(input_file);
    
    // obtain file size
    std::ifstream file(input_file, std::ifstream::ate | std::ifstream::binary);
    int size = file.tellg();
    std::cout << "file size : " << size << std::endl;
    
    // calculate streams
    int streams = (int)std::ceil(size / (double)M);
    std::cout << "require streams : " << streams << std::endl;
    
    // split file into streams
    for(int i = 0; i < streams; i++){
        OutputStream new_stream;
        new_stream.create("external_merge/merge" + std::to_string(i+1) + ".dat");
        file_partitionning.push(std::make_shared<OutputStream>(new_stream));
    }
    
    // dispatch contents into files
    int32_t value = dispatch_stream.read_next();
    while(value != 0){
        file_partitionning.front()->write(value);
        auto temp = file_partitionning.front();
        file_partitionning.pop();
        file_partitionning.push(temp);
        value = dispatch_stream.read_next();
    }
    
    
    
    InputStream file_reader;
    file_reader.open(input_file);
    file_reader.read_next();
}

#endif /* Merge_hpp */

