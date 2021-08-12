#ifndef Task_H
#define Task_H
#include <fstream>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

template <typename T> struct Task {
    std::shared_ptr<std::thread> task;
    T taskResult;
};
#endif