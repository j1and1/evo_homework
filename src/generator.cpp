#include "generator.hpp"

#include <functional>
#include <iostream>
#include <sstream>
#include <random>

Generator::Generator(TSQueue<std::vector<int>>& target_queue)
    : queue(target_queue)
    , generator_thread(std::bind(&Generator::thread_loop, this))
{
}

Generator::~Generator()
{
    wait_until_finished();
}

void Generator::thread_loop()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> time_distr(1, 10000); // Runtime distr between 1 and 10s
    std::uniform_int_distribution<int> sleep_distr(1000, 2.5e7); // sleep distr between 0.001ms and 2.5ms
    std::uniform_int_distribution<int> vector_distr(2, 10); // element values and size

    const auto run_time = time_distr(gen); // gets the total time we can run
    std::cout << "Running for " << (run_time / 1000) << " seconds" << std::endl;
    const auto run_time_ms = std::chrono::milliseconds(run_time);
    const auto start_time = std::chrono::steady_clock::now();

    while (true)
    {
        std::stringstream log_stream;
        std::vector<int> target;
        const int size = vector_distr(gen);
        log_stream << "Adding vector: ";
        for (int i = 0; i < size; ++i)
        {
            const int value = vector_distr(gen);
            log_stream << value << " ";
            target.push_back(value);
        }
        std::cout << log_stream.str() << std::endl;
        queue.push(target);

        // check if we need to stop generating
        if (std::chrono::steady_clock::now() - start_time >= run_time_ms)
        {
            std::cout << "Generator finished" << std::endl;
            break;
        }
        // sleep for random ammount of time
        std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_distr(gen)));
    }
    queue.notify_manually();
}

void Generator::wait_until_finished()
{
    if (generator_thread.joinable())
        generator_thread.join();
}