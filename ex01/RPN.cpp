#include "RPN.hpp"
#include <string>

RPN::RPN() {}
RPN::RPN(const RPN &other) : operands(other.operands) {}
RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        operands = other.operands;
    return *this;
}

RPN::~RPN() {}

int RPN::evaluate(const char* expression) {
    std::string rules = "+-*/";
    for (size_t a = 0; expression[a]; a++)
    {
        if (rules.find(expression[a]) != std::string::npos)
            performOperation(expression[a]);
        else if (isdigit(expression[a]))
            operands.push(expression[a] - '0');
        else if (expression[a] != ' ')
            throw std::runtime_error("Error");
    }
    int result = operands.top();
    operands.pop();
    return result;
}

int RPN::performOperation(char op) {
    std::string rules = "+-*/";
    int a;
    int b;

    b = operands.top();
    operands.pop();
    a = operands.top();
    operands.pop();

    switch (rules.find(op))
    {
        case 0:
            operands.push(a + b);
            break;
        case 1:
            operands.push(a - b);
            break;
        case 2:
            operands.push(a * b);
            break;
        case 3:
            if (b == 0)
                throw std::runtime_error("Error: Division by zero");
            operands.push(a / b);
            break;
        default:
            throw std::runtime_error("Error: Invalid operator");
    }
    return 0;
}