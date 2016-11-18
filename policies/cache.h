#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <stdarg.h>
#include <map>

#include "request.h"
#include "event.h"
#include "listener.h"
#include "event_queue.h"



using namespace std;

// uncomment to enable cache debugging:
#define CDEBUG 1

// util for debug
#ifdef CDEBUG
#define LOG(m,x,y,z) log_message(m,x,y,z)
#else
#define LOG(m,x,y,z)
#endif
inline void log_message(string m, double x, double y, double z) {
  cerr << m << "," << x << "," << y  << "," << z << "\n";
}

class Cache;

class CacheFactory {
public:
  CacheFactory() {}
  virtual unique_ptr<Cache> create_unique() = 0;
};

class Cache : public listener<request>{
public:
  // create and destroy a cache
  Cache() : cache_size(0), current_size(0), hits(0), bytehits(0), logStatistics(false) {
  }
  virtual ~Cache(){};

  // configure cache parameters
  virtual void setSize(long long cs) {cache_size = cs;
    cerr << "Cache size: " << cache_size << endl;}


  virtual void setPar(string parName, string parValue) {}
    
    virtual void notify(request req){
        bool hit(request(req.get_id(), req.get_size()));
        auto resp = std::make_shared<response>(req.get_id(),req.get_timestamp(), hit ? 0:1, hit);
        for(auto it=listeners.begin(); it!= listeners.end(); it++){
            resp->listen(*it);
        }
        event_queue::push(resp);

    }

  // request an object from the cache
  virtual bool request (const long cur_req, const long long size) = 0;
  // check in cache (debugging)
  virtual bool lookup (const long cur_req) const = 0;

    void listen(listener<response>* listener){
        listeners.push_back(listener);
    }

  // statistics
  void startStatistics() {
    logStatistics = true;
  }
  void stopStatistics() {
    logStatistics = false;
  }
  void resetStatistics() {
    hits = 0;
    bytehits = 0;
  }
  long getHits() const {
    return(hits);
  }
  long long getBytehits() const {
    return(bytehits);
  }
  long long getCurrentSize() const {
    return(current_size);
  }
  long long getSize() const {
    return(cache_size);
  }
  // helper functions (factory pattern)
  static void registerType(string name, CacheFactory *factory) {
    get_factory_instance()[name] = factory;
  }
  static unique_ptr<Cache> create_unique(string name) {
    unique_ptr<Cache> Cache_instance;
    if(get_factory_instance().count(name) != 1) {
      cerr << "unkown cacheType" << endl;
      return nullptr;
    }
    Cache_instance = move(get_factory_instance()[name]->create_unique());
    return Cache_instance;
  }

protected:
  // basic cache properties
  long long cache_size;
  long long current_size;
  // cache hit statistics
  long hits;
  long long bytehits;

  bool logStatistics;

  // helper functions (factory pattern)
   static map<string, CacheFactory *> &get_factory_instance() {
     static map<string, CacheFactory *> map_instance;
     return map_instance;
  }
  // helper function (statistics gathering)
   void hit(long size) {
    if(logStatistics) {
      hits++;
      bytehits+=size;
        }
    }

private:
   std::vector<listener<response>* > listeners;
        

};

template<class T>
 class Factory : public CacheFactory {
 public:
  Factory(string name) { Cache::registerType(name, this); }
  unique_ptr<Cache> create_unique() {
    unique_ptr<Cache> newT(new T);
    return newT;
  }
};


#endif /* CACHE_H */
