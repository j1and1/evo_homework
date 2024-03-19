#pragma once

#include "ts_queue.hpp"

#include <atomic>
#include <thread>

class Agregator
{
public:

    Agregator(TSQueue<float>& queue_in);

    ~Agregator();

    void wait_until_finished();

private:
    std::atomic<bool> running { true };
    TSQueue<float>& input_queue;
    std::thread processing_thread;

    void thread_loop();
};