#ifndef SYSTEM_H
#define SYSTEM_H 
#include <vector>

#include "event_queue.h"
#include "fetch.h"
#include "listener.h"

class backend_system{
    
    public:
        virtual ~backend_system(){};

        void listen(listener<response>* listener){
            listeners.push_back(listener);
        }

        virtual void process(request req, listener<fetch>* requestor){
            auto fetch_event = std::make_shared<fetch>(req.get_id(), req.get_size(), req.get_timestamp(), 0);
            fetch_event->listen(requestor);
            event_queue::push(fetch_event);
        }

    private:
        std::vector<listener<response>* > listeners;
    
};



#endif /* SYSTEM_H */
