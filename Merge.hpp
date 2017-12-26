//
//  MultiWayMerge.hpp
//
//
//  Created by Tanguy d'Hose on 25/12/17.
//

#ifndef MultiWayMerge_hpp
#define MultiWayMerge_hpp

#include <stdio.h>
#include <queue>

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

#endif /* MultiWayMerge_hpp */

