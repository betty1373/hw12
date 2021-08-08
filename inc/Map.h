#ifndef Map_H
#define Map_H
#include <fstream>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include "Task.h"

class Map {
public:
    Map(std::string fileName,std::size_t mapThreads);
    std::vector<std::shared_ptr<std::vector<std::string>>> Work(std::vector<std::ifstream::pos_type> sections,
            std::function<void(std::ifstream> &file, std::ifstream::pos_type beg_pos,std::ifstream::pos_type end_pos,
                               std::shared_ptr<std::vector<std::string>> container)> map_func);
private:
    Map() =  delete;
    std::mutex m_mutex;
    std::ifstream m_file;
    std::size_t m_mapThreads;
};
#endif