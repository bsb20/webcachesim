#ifndef EVENT_H
#define EVENT_H 
#include <cstdint>
#include <iostream>
class event{

    public:
        event(uint64_t timestamp);
        virtual ~event(){};

        inline uint32_t get_timestamp() const {return timestamp;}

        virtual void print() =0;

        virtual void process(){}



    private:
        uint64_t timestamp;

};


#endif /* EVENT_H */
