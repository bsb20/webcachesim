#ifndef FETCH_H
#define FETCH_H 
#include "event.h"
#include "listener.h"

class fetch: public event{
    public:
        fetch(uint32_t id, uint32_t size, uint64_t timestamp, uint64_t latency):
            id(id), 
            size(size),
            event(timestamp + latency)
        {}

        virtual void print(){
            std::cout << "FETCH " << id << std::endl;
        }



        virtual void process(){
            for(auto it=listeners.begin(); it!= listeners.end(); it++){
                (*it)->notify(*this);
            }
        }

        uint32_t get_id(){
            return id;
        }

        uint32_t get_size(){
            return size;
        }

        void listen(listener<fetch>* l){
            listeners.push_back(l);
        }


    private:
        uint32_t id;
        uint32_t size;
        std::vector<listener<fetch>* > listeners;

};

#endif /* FETCH_H */
