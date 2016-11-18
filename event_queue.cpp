#include "event_queue.h"

heap_t event_queue::event_heap(new std::priority_queue<std::shared_ptr<event> >);

bool event_queue::empty(){
    return event_heap->empty();
}

std::shared_ptr<event> event_queue::pop(){
    std::shared_ptr<event> next(event_heap->top());
    event_heap->pop();
    return next;
}

void event_queue::push(std::shared_ptr<event> e){
    event_heap->push(e);
}
