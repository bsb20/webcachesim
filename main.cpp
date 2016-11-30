#include "machine.h"
#include "request_filestream.h"
#include "request.h"
#include <cstdint>
#include <fstream>
#include <regex>
#include "policies/lru_variants.cc"
#include "policies/gd_variants.cc"
#include "policies/mdp_variants.cc"
#include "request_rand_stream.h"

int main(int argc, char* argv[]){
    // output help if insufficient params
    if(argc < 5) {
        cerr << "webcachesim traceFile warmUp cacheType log2CacheSize cacheParams" << endl;
        return 1;
    }

    // trace properties
    const char* path = argv[1];
    const long warmUp = atol(argv[2]);
    assert(warmUp>=0);

    // create cache
    const string cacheType = argv[3];
    unique_ptr<Cache> webcache = move(Cache::create_unique(cacheType));
    if(webcache == nullptr)
        return 1;



    // configure cache size
    const double sizeExp = atof(argv[4]);
    const long long cache_size  = pow(2.0,sizeExp);
    webcache->setSize(cache_size);

    // parse cache parameters
    regex opexp ("(.*)=(.*)");
    cmatch opmatch;
    string paramSummary;
    for(int i=5; i<argc; i++) {
      regex_match (argv[i],opmatch,opexp);
      if(opmatch.size()!=3) {
        cerr << "each cacheParam needs to be in form name=value" << endl;
        return 1;
      }
      webcache->setPar(opmatch[1], opmatch[2]);
      paramSummary += opmatch[2];
    }

    request_filestream s(path);
    //request_rand_stream s({40,100,200}, {.4, .3, .3});
    machine m(s, *webcache);
    m.start();
    while(m.process()){
    }
    return 0;
}
