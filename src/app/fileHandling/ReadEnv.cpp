#include <iostream>
#include <string>
#include <fstream>
#include "IO.hpp" //hpp ensures Pass-by-Reference of single class SO, doesn't import multiple times in all cpp files
#include <sstream>

class ReadEnv{
    public:
        std::string getenv(){
            std::string env_path = ".env"; // use env file outside SRC
            IO io(env_path);
            std::fstream f_stream = io.getFileStream();
            std::stringstream buffer;
            buffer << f_stream.rdbuf(); // put f_stream in buffer
            std::string content = buffer.str();
            return content;
        }

};