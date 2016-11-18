
#include "request_rand_stream.h"

request_rand_stream::request_rand_stream(std::vector<uint32_t> lengths, std::vector<double> pmf) : lengths(lengths), generator(time(0)), distribution(0.0, 1.0), clock(1){
    double cutoff(0);
    for(int i=0; i<lengths.size(); i++){
        pointers.push_back(0); 
        cutoff += pmf[i];
        cutoffs.push_back(cutoff);
    }
}

std::shared_ptr<request> request_rand_stream::next(){
    double choice(distribution(generator));
    uint32_t base(0);
    for(int i=0; i<cutoffs.size(); i++){
        if(cutoffs[i] >= choice){
            uint32_t id(base+(pointers[i]++));
            pointers[i] = pointers[i] % lengths[i];
            return std::make_shared<request>(id, 1, *this, clock++);
        }
        else{
            base += lengths[i];
        }
    }
    return next();
}
