#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <exception>

class RPN
{
public:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();
    int evaluate(const char* expression);

private:
    std::stack<int> operands;
    int performOperation(char op);

};


#endif