#include <stack>
#include <string>
#include <iostream>
using namespace std;

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

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
        return 0;
}

int evalExpression(string expression)
{
    stack<char> OPTR;
    stack<int> OPND;
    for (int i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        if (isdigit(c))
        {
            int num = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            OPND.push(num);
            i--;
        }
        else if (c == '(')
        {
            OPTR.push(c);
        }
        else if (c == ')')
        {
            // 遇到右括号，将栈内运算符依次弹出并计算，直到遇到左括号
            while (!OPTR.empty() && OPTR.top() != '(')
            {
                int b = OPND.top();
                OPND.pop();
                int a = OPND.top();
                OPND.pop();
                char op = OPTR.top();
                OPTR.pop();
                if (op == '+')
                {
                    OPND.push(a + b);
                }
                else if (op == '-')
                {
                    OPND.push(a - b);
                }
                else if (op == '*')
                {
                    OPND.push(a * b);
                }
                else if (op == '/')
                {
                    OPND.push(a / b);
                }
            }
            OPTR.pop(); // 弹出左括号
        }
        else if (isOperator(c))
        {
            while (!OPTR.empty()&&getPriority(OPTR.top()) >= getPriority(c))
            {
                int b = OPND.top();
                OPND.pop();
                int a = OPND.top();
                OPND.pop();
                char op = OPTR.top();
                OPTR.pop();
                if (op == '+')
                {
                    OPND.push(a + b);
                }
                else if (op == '-')
                {
                    OPND.push(a - b);
                }
                else if (op == '*')
                {
                    OPND.push(a * b);
                }
                else if (op == '/')
                {
                    OPND.push(a / b);
                }
            }
            OPTR.push(c);
        }
    }
    while (!OPTR.empty())
    {
        int b = OPND.top();
        OPND.pop();
        int a = OPND.top();
        OPND.pop();
        char op = OPTR.top();
        OPTR.pop();
        if (op == '+')
        {
            OPND.push(a + b);
        }
        else if (op == '-')
        {
            OPND.push(a - b);
        }
        else if (op == '*')
        {
            OPND.push(a * b);
        }
        else if (op == '/')
        {
            OPND.push(a / b);
        }
    }
    return OPND.top();
}

int main()
{
    string expression;
    getline(cin, expression);
    int result = evalExpression(expression);
    cout << result << endl;
    return 0;
}