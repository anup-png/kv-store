#include<iostream>
#include<unordered_map>

#include<shared_mutex>




class Store { 

    private:
    std::unordered_map<std::string,std::string> kv_;
    mutable std::shared_mutex mtx_;

    public:
     void set(const std::string& key ,const std::string& val){
        std::unique_lock<std::shared_mutex> lock(mtx_); 
        kv_[key] = val ;
     }

     std::string get(const std::string& key)const {

        std::shared_lock<std::shared_mutex> lock(mtx_);
        if(kv_.find(key) != kv_.end()){
            return kv_[key];
        }
        else{
            return " ";
        }
     }





};