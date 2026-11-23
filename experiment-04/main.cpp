#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <queue>
#include <stack>

constexpr std::size_t capacity = 10000;

template <typename T, std::size_t N>
class MyStack {
public:
    bool push(const T& value) {
        if (size_ == N) return false;
        data_[size_++] = value;
        return true;
    }
    bool pop() {
        if (size_ == 0) return false;
        --size_;
        return true;
    }
private:
    std::array<T, N> data_{};
    std::size_t size_ = 0;
};

template <typename T, std::size_t N>
class MyQueue {
public:
    bool enqueue(const T& value) {
        if (size_ == N) return false;
        data_[rear_] = value;
        rear_ = (rear_ + 1) % N;
        ++size_;
        return true;
    }
    bool dequeue() {
        if (size_ == 0) return false;
        front_ = (front_ + 1) % N;
        --size_;
        return true;
    }
private:
    std::array<T, N> data_{};
    std::size_t front_ = 0;
    std::size_t rear_ = 0;
    std::size_t size_ = 0;
};

template <typename Work>
auto timeMicroseconds(Work work) {
    const auto start = std::chrono::steady_clock::now();
    work();
    const auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    const auto customStack = timeMicroseconds([] {
        MyStack<int, capacity> values;
        for (std::size_t i = 0; i < capacity; ++i) values.push(static_cast<int>(i));
        for (std::size_t i = 0; i < capacity; ++i) values.pop();
    });
    const auto stlStack = timeMicroseconds([] {
        std::stack<int> values;
        for (std::size_t i = 0; i < capacity; ++i) values.push(static_cast<int>(i));
        for (std::size_t i = 0; i < capacity; ++i) values.pop();
    });
    const auto customQueue = timeMicroseconds([] {
        MyQueue<int, capacity> values;
        for (std::size_t i = 0; i < capacity; ++i) values.enqueue(static_cast<int>(i));
        for (std::size_t i = 0; i < capacity; ++i) values.dequeue();
    });
    const auto stlQueue = timeMicroseconds([] {
        std::queue<int> values;
        for (std::size_t i = 0; i < capacity; ++i) values.push(static_cast<int>(i));
        for (std::size_t i = 0; i < capacity; ++i) values.pop();
    });
    std::cout << "Custom Stack: " << customStack << " us\n"
              << "STL Stack: " << stlStack << " us\n"
              << "Custom Queue: " << customQueue << " us\n"
              << "STL Queue: " << stlQueue << " us\n";
}
