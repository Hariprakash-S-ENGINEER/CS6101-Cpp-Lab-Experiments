#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

int main() {
    constexpr int maxItems = 10;
    std::queue<int> buffer;
    std::mutex mutex;
    std::condition_variable condition;
    std::atomic<int> producedCount{0};
    bool finished = false;

    std::cout << "Producer-Consumer System Started\n\n";

    std::thread producer([&] {
        for (int item = 1; item <= maxItems; ++item) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            {
                std::lock_guard<std::mutex> lock(mutex);
                buffer.push(item);
                ++producedCount;
                std::cout << "Produced: " << item << '\n';
            }
            condition.notify_one();
        }

        {
            std::lock_guard<std::mutex> lock(mutex);
            finished = true;
        }
        condition.notify_all();
    });

    std::thread consumer([&] {
        while (true) {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [&] { return !buffer.empty() || finished; });

            if (buffer.empty() && finished)
                break;

            const int item = buffer.front();
            buffer.pop();
            std::cout << "Consumed: " << item << '\n';
        }
    });

    producer.join();
    consumer.join();

    std::cout << "\nTotal Items Produced: " << producedCount.load() << '\n';
    std::cout << "Producer-Consumer System Completed\n";
}
