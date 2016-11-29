#include "cache.h"
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

class MDPCache : public Cache{

    public:
        MDPCache(): Cache(){
                            
        }

        virtual void setPar(string parName, string parValue){
            if(parName == "f"){
                std::ifstream policy_file(parValue);
                double curr;
                std::string header;
                std::getline(policy_file, header);
                uint32_t age(0);
                while(policy_file){
                    policy_file >> curr;
                    policy[age++] = curr;
                }
            }

        }
        
        ~MDPCache(){}

        virtual bool lookup(const long cur_req) const{
            return(cache_map.count(cur_req)>0);
        }


        virtual bool request(const long cur_req, const long long size){
            for(auto i = age_map.begin(); i != age_map.end(); i++){
                    i->second++;
            }
            auto it = cache_map.find(cur_req);
            if(it != cache_map.end()){
                hit(cur_req, size);
                return true;
            }
            miss(cur_req, size);
            return false;
        }



    private:
        std::unordered_map<uint32_t, double> policy;
        std::unordered_map<long, object_t> cache_map;
        std::unordered_map<long, uint32_t> age_map;

        virtual void hit(const long cur_req, const long long size ){
            LOG("h",0,cur_req,size);
            age_map[cur_req] = 0;
            Cache::hit(size);
        }
        

        virtual void miss(const long cur_req, const long long size){
            if(cache_map.size() < cache_size){
                cache_map[cur_req] = object_t(cur_req, size);
                age_map[cur_req] = 0;
            }  
            else{
                long min_id(cache_map.begin()->first);
                double min_val(policy[age_map[min_id]]);
                for(auto it = cache_map.begin(); it != cache_map.end(); it++){
                    double val = policy[age_map[it->first]];
                    if(val < min_val){
                        min_id = it->first;
                        min_val = val;
                    }
                }
                if(min_id == cur_req){
                   return;
                }
                else{
                    cache_map.erase(min_id);
                    age_map.erase(min_id);
                    cache_map[cur_req]  = object_t(cur_req, size);
                    age_map[cur_req] = 0;
                }
            }
        }



};

static Factory<MDPCache> factoryMDP("MDP");
