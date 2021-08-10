#ifndef Task_H
#define Task_H
#include <thread>
#include <memory>

template <typename T> struct Task {
    std::shared_ptr<std::thread> task;
    T taskResult;
};
#endif