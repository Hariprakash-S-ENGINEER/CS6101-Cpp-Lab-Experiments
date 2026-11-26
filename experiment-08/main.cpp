#include <chrono>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

class String {
public:
    explicit String(const char* text = "") {
        if (text == nullptr) text = "";
        length_ = std::strlen(text);
        data_ = new char[length_ + 1];
        std::memcpy(data_, text, length_ + 1);
    }

    String(const String& other) : String(other.data_ ? other.data_ : "") {}

    String(String&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)),
          length_(std::exchange(other.length_, 0)) {}

    String& operator=(const String& other) {
        if (this != &other) {
            String copy(other);
            swap(copy);
        }
        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = std::exchange(other.data_, nullptr);
            length_ = std::exchange(other.length_, 0);
        }
        return *this;
    }

    ~String() { delete[] data_; }

    void swap(String& other) noexcept {
        using std::swap;
        swap(data_, other.data_);
        swap(length_, other.length_);
    }

    const char* c_str() const { return data_ ? data_ : ""; }
    std::size_t size() const { return length_; }

private:
    char* data_ = nullptr;
    std::size_t length_ = 0;
};

template <typename T>
String createString(T&& value) {
    return String(std::forward<T>(value));
}

int main() {
    constexpr int iterations = 100000;
    const String original(
        "This is a resource-heavy string used to demonstrate copy and move semantics in C++.");

    std::size_t checksum = 0;
    const auto copyStart = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) {
        String copy = original;
        checksum += copy.size();
    }
    const auto copyEnd = std::chrono::steady_clock::now();

    const auto moveStart = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) {
        String temporary(
            "This is a resource-heavy string used to demonstrate move semantics.");
        String moved = std::move(temporary);
        checksum += moved.size();
    }
    const auto moveEnd = std::chrono::steady_clock::now();

    String forwarded = createString("Perfect Forwarding Example");
    std::cout << "Perfect Forwarding Result: " << forwarded.c_str() << '\n';
    std::cout << "\nCopy Operation Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     copyEnd - copyStart).count()
              << " milliseconds\n";
    std::cout << "Move Operation Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     moveEnd - moveStart).count()
              << " milliseconds\n";
    (void)checksum;
}
