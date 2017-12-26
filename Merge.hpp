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

InputStream multiway_merge(std::list<InputStream> input_streams, int count = 0){
    
    OutputStream sorted_stream;
    InputStream return_stream;
    sorted_stream.create("test_files/mergesort" + std::to_string(count) + ".dat");
    std::queue<int32_t> sorting_queue;
    
    int j = 1;
    
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
    
    return_stream.open("test_files/mergesort" + std::to_string(count) + ".dat");
    return return_stream;
}

void s_merge(int32_t to_sort[], int start_1, int end_1, int start_2, int end_2){
    int len = end_2 - start_1 + 1;
    int32_t temp[len];
    int left = start_1;
    int right = start_2;
    
    for(int i = 0; i < len; i++){
        if(left > end_1){
            temp[i] = to_sort[right++];
        }
        else if(right > end_2){
            temp[i] = to_sort[left++];
        }
        else if(to_sort[left] <= to_sort[right]){
            temp[i] = to_sort[left++];
        }
        else {
            temp[i] = to_sort[right++];
        }
    }
    
    for(int i = 0; i < len; i++){
        to_sort[start_1++] = temp[i];
    }
}

void sub_sort(int32_t to_sort[], int start, int end){
    if(start >= end){
        return;
    }
    else {
        int mid = (start+end) / 2;
        sub_sort(to_sort, start, mid);
        sub_sort(to_sort, mid+1, end);
        s_merge(to_sort, start, mid, mid+1, end);
    }
}

void merge_sort(int32_t to_sort[], int len){
    sub_sort(to_sort, 0, len-1);
}


int getFileSize(std::string input_file){
    std::ifstream file(input_file, std::ifstream::ate | std::ifstream::binary);
    int size = file.tellg();
    return size;
}

// M = available memory in number of int32_t, d = number of streams for merge
void external_merge(std::string input_file, int M, int d){
    
    // data structures
    std::queue<std::shared_ptr<OutputStream> > file_partitionning;
    std::queue<std::shared_ptr<InputStream> > file_merging;
    InputStream dispatch_stream;
    dispatch_stream.open(input_file);
    
    // obtain file size
    int size = getFileSize(input_file);
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
    
    // close streams
    for(int i = 0; i < streams; i++){
        file_partitionning.front()->close();
        file_partitionning.pop();
    }
    
    // open created streams and mergesort
    for(int i = 0; i < streams; i++){
        InputStream in_stream;
        in_stream.open("external_merge/merge" + std::to_string(i+1) + ".dat");
        size = getFileSize("external_merge/merge" + std::to_string(i+1) + ".dat");
        
        int nb_elem = size/sizeof(int32_t);
        int32_t stream_content[nb_elem];
        
        for(int j = 0; j < nb_elem; j++){
            value = in_stream.read_next();
            stream_content[j] = value;
        }
        in_stream.close();
        
        merge_sort(stream_content, nb_elem);
        
        OutputStream out_stream;
        out_stream.create("external_merge/merge" + std::to_string(i+1) + ".dat");
        for(int j = 0; j < nb_elem; j++) {
            out_stream.write(stream_content[j]);
        }
        out_stream.close();
    }
    
    // stored sorted streams in queue
    for(int i = 0; i < streams; i++){
        InputStream new_stream;
        new_stream.open("external_merge/merge" + std::to_string(i+1) + ".dat");
        file_merging.push(std::make_shared<InputStream>(new_stream));
    }
    
    std::list<InputStream> to_merge;
    InputStream temp;
    int count = 1;
    
    // while files to merge
    while(!file_merging.empty()){
        // no previous result -> pre-select
        if(count == 1){
            temp = *file_merging.front();
            to_merge.push_back(temp);
            file_merging.pop();
        }
        
        // merge max d files together | previous result -> i = 1
        for(int i = 1; i < d && !file_merging.empty(); i++){
            temp = *file_merging.front();
            to_merge.push_back(temp);
            file_merging.pop();
        }
        
        // obtain result
        temp = multiway_merge(to_merge, count);
        to_merge.clear();
        to_merge.push_back(temp);
        count++;
    }
    
    // clear working files and rename resulting file
    std::string file_identifier, final_file;
    for(int i = 1; i < count-1; i++){
        file_identifier = "test_files/mergesort" + std::to_string(i) + ".dat";
        remove(file_identifier.c_str());
    }
    file_identifier = "test_files/mergesort" + std::to_string(count-1) + ".dat";
    final_file = "test_files/merge_result.dat";
    rename(file_identifier.c_str(), final_file.c_str());
}

#endif /* Merge_hpp */

