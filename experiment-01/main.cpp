#include <iostream>
#include <string>
#include <utility>

class Student {
public:
    Student(int rollNumber, std::string studentName)
        : rollNumber_(rollNumber), name_(std::move(studentName)) {
        std::cout << "Student object created\n";
    }

    void display() const {
        std::cout << "Roll Number: " << rollNumber_ << '\n'
                  << "Name: " << name_ << '\n';
    }

    ~Student() { std::cout << "Student object destroyed\n"; }

private:
    int rollNumber_;
    std::string name_;
};

int main() {
    Student student(101, "Arun");
    student.display();
}
