#ifndef REQUEST_FILESTREAM_H
#define REQUEST_FILESTREAM_H 
#include <string>
#include <fstream>
#include <memory>
#include "listener.h"
#include "request.h"
#include "request_stream.h"



class request_filestream : public request_stream{
    public:
        
        request_filestream(std::string filename);
        virtual std::shared_ptr<request> next();

    private:
        std::ifstream source_file;
};


#endif /* REQUEST_FILESTREAM_H */
