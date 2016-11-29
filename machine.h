#ifndef MACHINE_H
#define MACHINE_H 
#include <queue>
#include <memory>
#include "event.h"
#include "response.h"
#include "request_stream.h"
#include "listener.h"
#include "policies/cache.h"

class machine : public listener<request>, public listener<response>{

    public:
        machine(request_stream& requests, Cache& c);
        ~machine();
        bool process();
        void start();
        virtual void notify(response event);
        virtual void notify(request event);


    private:
        uint64_t timestamp;
        uint32_t reqs;
        uint32_t hits;
        request_stream& requests;
        Cache& cache;
        

};

#endif /* MACHINE_H */
