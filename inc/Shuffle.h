#ifndef Shuffle_H
#define Shuffle_H

#include <fstream>
#include <functional>
#include <memory>
#include <thread>
#include <vector>
#include <algorithm>

struct Shuffle {
    std::vector<std::string> Work(std::vector<std::shared_ptr<std::vector<std::string>>> containers) {
          std::vector<std::string> merged;
    
        for (auto &cont : containers) {
            std::vector<std::string> tmp;
            
            std::merge(cont->begin(),cont->end(),
                        merged.begin(),merged.end(),
                        std::back_inserter(tmp));
            merged = tmp;    
        }
        return merged;
    }
};
#endif