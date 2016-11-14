#include "event.h"

event::event(uint64_t timestamp):timestamp(timestamp){}

bool operator<(const event &e1, const event&e2){
    return e1.get_timestamp() < e2.get_timestamp();
}
