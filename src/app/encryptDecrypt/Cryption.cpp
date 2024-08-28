#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"

int executeCryption(const std::string& taskData) {
    Task task = Task::fromString(taskData); // Deserialize
    ReadEnv env;

    std::string envKey = env.getenv();
    int key = std::stoi(envKey); // string to integer


    if(task.action == Action::ENCRYPT) {
        char ch;
        while(task.f_stream.get(ch)){
            ch = (ch+key)%256; // means value will come 0-255
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    } else {
        char ch;
        while(task.f_stream.get(ch)){
            ch = (ch-key+256)%256;
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    return 0;
}