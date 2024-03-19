#pragma once

#include "ts_queue.hpp"

#include <thread>

class Generator
{
public:

    Generator(TSQueue<std::vector<int>>& target_queue);
    ~Generator();

    void wait_until_finished();

private:
    TSQueue<std::vector<int>>& queue;
    std::thread generator_thread;

    void thread_loop();
};