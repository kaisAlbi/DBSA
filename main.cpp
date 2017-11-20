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
    cout << "running.." << endl;
    InputStream i_stream;
    OutputStream o_stream;
    
    // testing input stream
    i_stream.open();
    i_stream.read_next();
    bool end = i_stream.end_of_stream();
    
    cout << "should be false : " << end << endl;
    
    return 1;
}
