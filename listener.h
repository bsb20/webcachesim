#ifndef LISTENER_H
#define LISTENER_H 

template<typename T>
class listener{
    public:
        virtual void notify(T event){};
};

#endif /* LISTENER_H */
