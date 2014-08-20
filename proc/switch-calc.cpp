#include <iostream>

int main()
{
    double lhs, rhs;
    std::cout << "Enter left-hand side operand: ";
    std::cin >> lhs;
    std::cout << "Enter right-hand side operand: ";
    std::cin >> rhs;

    char op;
    std::cout << "Enter operator: ";
    std::cin >> op;

    double result = 0; // Initialize to avoid MSVC's warning C4701.
    auto valid_op = true;
    switch (op) {
        case '+': result = lhs + rhs; break;
        case '-': result = lhs - rhs; break;
        case '*': result = lhs * rhs; break;
        case '/': result = lhs / rhs; break;
        default:
            valid_op = false;
            std::cout << "E: '" << op << "' is not a known operator.\n";
        break;
    }
    if (valid_op)
        std::cout << lhs << ' ' << op << ' ' << rhs << " = " << result << '\n';
}
