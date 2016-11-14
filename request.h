#ifndef REQUEST_H
#define REQUEST_H 

#include "event.h"
#include <vector>
#include "listener.h"
#include "request_stream.h"
#include <iostream>

class request_stream;

class request : public event{

    public:
        request(uint32_t id, uint32_t size, request_stream& source, uint64_t timestamp):
            id(id), 
            size(size), 
            source(source),
            event(timestamp){
        }

        virtual void process(){
            for(auto it=listeners.begin(); it!= listeners.end(); it++){
                (*it)->notify(*this);
            }
        }

        void listen(listener<request>* l){
            listeners.push_back(l);
        }

        uint32_t get_id(){
            return id;
        }

        uint32_t get_size(){
            return size;
        }

    private:
        uint32_t id;
        uint32_t size;
        std::vector<listener<request>* > listeners;
        request_stream& source;

};


#endif /* REQUEST_H */
