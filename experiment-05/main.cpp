#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int mark;
    char grade = ' ';
};

int main() {
    std::vector<Student> students{{"Arun", 85}, {"Bala", 72}, {"Kumar", 91}, {"Ravi", 65}};

    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.mark > b.mark;
    });
    std::transform(students.begin(), students.end(), students.begin(), [](Student student) {
        if (student.mark >= 90) student.grade = 'A';
        else if (student.mark >= 75) student.grade = 'B';
        else if (student.mark >= 50) student.grade = 'C';
        else student.grade = 'F';
        return student;
    });
    const auto topStudent = std::find_if(students.begin(), students.end(), [](const Student& student) {
        return student.mark > 80;
    });
    const int total = std::accumulate(students.begin(), students.end(), 0,
        [](int sum, const Student& student) { return sum + student.mark; });
    const double average = students.empty() ? 0.0 : static_cast<double>(total) / students.size();

    std::cout << "Student Grade Analyzer\nName\tMark\tGrade\n";
    for (const auto& student : students)
        std::cout << student.name << '\t' << student.mark << '\t' << student.grade << '\n';
    if (topStudent != students.end())
        std::cout << "First student scoring above 80: " << topStudent->name << '\n';
    std::cout << "Total Marks: " << total << "\nAverage Mark: "
              << std::fixed << std::setprecision(2) << average << '\n';
}
