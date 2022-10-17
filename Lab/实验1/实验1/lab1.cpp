#include <iostream>
#include "Stack/Stack.hpp"
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

int cal(ch_Stack exp)
{
    int_Stack eval;
    eval.init();

    while(!exp.empty())
    {
        if (isdigit(exp.top()))
        {
            int x = 0;
            while(isdigit(exp.top()))
            {
                printf("exp : %c out \n",exp.top()); _sleep(1*500);
                auto c = exp.pop() - '0';
                x = x * 10 + c;
            }
            eval.push(x);
            printf("eval: %d in \n",eval.top()); _sleep(1*500);
            exp.pop();
        }
        else
        {
            int x;
            printf("eval: %d out \n",eval.top()); _sleep(1*500);
            auto a = eval.pop();
            printf("eval: %d out \n",eval.top()); _sleep(1*500);
            auto b = eval.pop();
            printf("exp : %c out \n",exp.top()); _sleep(1*500);
            auto c = exp.pop();

            if(c == '+') x = b + a;
            else if(c == '-') x = b - a;
            else if(c == '/') x = b / a;
            else if(c == '*') x = b * a;

            eval.push(x);
            printf("eval: %d in \n",eval.top()); _sleep(1*500);
            exp.pop();
        }
    }

    return eval.pop();
}

string w_and_r_txt()
{
    string str;

    fstream newfile;
    newfile.open("exp.txt",ios::out);  // open a file and operate
    if(newfile.is_open())   // test whether the file is open
    {
        string input;
        cin >> input;   // get the input_expression
        newfile << input;   // write in file
        newfile.close();    // close the file
    }

    newfile.open("exp.txt",ios::in);    // open file and read data
    if(newfile.is_open())
    {
        while(getline(newfile,str));    // copy data to str
    }
    newfile.close();

    return str; // Return expression
}

void Aexp()
{
    unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    ch_Stack exp;  // 储存数字以及初始获得的表达式
    ch_Stack sym;  // 储存符号
    ch_Stack r_exp;    // 储存后缀表达式
    // 初始化栈
    exp.init();
    sym.init();

    string str;
    str = w_and_r_txt();    // 读入 expression

    cout << "The process of stack changes:" << endl;
    for (int i = 0; i < str.size(); i ++)
    {
        auto c = str[i];

        if(isdigit(c))  // 如果是数字就保存
        {
            while(isdigit(str[i]))  // 考虑到不同位数的情况
            {
                exp.push(str[ i++ ]);
                cout << exp.top();
                _sleep(1*1000);
            }
            exp.push(' ');  // 用 ' ' 来分开不同数字以及符号
            i--;
        }
        else if (c == '(')
        {
            sym.push(c);
        }
        else if (c == ')')
        {
            while(sym.top() != '(')
            {
                exp.push(sym.pop());
                cout << exp.top();
                _sleep(1*1000);
                exp.push(' ');
            }
            sym.pop();
        }
        else 
        {
            char cc = c;
            if(!sym.empty())
                while(sym.top() != '(' && pr[sym.top()] > pr[cc])
                {
                    exp.push(sym.pop());
                    cout << exp.top();
                    _sleep(1*1000);
                    exp.push(' ');
                    cc = sym.pop();
                }
            sym.push(c);
        }
    }
    
    while(!sym.empty()) 
    {
        exp.push(sym.pop());
        cout << exp.top();
        _sleep(1*1000);
        exp.push(' ');
    }

    // exp.show();
    while(!exp.empty())
        r_exp.push(exp.pop());

    // r_exp.show();  //测试后缀表达式是否正确

    cout << "\nThe evaluation process of the expression:" << endl;
    cout << cal(r_exp) << endl;
}

int main()
{
    Aexp();

    system("pause");
    return 0;
}