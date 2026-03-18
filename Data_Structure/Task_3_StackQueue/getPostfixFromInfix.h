#ifndef GET_POSTFIX_FROM_INFIX_H
#define GET_POSTFIX_FROM_INFIX_H

#include "StackVector.h"
#include <cctype>

inline bool isOperand(char c) {
    return std::isdigit(c) || std::isalpha(c);
}

inline bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

inline int getPriority(char operation) {
    switch (operation) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}


void getPostfixFromInfix(const char* infix, char* postfix) {
    StackVector<char> opStack;
    size_t idxInfix = 0;
    size_t idxPostfix = 0;

    while (infix[idxInfix] != '\0') {
        char c = infix[idxInfix];

        if (isOperand(c)) {
            postfix[idxPostfix++] = c;
        }
        else if (c == '(') {
            opStack.push(c);
        }
        else if (c == ')') {
            while (!opStack.isEmpty() && opStack.top() != '(') {
                postfix[idxPostfix++] = opStack.pop();
            }
            if (opStack.isEmpty()) {
                throw std::runtime_error("ERROR: No closing bracket");
            }
            opStack.pop();
        }
        else if (isOperator(c)) {
            while (!opStack.isEmpty() && isOperator(opStack.top()) && getPriority(opStack.top()) >= getPriority(c)) {
                postfix[idxPostfix++] = opStack.pop();
            }
            opStack.push(c);
        }
        else {
            throw std::runtime_error("ERROR: Invalid character in expression");
        }
        idxInfix++;
    }

    while (!opStack.isEmpty()) {
        if (opStack.top() == '(') {
            throw std::runtime_error("ERROR: Opening bracket in the end");
        }
        postfix[idxPostfix++] = opStack.pop();
    }
    postfix[idxPostfix] = '\0';
}


#endif //GET_POSTFIX_FROM_INFIX_H