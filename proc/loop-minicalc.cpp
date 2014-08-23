#include <iostream>

int main()
{
    double value;
    std::cout << "Enter initial value: ";
    std::cin >> value;

    char op;
    std::cout << "Enter an operator followed by an operand.\n";
    do {
        double operand;
        std::cout << "> ";
        std::cin >> op;
        if (op != 'q' && op != 'Q') {
            std::cin >> operand;
            switch (op) {
                case '+': value += operand; break;
                case '-': value -= operand; break;
                case '*': value *= operand; break;
                case '/':
                    if (operand != 0)
                        value /= operand;
                    else
                        std::cout << "E: Cannot divide by zero.\n";
                break;

                default:
                    std::cout << "E: unknown operator '" << op << "'.\n";
                break;
            }
            std::cout << "Current value: " << value << "\n";
        }
    } while (op != 'q' && op != 'Q');
}
