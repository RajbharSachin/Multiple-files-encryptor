#include <iostream>
#include "IO.hpp"
#include <fstream>

// define these IO functions
IO::IO(const std::string& file_path){
    file_stream.open(file_path, std::ios::in | std::ios::out | std::ios::binary);
    if(!file_stream.is_open()){
        std::cout << "Unable to open the file: "<<file_path<<std::endl;
    }
}

std::fstream IO::getFileStream(){ // getters- get the value of path &
    return std::move(file_stream); // return it
}

IO::~IO(){
    if(file_stream.is_open()){
        file_stream.close();
    }
}



