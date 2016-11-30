#ifndef RESPONSE_H
#define RESPONSE_H 
#include "event.h"
#include "listener.h"

class response: public event{
    public:
        response(uint32_t id, uint64_t timestamp, bool hit):
            id(id), 
            hit(hit),
            event(timestamp)
        {}

        virtual void print(){
            std::cout << "RESP" << id << std::endl;
        }



        virtual void process(){
            for(auto it=listeners.begin(); it!= listeners.end(); it++){
                (*it)->notify(*this);
            }
        }

        void listen(listener<response>* l){
            listeners.push_back(l);
        }

        inline bool was_hit(){
            return hit;
        }


    private:
        uint32_t id;
        bool hit;
        std::vector<listener<response>* > listeners;

};
#endif /* RESPONSE_H */
