﻿#include "../inc/Reduce.h"

#include <algorithm>

Reduce::Reduce(std::vector<std::string> data, size_t numThreads)
    : m_data(data), m_Threads(numThreads) {}

void Reduce::Work(fncToReduce reduce_func) {
  std::vector<std::shared_ptr<std::vector<std::string>>> containers(m_Threads);
  std::generate(containers.begin(), containers.end(),
                []() { return std::make_shared<std::vector<std::string>>(); });

  // Generate keys
  {
    for (auto &part : m_data) {
      std::hash<std::string> hash;
      uint8_t key = (part.empty()) ? 0 : (hash(part) % m_Threads);

      containers[key]->push_back(part);
    }
  }

  // Start reduce procedure
  {
    std::vector<Task<std::shared_ptr<std::ofstream>>> reducers;

    for (size_t taskIndex = 0; taskIndex < m_Threads; taskIndex++) {
      std::string fileName("result_" + std::to_string(taskIndex) + ".txt");

      // Start task
      Task<std::shared_ptr<std::ofstream>> task;
      task.taskResult = std::make_shared<std::ofstream>(fileName);
      task.task = std::make_shared<std::thread>(
          reduce_func, std::ref(containers[taskIndex]), task.taskResult);
      reducers.push_back(task);
    }

    // Wait reduce
    {
      for (auto &reducer : reducers)
        reducer.task->join();

      //reducers.clear();
    }
  }
}
