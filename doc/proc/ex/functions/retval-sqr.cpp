#include <iostream>


double sqr(double n)
{
    return n * n;
}


int main()
{
    auto x = 5.;
    std::cout << x << " squared: " << sqr(x) << '\n';
    std::cout << x << " to the 4th power: " << sqr(sqr(x)) << '\n';

    const auto pi = 3.14159265359;
    auto radius = 5;

    std::cout "area of circle with r=" << r << ": " << sqr(r) * pi;
}
