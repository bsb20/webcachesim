#ifndef REQUEST_RAND_STREAM_H
#define REQUEST_RAND_STREAM_H

#include "request_stream.h"
#include <vector>
#include <random>

class request_rand_stream : public request_stream{
   
    public:
        request_rand_stream(std::vector<uint32_t>lengths, std::vector<double> pmf);
        virtual std::shared_ptr<request> next(); 

    private:

        std::vector<double> cutoffs;
        std::vector<uint32_t> pointers;
        std::vector<uint32_t> lengths;
        std::mt19937 generator;
        std::uniform_real_distribution<double> distribution;
        uint64_t clock;
        
};
#endif /* REQUEST_RAND_STREAM_H */
