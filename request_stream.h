#ifndef REQUEST_STREAM_H
#define REQUEST_STREAM_H 
#include <string>
#include <fstream>
#include "request.h"
#include <memory>

class request_stream{
    public:
        
        request_stream(std::string filename);
        virtual std::shared_ptr<request> next();

    private:
        std::ifstream source_file;
};


#endif /* REQUEST_STREAM_H */
