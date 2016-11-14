#include "request_stream.h"
#include <sstream>
#include <iostream>
#include "request.h"
request_stream::request_stream(std::string filename):source_file(filename){}

std::shared_ptr<request> request_stream::next(){
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
