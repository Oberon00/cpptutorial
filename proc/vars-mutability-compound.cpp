#include <iostream>

int main()
{
    auto price = 0; // In cent.
    price = 42;
    price +=   90; // Buy ice cream.
    price += 1399; // Buy SD-card.
    price +=  345; // Buy apples.
    std::cout << "Total price: " << price / 100.0 << "\n";
}
