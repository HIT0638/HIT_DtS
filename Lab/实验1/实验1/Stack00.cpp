#include <iostream>
#include "Stack.h"
using namespace std;

// AC : Functions of char_type Stack
void ch_Stack::init()
{
    tt = -1;
}
char ch_Stack::pop()
{
    return empty() ? 0:val[tt--];
}
void ch_Stack::push(char item)
{
    val[ ++tt ] = item;
}
bool ch_Stack::empty()
{
    return tt<0 ? true:false;
}
char ch_Stack::top()
{
    return val[tt];
}
void ch_Stack::show()
{
    while (!empty()) 
        cout << val[ tt-- ];
}
int ch_Stack::size()
{
    return tt + 1;
}


// AC : Functions of int_type Stack
void int_Stack::init()
{
    tt = -1;
}
char int_Stack::pop()
{
    return empty() ? 0:val[tt--];
}
void int_Stack::push(int item)
{
    val[ ++tt ] = item;
}
bool int_Stack::empty()
{
    return tt<0 ? true:false;
}
char int_Stack::top()
{
    return val[tt];
}
void int_Stack::show()
{
    while (!empty()) 
        cout << val[ tt-- ];
}
int int_Stack::size()
{
    return tt + 1;
}
