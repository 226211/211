#pragma once
#include <iostream>
#include<stdlib.h>
using namespace std;
#include "LinkStack.h"
class Calculator
{
private:
    static bool Operator(char op);//�ж��ַ��Ƿ�Ϊ�����,����Ϊ��̬������������ ����ֱ�ӵ��ö����ô�������
    static char Precede(char op1, char op2);//�Ƚ���������ȼ�
    static double Operate(double a, char op, double b);//����
    static void GetTwoOperands(Linkstack<double>& opnd, double& a, double& b);//��ջ��ȡ������������

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
    case '[':
    case ']':
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
        case ']':
            return '>';
        case '/':
        case '(':
        case '*':
        case '[':
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
        case ']':
            return '>';
        case '(':
        case '[':
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
        case ']':
            return '>';
        case '(':
            return 'E';
        
        }
        break;
    case '[':
        switch (op2)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case '[':
            return '<';
        case ')':
            return 'E';
        case '=':
        case ']':
            return '=';
        }
        break;
    case ']':
        switch (op2)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case ')':
        case '=':
        case ']':
            return '>';
        case '(':
        case '[':
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
        case '[':
            return '<';
        case ')':
        case ']':
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
    if(ch=='-')
    {
        double x;
        cin >> x;
        opnd.Push(-x);
        cin >> ch;
    }
    while (ch != '=' || optr.GetTop(e) != '=')
    {
        
        
        if (!Operator(ch))
        {
            if(ch>='0'&&ch<='9')
            {
            cin.putback(ch);//��ch�Ż�������
            double x;
            cin >> x;
            opnd.Push(x);
            cin >> ch;
            if(ch == '!')
            {
                double y = 1;
                for(int i = 1; i <= x; i++)
                {
                    y = y * i;
                }
                opnd.Pop(x);
                opnd.Push(y);
                cin >> ch;
            }
            else if(ch== '(')//���ֺ��治�ܸ�����
            {
                cout << "Error!" << endl;
                return;
            }
            }
            else
            {
                cout << "Error!" << endl;
                return;
            }
            
        }
        else
        {
            switch (Precede(optr.GetTop(e), ch))
            {

            case '<':
                optr.Push(ch);//���e<ch,��ch��ջ
                cin >> ch;
                break;
            case '=':
                    optr.Pop(ch);//���e=ch,��ֱ�Ӷ���ch ֻ�У����Ż�����������
                    cin >> ch;
                    break;
            case '>':
                char op;
                optr.Pop(op);//��ջ��Ԫ�ص��� �����м��� ֻ��С�ڲŻ����
                double a, b;
                GetTwoOperands(opnd, a, b);
                opnd.Push(Operate(a, op, b));
                    break;
            case 'E':
                cout << "Error!" << endl;
                return;//������������
            }
            if(Operator(ch)&&ch!='=')
            {
                switch (ch)
                {
                case '(':
                    switch(optr.GetTop(e))
                    {
                        case '[':
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '=':
                            break;
                        default:
                            cout << "Error!" << endl;
                            return;
                    }
                    break;
                case '[':   
                    switch(optr.GetTop(e))
                    {
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '=':
                            break;
                        default:
                            cout << "Error!" << endl;
                            return;
                    }
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                    if(optr.GetTop(e) == '(' || optr.GetTop(e) == '['||optr.GetTop(e) == '=')
                    {
                        break;
                    }
                    else
                    {
                        cout << "Error!" << endl;
                        return;
                    }
                    break;
                case ')':
                    switch(optr.GetTop(e))
                    {
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '(':
                            break;
                        default:
                            cout << "Error!" << endl;
                            return;
                    }
                    break;
                case ']':
                    switch(optr.GetTop(e))
                    {
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '[':
                            break;
                        default:
                            cout << "Error!" << endl;
                            return;
                    }
                    break;
                default:
                        cout << "Error!" << endl;
                        return;
                }
            }
        }
        
    }
    
    double m = 0;
    cout << opnd.GetTop(m) << endl;
}
