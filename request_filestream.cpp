#include "request_filestream.h"
#include <sstream>
#include <iostream>
request_filestream::request_filestream(std::string filename):source_file(filename){}

std::shared_ptr<request> request_filestream::next(){
    std::string line;
    if(std::getline(source_file, line)){
        std::istringstream is(line);
        uint32_t id;
        uint32_t size;
        uint64_t timestamp;
        is >> id;
        is >> size;
        is >> timestamp;
        return std::make_shared<request>(id, size, *this, timestamp);
    } 
    throw 1;
}
