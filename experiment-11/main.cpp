#include <iostream>

struct Meter {
    static constexpr double factor = 1.0;
};

struct Kilometer {
    static constexpr double factor = 1000.0;
};

struct Centimeter {
    static constexpr double factor = 0.01;
};

template <typename Unit>
class Quantity {
public:
    constexpr explicit Quantity(double value) : value_(value) {}
    constexpr double value() const { return value_; }

private:
    double value_;
};

template <typename ToUnit, typename FromUnit>
constexpr Quantity<ToUnit> convert(const Quantity<FromUnit>& quantity) {
    const double baseValue = quantity.value() * FromUnit::factor;
    return Quantity<ToUnit>(baseValue / ToUnit::factor);
}

int main() {
    constexpr Quantity<Meter> distance(5000.0);
    constexpr auto kilometers = convert<Kilometer>(distance);
    constexpr auto centimeters = convert<Centimeter>(distance);

    std::cout << "Distance in Meters: " << distance.value() << " m\n"
              << "Distance in Kilometers: " << kilometers.value() << " km\n"
              << "Distance in Centimeters: " << centimeters.value() << " cm\n";
}
