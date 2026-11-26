#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const std::string& message) = 0;
};

class EmailNotification final : public Observer {
public:
    explicit EmailNotification(std::string address)
        : address_(std::move(address)) {}

    void notify(const std::string& message) override {
        std::cout << "Email sent to " << address_ << ": " << message << '\n';
    }

private:
    std::string address_;
};

class SMSNotification final : public Observer {
public:
    explicit SMSNotification(std::string phoneNumber)
        : phoneNumber_(std::move(phoneNumber)) {}

    void notify(const std::string& message) override {
        std::cout << "SMS sent to " << phoneNumber_ << ": " << message << '\n';
    }

private:
    std::string phoneNumber_;
};

class NotificationFactory {
public:
    static std::shared_ptr<Observer> create(
        const std::string& type, const std::string& receiver) {
        if (type == "EMAIL")
            return std::make_shared<EmailNotification>(receiver);
        if (type == "SMS")
            return std::make_shared<SMSNotification>(receiver);
        throw std::invalid_argument("Unknown notification type.");
    }
};

class EventManager {
public:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    static EventManager& instance() {
        static EventManager manager;
        return manager;
    }

    void subscribe(std::shared_ptr<Observer> observer) {
        observers_.push_back(std::move(observer));
    }

    void triggerEvent(const std::string& message) const {
        std::cout << "\nEvent Triggered: " << message
                  << "\nSending Notifications...\n\n";
        for (const auto& observer : observers_)
            observer->notify(message);
    }

private:
    EventManager() = default;
    std::vector<std::shared_ptr<Observer>> observers_;
};

int main() {
    auto& manager = EventManager::instance();
    manager.subscribe(NotificationFactory::create("EMAIL", "student@gmail.com"));
    manager.subscribe(NotificationFactory::create("SMS", "9876543210"));
    manager.triggerEvent("University examination starts tomorrow!");
}
