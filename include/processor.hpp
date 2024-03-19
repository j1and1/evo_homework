#pragma once

#include "ts_queue.hpp"

#include <atomic>
#include <thread>

class Processor
{
public:

    Processor(TSQueue<std::vector<int>>& queue_in
        , TSQueue<float>& queue_out);

    ~Processor();

    void wait_until_finished();

private:
    std::atomic<bool> running { true };
    TSQueue<std::vector<int>>& input_queue;
    TSQueue<float>& output_queue;
    std::thread processing_thread;

    void thread_loop();
    float calculate_average(const std::vector<int>& input) const;
    void print_results(const std::vector<int>& input, const float& avg) const;
};