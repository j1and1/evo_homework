#pragma once

#include <atomic>
#include <condition_variable>
#include <memory>
#include <queue>
#include <optional>

template<typename T>
class TSQueue
{
public:

    void push(const T& element)
    {
        std::unique_lock<std::mutex> queue_guard(queue_mutex);
        queue.push(element);
        // Notify thread waiting for the elemets
        cv.notify_one();
    }

    std::optional<T> pop()
    {
        std::unique_lock<std::mutex> queue_guard(queue_mutex);
        // wait until we have an element in queue or stopflag is set
        cv.wait(queue_guard, [this] { return !queue.empty() || notified; });
        if (notified && queue.empty())
        {
            // the other option would be to throw an exception for this case, but that seemd sketchy
            // same as this
            return std::nullopt;
        }
        T element = queue.front();
        queue.pop();
        return element;
    }

    bool empty()
    {
        std::lock_guard<std::mutex> queue_guard(queue_mutex);
        return queue.empty();
    }

    
    void notify_manually()
    {
        notified = true;
        cv.notify_all();
    }
   
private:
    std::atomic_bool notified { false };
    std::mutex queue_mutex;
    std::queue<T> queue;
    std::condition_variable cv; // used to wake up threads waiting for data
};