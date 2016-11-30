#ifndef LISTENER_H
#define LISTENER_H 

template<typename T>
class listener{
    public:
        virtual void notify(T event)=0;
};

#endif /* LISTENER_H */
