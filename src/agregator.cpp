#include "agregator.hpp"

#include <functional>
#include <iostream>
#include <sstream>

Agregator::Agregator(TSQueue<float>& queue_in)
    : input_queue(queue_in)
    , processing_thread(std::bind(&Agregator::thread_loop, this))
{
}

Agregator::~Agregator()
{
    running = false;
    wait_until_finished();
}

void Agregator::thread_loop()
{
    float count = 0.0f;
    float sum = 0.0f;
    while(running || !input_queue.empty())
    {
        const auto input = input_queue.pop();
        // the only case this should be nullopt is when 
        // the queue is empty and stop flag is set
        if (input == std::nullopt)
        {
            break;
        }
        const auto value = input.value();
        sum += value;
        count++;
        std::cout << "Agregator received avg value: " << value << std::endl;
    }

    std::cout << "Agregator calculated average value: " << sum / count << std::endl;
}

void Agregator::wait_until_finished()
{
    if (processing_thread.joinable())
        processing_thread.join();
}