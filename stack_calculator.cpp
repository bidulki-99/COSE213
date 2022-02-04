#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include "stack.h"

int icp(char op) {
    switch (op)
    {
    case '(':
        return 0;
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '+':
    case '-':
        return 3;
        break;
    case '#':
        return 8;
        break;
    default:
        break;
    }
}

int isp(char op) {
    switch (op)
    {
    case '(':
        return 8;
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '+':
    case '-':
        return 3;
        break;
    default:
        break;
    }
}

double Eval(char* in)
{
    Stack<double> opr; // stack for operands
    Stack<char> opt;   // stack for operators
    Stack<char> opt2;
    char post[100000] = { 0 };
    char* postfix;
    postfix = post;
    double out = 0;

    char buf[1000]; // temp buffer
    char lastToken = '#';

    double operand;
    int i = 0, bi = 0;

    opt.Push('#');

    if (in[0] == '-') {
        buf[bi++] = '-';
        i++;
    }

    while (in[i] != '\0')
    {
        char c = in[i];

        if (c == '0' || c == '1' ||
            c == '2' || c == '3' ||
            c == '4' || c == '5' ||
            c == '6' || c == '7' ||
            c == '8' || c == '9' ||
            c == '.')
        {
            buf[bi++] = c;
            if ((in[i + 1] >= '0' && in[i + 1] <= '9') || in[i + 1] == '.') {
                i++;
                continue;
            }

            operand = atof(buf);
            for (int z = 0; z < bi; z++) {
                *postfix++ = buf[z];
                buf[z] = 0;
            }
            *postfix++ = ' ';
            bi = 0;
            //std::cout << "New operand : " << operand << std::endl;
        }

        else if (c == ')') {
            for (; opt.Size() > 1 && opt.Top() != '('; opt.Pop()) {
                *postfix++ = opt.Top();
                *postfix++ = ' ';
                //std::cout << "New operator : " << opt.Top() << std::endl;
            }
            opt.Pop();
        }

        else {
            if (c == '-' &&
                (in[i - 1] == '+' || in[i - 1] == '-' || in[i - 1] == '*' || in[i - 1] == '/' || in[i - 1] == '(')) {
                buf[bi++] = c;
                i++;
                continue;
            }

            else if (c == '-' && in[i - 1] == ' ' &&
                (in[i - 2] == '+' || in[i - 2] == '-' || in[i - 2] == '*' || in[i - 2] == '/' || in[i - 2] == '(')) {
                buf[bi++] = c;
                i++;
                continue;
            }

            else if (c == '-' && in[i - 1] == ' ' && in[i - 2] == ' ') {
                i++;
                continue;
            }

            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(') {
                for (; opt.Size() > 1 && isp(opt.Top()) <= icp(c); opt.Pop()) {
                    //std::cout << "New operator : " << opt.Top() << std::endl;
                    *postfix++ = opt.Top();
                    *postfix++ = ' ';
                }
                opt.Push(c);
            }

            else {}
        }
        i++;
    }
    while (!opt.IsEmpty()) {
        //std::cout << "New operator : " << opt.Top() << std::endl;
        *postfix++ = opt.Top();
        *postfix++ = ' ';
        opt.Pop();
    }

    //std::cout << post << std::endl;
    double opr1;
    double opr2;
    double temp;

    char* ptr = strtok(post, " ");
    while (*ptr != '#') {
        if (!(strlen(ptr) == 1 && (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/')))
            opr.Push(atof(ptr));

        else {
            opt.Push(*ptr);

            opr1 = opr.Top();
            opr.Pop();
            opr2 = opr.Top();
            opr.Pop();

            switch (opt.Top()) {
            case '+':
                temp = opr2 + opr1;
                opr.Push(temp);
                break;

            case '-':
                temp = opr2 - opr1;
                opr.Push(temp);
                break;

            case '*':
                temp = opr2 * opr1;
                opr.Push(temp);
                break;

            case '/':
                temp = opr2 / opr1;
                opr.Push(temp);
                break;

            default:
                break;
            }
            opt.Pop();
        }
        ptr = strtok(NULL, " ");
    }
    out = opr.Top();
    return out;
}
