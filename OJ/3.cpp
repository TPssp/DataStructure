#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// 判断字符是否为运算符
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 获取运算符的优先级
int getPriority(char op)
{
    if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '+' || op == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 执行表达式计算
int evaluateExpression(const string &expression)
{
    stack<int> operandStack;   // 操作数栈
    stack<char> operatorStack; // 运算符栈

    for (int i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        if (isdigit(c))
        {
            // 处理整数
            int num = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            operandStack.push(num);
            i--; // 因为循环末尾会再次自增，所以这里需要减一
        }
        else if (c == '(')
        {
            // 左括号直接入栈
            operatorStack.push(c);
        }
        else if (c == ')')
        {
            // 遇到右括号，将栈内运算符依次弹出并计算，直到遇到左括号
            while (!operatorStack.empty() && operatorStack.top() != '(')
            {
                int b = operandStack.top();
                operandStack.pop();
                int a = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                if (op == '+')
                {
                    operandStack.push(a + b);
                }
                else if (op == '-')
                {
                    operandStack.push(a - b);
                }
                else if (op == '*')
                {
                    operandStack.push(a * b);
                }
                else if (op == '/')
                {
                    operandStack.push(a / b);
                }
            }
            operatorStack.pop(); // 弹出左括号
        }
        else if (isOperator(c))
        {
            // 处理运算符
            while (!operatorStack.empty() && getPriority(c) <= getPriority(operatorStack.top()))
            {
                int b = operandStack.top();
                operandStack.pop();
                int a = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                if (op == '+')
                {
                    operandStack.push(a + b);
                }
                else if (op == '-')
                {
                    operandStack.push(a - b);
                }
                else if (op == '*')
                {
                    operandStack.push(a * b);
                }
                else if (op == '/')
                {
                    operandStack.push(a / b);
                }
            }
            operatorStack.push(c);
        }
    }

    // 处理剩余的运算符
    while (!operatorStack.empty())
    {
        int b = operandStack.top();
        operandStack.pop();
        int a = operandStack.top();
        operandStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        if (op == '+')
        {
            operandStack.push(a + b);
        }
        else if (op == '-')
        {
            operandStack.push(a - b);
        }
        else if (op == '*')
        {
            operandStack.push(a * b);
        }
        else if (op == '/')
        {
            operandStack.push(a / b);
        }
    }

    return operandStack.top();
}

int main()
{
    string expression;

    getline(cin, expression);

    int result = evaluateExpression(expression);
    cout << result << endl;

    return 0;
}