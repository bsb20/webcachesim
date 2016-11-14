#include "machine.h"
#include <iostream>

machine::machine(request_stream& requests, Cache& c):timestamp(0), requests(requests), cache(c){
}

void machine::start(){
    cache.set_event_queue(&event_queue);
    cache.listen(this);
    auto first = requests.next();
    first->listen(this);
    first->listen(&cache);
    event_queue.push(first);
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
        event_queue.push(next);
    }
    catch(int){
        std::cerr << "Reqs: " << reqs << std::endl;
        std::cerr << "Hits: " << hits << std::endl;
        std::cerr << "DONE" << std::endl;
    }
}

bool machine::process(){
    if(!event_queue.empty()){
        std::shared_ptr<event> next(event_queue.top());
        event_queue.pop();
        timestamp = next->get_timestamp();
        next->process();
        return true;
    }
    else{
        return false;
    }
}
