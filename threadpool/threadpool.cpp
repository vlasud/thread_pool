#include "threadpool.hpp"


ThreadPool::ThreadPool()
    : ThreadPool(std::thread::hardware_concurrency())
{
}

ThreadPool::ThreadPool(uint32_t max_threads)
    : shouldStop(false)
{
    threads.reserve(max_threads);

    for (uint32_t i = 0; i < max_threads; ++i)
        threads.emplace_back(std::thread(&ThreadPool::run, this));
}

ThreadPool::~ThreadPool()
{
    stop();

    for (auto & i : threads)
        i.join();
}

void ThreadPool::run()
{
    while (true)
    {
        std::unique_lock<std::mutex> ul(mutex);
        conditionVarForRunTask.wait(ul, [this]() { return !jobQueue.empty() || shouldStop; });

        if (shouldStop && jobQueue.empty())
            return;

        if (!jobQueue.empty())
        {
            auto job = std::move(jobQueue.front());
            jobQueue.pop();
            ul.unlock();

            job();
        }
    }
}

void ThreadPool::stop()
{
    shouldStop = true;
    conditionVarForRunTask.notify_all();
}

void ThreadPool::addJob(std::function<void()> func)
{
    std::lock_guard<std::mutex> lmtx(mutex);
    jobQueue.emplace(func);
    conditionVarForRunTask.notify_one();
}
