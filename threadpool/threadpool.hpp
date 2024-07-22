#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>


class ThreadPool
{
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobQueue;
    std::condition_variable conditionVarForRunTask;
    std::mutex mutex;
    std::atomic<bool> shouldStop;

    void run();
    void stop();

public:
    ThreadPool();
    explicit ThreadPool(uint32_t max_threads);
    ~ThreadPool();

    void addJob(std::function<void()> func);
};
