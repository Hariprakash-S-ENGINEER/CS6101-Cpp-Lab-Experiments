#include <iostream>
#include <memory>
#include <utility>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
    void use() const { std::cout << "Resource is being used\n"; }
};

class MySmartPointer {
public:
    explicit MySmartPointer(Resource* resource) : resource_(resource) {}
    ~MySmartPointer() { delete resource_; }
    MySmartPointer(const MySmartPointer&) = delete;
    MySmartPointer& operator=(const MySmartPointer&) = delete;
    MySmartPointer(MySmartPointer&& other) noexcept : resource_(std::exchange(other.resource_, nullptr)) {}
    MySmartPointer& operator=(MySmartPointer&& other) noexcept {
        if (this != &other) {
            delete resource_;
            resource_ = std::exchange(other.resource_, nullptr);
        }
        return *this;
    }
    Resource* operator->() const { return resource_; }
private:
    Resource* resource_;
};

int main() {
    std::cout << "--- Manual RAII owner ---\n";
    { MySmartPointer resource(new Resource()); resource->use(); }

    std::cout << "--- unique_ptr ---\n";
    { auto resource = std::make_unique<Resource>(); resource->use(); }

    std::cout << "--- shared_ptr ---\n";
    {
        auto first = std::make_shared<Resource>();
        auto second = first;
        first->use();
        std::cout << "Shared pointer count: " << first.use_count() << '\n';
    }
}
