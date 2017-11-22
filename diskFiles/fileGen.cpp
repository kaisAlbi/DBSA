//
//  fileGen.cpp
//  DBSA
//
//  Created by Nicolas Baudoux on 20/11/17.
//

#include "fileGen.hpp"

class fileGen {
	std::size_t _length;	//Length of the file (Amount of 32-bit integers)
	std::string _path;		//Path to the file
	
public:
	//Constructor
	fileGen(std::size_t length, std::string path): 
										_length(length), _path(path){
		//Opening output stream
		std::ofstream outputFile;
		outputFile.open(_path);
		
		//Source : https://stackoverflow.com/a/22883968
		std::random_device rd;     	//Get a random seed from the OS entropy device, or whatever
		std::mt19937 eng(rd()); 	//Use the 32-bit Mersenne Twister 19937 generator
									//and seed it with entropy.
									
		int32_t int32min = std::numeric_limits<int32_t>::min(); //minimum value
		int32_t int32max = std::numeric_limits<int32_t>::max(); //maximum value 
		
		//Define the distribution, by default it goes from 0 to MAX(unsigned long long)
		//or what have you. 
		std::uniform_int_distribution<int32_t> distr(int32min,int32max);
		for(std::size_t i = 0; i < _length; ++i){
			//Writing in file
			outputFile << distr(eng);
			outputFile << std::endl;
		};
		outputFile.close();
	}	
};

//Test
int main(){
	fileGen(10, "test.txt");
}
