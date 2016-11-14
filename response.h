#ifndef RESPONSE_H
#define RESPONSE_H 
#include "event.h"
#include "listener.h"

class response: public event{
    public:
        response(uint32_t id, uint64_t timestamp, uint64_t latency, bool hit):
            id(id), 
            latency(latency), 
            hit(hit),
            event(timestamp+latency)
        {}

        virtual void process(){
            for(auto it=listeners.begin(); it!= listeners.end(); it++){
                (*it)->notify(*this);
            }
        }

        uint64_t get_latency(){
            return latency;
        }

        void listen(listener<response>* l){
            listeners.push_back(l);
        }

        inline bool was_hit(){
            return hit;
        }


    private:
        uint32_t id;
        uint64_t latency;
        bool hit;
        std::vector<listener<response>* > listeners;

};
#endif /* RESPONSE_H */
