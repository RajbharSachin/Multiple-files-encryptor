#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <iostream>
#include "../fileHandling/IO.hpp"
#include <sstream>

enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task {
    std::fstream f_stream;
    Action action;
    std::string filePath;

    Task(std::fstream&& stream, Action act, std::string path) 
        : f_stream(std::move(stream)), action(act), filePath(std::move(path)) {}

    // Serialize the task
    std::string toString() const{
        std::ostringstream oss;
        oss << filePath << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return oss.str();
    }

    // De-serialize
    static Task fromString(const std::string& taskData) {
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;

        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr)) {
            Action action = (actionStr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);
            IO io(filePath);
            std::fstream f_stream = std::move(io.getFileStream());
            if (f_stream.is_open()) {
                return Task(std::move(f_stream), action, filePath);
            } else {
                throw std::runtime_error("Failed to open file: " + filePath);
            }
        } else {
            throw std::runtime_error("Invalid Task-Data Format");
        }
    }
};

#endif
