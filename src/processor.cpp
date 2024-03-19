#include "processor.hpp"

#include <functional>
#include <iostream>
#include <sstream>
#include <numeric>

Processor::Processor(TSQueue<std::vector<int>>& queue_in
    , TSQueue<float>& queue_out)
    : input_queue(queue_in)
    , output_queue(queue_out)
    , processing_thread(std::bind(&Processor::thread_loop, this))
{
}

Processor::~Processor()
{
    running = false;
    wait_until_finished();
}

void Processor::thread_loop()
{
    while(running || !input_queue.empty())
    {
        const auto input = input_queue.pop();
        // the only case this should be nullopt is when 
        // the queue is empty and stop flag is set
        if (input == std::nullopt)
        {
            break;
        }
        const float output = calculate_average(input.value());
        print_results(input.value(), output);
        output_queue.push(output);
    }
    output_queue.notify_manually();
    std::cout << "Processor finished" << std::endl;
}

float Processor::calculate_average(const std::vector<int>& input) const
{
    const auto sum = std::reduce(input.begin(), input.end());
    return static_cast<float>(sum) / static_cast<float>(input.size());
}

void Processor::print_results(const std::vector<int>& input, const float& avg) const
{
    std::stringstream log_stream;
    log_stream << "Input: ";
    for (const auto& value : input)
    {
        log_stream << value << " ";
    }
    log_stream << "Average: " << avg << std::endl;
    std::cout << log_stream.str();
}

void Processor::wait_until_finished()
{
    if (processing_thread.joinable())
        processing_thread.join();
}