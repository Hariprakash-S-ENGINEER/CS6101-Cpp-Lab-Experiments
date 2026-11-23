#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual const char* name() const = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}
    double area() const override { return 3.14 * radius_ * radius_; }
    const char* name() const override { return "Circle"; }
private:
    double radius_;
};

class Rectangle final : public Shape {
public:
    Rectangle(double length, double width) : length_(length), width_(width) {}
    double area() const override { return length_ * width_; }
    const char* name() const override { return "Rectangle"; }
private:
    double length_;
    double width_;
};

class Triangle final : public Shape {
public:
    Triangle(double base, double height) : base_(base), height_(height) {}
    double area() const override { return 0.5 * base_ * height_; }
    const char* name() const override { return "Triangle"; }
private:
    double base_;
    double height_;
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(4, 6));
    shapes.push_back(std::make_unique<Triangle>(10, 8));

    for (const auto& shape : shapes)
        std::cout << "Area of " << shape->name() << ": " << shape->area() << '\n';
}
