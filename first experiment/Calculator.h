#pragma once
#include <iostream>
#include<stdlib.h>
using namespace std;
#include "LinkStack.h"
class Calculator
{
private:
    static bool Operator(char op);//判断字符是否为运算符,当设为静态函数就属于类 可以直接调用而不用创建对象
    static char Precede(char op1, char op2);//比较运算符优先级
    static double Operate(double a, char op, double b);//计算
    static void GetTwoOperands(Linkstack<double>& opnd, double& a, double& b);//从栈中取出两个操作数

public:
    Calculator() {};
    ~Calculator() {};
    void run();
};
bool Calculator::Operator(char op)
{
    switch (op)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '=':
        return true;
    default:
        return false;
    }
}
char Calculator::Precede(char op1, char op2)
{
    switch (op1)
    {
    case '+':
    case '-':
        switch (op2)
        {
        case '+':
        case '-':
        case ')':
        case '=':
            return '>';
        case '/':
        case '(':
        case '*':
            return '<';
        }
        break;
    case '*':
    case '/':
        switch (op2)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case ')':
        case '=':
            return '>';
        case '(':
            return '<';
        }
        break;
    case '(':
        switch (op2)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
            return '<';
        case ')':
            return '=';
        }
        break;
    case ')':
        switch (op2)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case ')':
        case '=':
            return '>';
        case '(':
            return 'E';
        }
        break;
    case '=':
        switch (op2)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
            return '<';
        case ')':
            return 'E';
        case '=':
            return '=';
        }
        break;
    }
}
double Calculator::Operate(double a, char op, double b)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}
void Calculator::GetTwoOperands(Linkstack<double>& opnd, double& a, double& b)
{
    opnd.Pop(b);
    opnd.Pop(a);
}
void Calculator::run()
{
    Linkstack<char> optr;
    Linkstack<double> opnd;
    char ch = '\0', e = '=';
    optr.Push('=');
    cin >> ch;
    while (ch != '=' || optr.GetTop(e) != '=')
    {
        
        if (!Operator(ch))
        {
            cin.putback(ch);//将ch放回输入流
            double x;
            cin >> x;
            opnd.Push(x);
            cin >> ch;
        }
        else
        {
            switch (Precede(optr.GetTop(e), ch))
            {

            case '<':
                optr.Push(ch);//如果e<ch,则将ch入栈
                cin >> ch;
                break;
            case '=':
                    optr.Pop(ch);//如果e=ch,则直接丢弃ch 只有（）才会出现这种情况
                    cin >> ch;
                    break;
            case '>':
                char op;
                optr.Pop(op);//将栈顶元素弹出 并进行计算 只有小于才会计算
                double a, b;
                GetTwoOperands(opnd, a, b);
                opnd.Push(Operate(a, op, b));
                break;
            case 'E':
                cout << "Error!" << endl;
                return;//出错，跳出函数
            }
        }
        
    }
    
    double m = 0;
    cout << opnd.GetTop(m) << endl;
}
