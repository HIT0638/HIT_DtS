#ifndef STACK_HPP
#define STACK_HPP
#define MAX_SIZE 1010

class ch_Stack{
    private: 
        char val[MAX_SIZE];
        int tt;
    public:
        void init();
        char pop();
        void push(char item);
        bool empty();
        char top();
        void show();
        int size();
};

class int_Stack{
    private: 
        int val[MAX_SIZE];
        int tt;
    public:
        void init();
        char pop();
        void push(int item);
        bool empty();
        char top();
        void show();
        int size();
};

#endif