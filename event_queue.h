#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H 
#include <memory>
#include <queue>

#include "event.h"
typedef std::unique_ptr<std::priority_queue<std::shared_ptr<event> > > heap_t;
class event_queue{

    public:
        static bool empty();
        static std::shared_ptr<event> pop();
        static void push(std::shared_ptr<event> e);

    private:
        static heap_t event_heap;

};


#endif /* EVENT_QUEUE_H */
