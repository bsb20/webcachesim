#include "machine.h"
#include <iostream>
#include "event_queue.h"

machine::machine(request_stream& requests, Cache& c):timestamp(0), reqs(0), hits(0), requests(requests), cache(c){
}
machine::~machine(){
    std::cout << "Hits: " << hits << std::endl;
    std::cout << "Requests: " << reqs << std::endl;
}

void machine::start(){
    cache.listen(this);
    auto first = requests.next();
    first->listen(this);
    first->listen(&cache);
    event_queue::push(first);
}

void machine::notify(request r){
    reqs++; 
}

void machine::notify(response r){
    if(r.was_hit()){
        hits++;
    }
    else{
        std::cout << "Miss latency: " << r.get_latency() << std::endl;
    }
    try{
        auto next = requests.next();
        next->listen(this);
        next->listen(&cache);
        event_queue::push(next);
    }
    catch(int){
        std::cerr << "DONE" << std::endl;
    }
}

bool machine::process(){
    if(reqs > 100){
        return false;
    }
    if(!event_queue::empty()){
        std::shared_ptr<event> next(event_queue::pop());
        timestamp = next->get_timestamp();
        next->process();
        return true;
    }
    else{
        return false;
    }
}
