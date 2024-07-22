#include <threadpool.hpp>

#include <iostream>

void test1()
{
    int a = 0;
    while (true)
    {
        std::cout << "task 1" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        if (++a == 2)
            return;
    }
}

void test2()
{
    while (true)
    {
        std::cout << "task 2" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

void test3()
{
    while (true)
    {
        std::cout << "task 3" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

int main()
{
    ThreadPool tPool(2);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    tPool.addJob(test1);
    tPool.addJob(test2);
    tPool.addJob(test3);

    return 0;
}