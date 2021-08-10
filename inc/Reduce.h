#ifndef Reduce_H
#define Reduce_H
#include <fstream>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include "Task.h"

class Reduce {
public:
using fncToReduce = std::function<void(std::shared_ptr<std::vector<std::string>> &data,
                                    std::shared_ptr<std::ofstream> &out)>;
    Reduce(std::vector<std::string> &data,std::size_t numThreads);
    void Work(fncToReduce reduce_func);
private:
    Reduce() =  delete;
    std::vector<std::string> m_data;
    std::size_t m_Threads;
};
#endif