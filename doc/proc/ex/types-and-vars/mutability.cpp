#include <iostream>

int main()
{
  auto price = 0; // In cent.
  price = 42;
  price = price +   90; // Buy ice cream.
  price = price + 1399; // Buy SD-card.
  price = price +  345; // Buy apples.
  std::cout << "Total price: " << price / 100.0 << "\n";
}
