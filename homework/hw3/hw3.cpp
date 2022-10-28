#include <iostream>
#include <queue>
#include <vector>
#include "E:\code\c++\hit_dts\tree\Tree.h"

#define MAX_SIZE 1010

using namespace std;

const int N = 1010;

typedef struct Btree Tnode;

struct Btree{
int val;
Tnode* lchild;
Tnode* rchild;
};

void setVal(Tnode* root,int num)
{
    if(root) root->val = num;
}

Tnode* initTree(int data)
{
    Tnode* root;
    setVal(root, data);

    return root;
}

// 先序创建树
Tnode* createTree()
{
    int value;
    cin >> value;

    Tnode* p;
    if(value == -1)
        p = NULL;
    else
    {
        p = new Tnode;
        setVal(p, value);
        p->lchild = createTree();
        p->rchild = createTree();
    }

    return p;
}

// 层序遍历
void printTree(Tnode* root)
{
    Tnode* p;
    queue<Tnode*> Q;

    Q.push(root);

    while(!Q.empty())
    {
        p = Q.front();
        cout << p->val << ' ';
        Q.pop();

        if(p->lchild != NULL)
            Q.push(p->lchild);
        if(p->rchild != NULL)
            Q.push(p->rchild);

    }
}

// 先序递归遍历
void pre_printTree(Tnode* root)
{
    Tnode* p = root;
    if (p)
    {
        cout << p->val << ' ';
        pre_printTree(p->lchild);
        pre_printTree(p->rchild);
    }
}

// 先序非递归遍历
void pre_printTree_NR(Tnode* root)
{
    struct Btree* s[MAX_SIZE];
    int top = -1;

    Tnode* p = root;

    while(p != NULL || top != -1)
    {
        while(p != NULL)  
        {
            cout << p->val << ' ';
            s[ ++top ] = p;
            p = p->lchild;
        }
        if(top != -1)
        {
            p = s[ top-- ];
            p = p->rchild;
        }
    }
}

// 后续递归遍历
void bhd_printTree(Tnode* root)
{
    Tnode* p = root;
    if(p)
    {
            bhd_printTree(p->lchild);
            bhd_printTree(p->rchild);
            cout << p->val << ' ';
    }

}

// 后续非递归遍历
void bhd_printTree_NR(Tnode* root)
{
    struct st{
        Tnode* node;
        int flag;
    };
    st s[MAX_SIZE];
    int top = -1;

    Tnode* p = root;

    while(p != NULL || top != -1)
    {
        while(p != NULL)
        {
            s[ ++top ].node = p;
            s[top].flag = 1;
            p = p->lchild;
        }
        while(top != -1 && s[top].flag == 2)
        {
            p = s[ top-- ].node;
            cout << p->val << ' ';
        }
        if(top != -1)
        {
            s[top].flag = 2;
            p = s[top].node;
            p = p->rchild;
        }
        if(top == -1)
            break;

    }
}

// 中序递归遍历
void mid_printTree(Tnode* root)
{
    Tnode* p = root;
    if(p)
    {
            mid_printTree(p->lchild);
            cout << p->val << ' ';
            mid_printTree(p->rchild);
        
    }
}

// 中序非递归遍历
void mid_printTree_NR(Tnode* root)
{
    struct Btree* s[MAX_SIZE];
    int top = -1;
    Tnode* p = root;

    while(p != NULL || top != -1)
    {
        while(p != NULL)
        {
            s[ ++top ] = p;
            p = p->lchild;
        }
        if(top != -1)
        {
            p = s[ top-- ];
            cout << p->val << ' ';
            p = p->rchild;
        }
    }
}

void JudgeCBT(Tnode* root)
{
    /**
     * @brief 
     * 判断是否完全二叉树，关键在于依次找到第一个 不饱和点（左右孩子非都存在） 之后的操作
     * 因此
     * 1.若第一个非饱和点的后续结点 均无左右孩子 则为完全二叉树
     * 2.若存在第一个非饱和结点的后续结点 存在左或右孩子 则为非完全二叉树
     */
    Tnode* Q[N];
    int head = 0;
    int base = 0;

    Tnode* p;
    Q[head++] = root;

    while(head - base > 0)
    {
        p = Q[base++];
        if(p->lchild && p->rchild)
        {
            Q[head++] = p->lchild;
            Q[head++] = p->rchild; 
        }
        else
        {
            if(p->lchild)
            {
                Q[head++] = p->lchild;
                if(p->rchild)
                Q[head++] = p->rchild;
            }
            
            while(head - base > 0)
            {
                p = Q[base++];
                if(p->lchild != NULL || p->rchild != NULL)
                {
                    std::cout << "Not CBT!" << std::endl;
                    return ;
                }
            }
        }
    }

    std::cout << "Is CBT!" << std::endl;
}

int maxWidth(Tnode* root)
{
    /**
     * @brief 
     * 以层为一个循环进行遍历
     * 记录各层宽度，并修改最大宽度
     * 
     */
    int max = 0;
    int tW;

    std::queue<Tnode*> Q;

    Tnode* p;
    Q.push(root);

    while(!Q.empty())
    {
        int tw = Q.size();
        max = max > tw ? max : tw;

        for(int i = 0; i < tw; i++)
        {
            p = Q.front();
            Q.pop();
            if(p->lchild) 
                Q.push(p->lchild);
            if(p->rchild)
                Q.push(p->rchild);
        }
    }

    return max;
}

int main()
{
    Tnode* root;

    root = createTree();
    cout << "层序遍历：" << endl;
    printTree(root); cout << endl;
    cout << "先序递归遍历：" << endl;
    pre_printTree(root); cout << endl;
    cout << "先序非递归遍历：" << endl;
    pre_printTree_NR(root); cout << endl;
    cout << "中序递归遍历：" << endl;
    mid_printTree(root); cout << endl;
    cout << "中序非递归遍历：" << endl;
    mid_printTree_NR(root); cout << endl;
    cout << "后序递归遍历：" << endl;
    bhd_printTree(root); cout << endl;
    cout << "后序非递归遍历：" << endl;
    bhd_printTree_NR(root); cout << endl;
    cout << "是否是完全二叉树？" << endl;
    JudgeCBT(root);
    cout << "树的最大宽度是多少？" << endl;
    cout << maxWidth(root) << endl;

    system("pause");
    return 0;
}
