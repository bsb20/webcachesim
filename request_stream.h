#ifndef REQUEST_STREAM_H
#define REQUEST_STREAM_H 
#include "request.h"
#include <memory>

class request_stream{

    public:
        virtual std::shared_ptr<request> next()=0;
};


#endif /* REQUEST_STREAM_H */
