#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <shared_mutex>

class Store { 
private:
    std::unordered_map<std::string, std::string> kv_;
    mutable std::shared_mutex mtx_;

public:
    Store() = default;
    ~Store() = default;

    void set(const std::string& key, const std::string& val) {
        std::unique_lock<std::shared_mutex> lock(mtx_); 
        kv_[key] = val;
    }

    std::string get(const std::string& key) const {
        std::shared_lock<std::shared_mutex> lock(mtx_);
        auto it = kv_.find(key);
        if (it != kv_.end()) {
            return it->second;
        }
        else {
            return ""; 
        }
    }
};

#endif 