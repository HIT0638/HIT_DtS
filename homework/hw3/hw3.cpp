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

// ���򴴽���
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

// �������
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

// ����ݹ����
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

// ����ǵݹ����
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

// �����ݹ����
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

// �����ǵݹ����
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

// ����ݹ����
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

// ����ǵݹ����
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
     * �ж��Ƿ���ȫ���������ؼ����������ҵ���һ�� �����͵㣨���Һ��ӷǶ����ڣ� ֮��Ĳ���
     * ���
     * 1.����һ���Ǳ��͵�ĺ������ �������Һ��� ��Ϊ��ȫ������
     * 2.�����ڵ�һ���Ǳ��ͽ��ĺ������ ��������Һ��� ��Ϊ����ȫ������
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
     * �Բ�Ϊһ��ѭ�����б���
     * ��¼�����ȣ����޸������
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
    cout << "���������" << endl;
    printTree(root); cout << endl;
    cout << "����ݹ������" << endl;
    pre_printTree(root); cout << endl;
    cout << "����ǵݹ������" << endl;
    pre_printTree_NR(root); cout << endl;
    cout << "����ݹ������" << endl;
    mid_printTree(root); cout << endl;
    cout << "����ǵݹ������" << endl;
    mid_printTree_NR(root); cout << endl;
    cout << "����ݹ������" << endl;
    bhd_printTree(root); cout << endl;
    cout << "����ǵݹ������" << endl;
    bhd_printTree_NR(root); cout << endl;
    cout << "�Ƿ�����ȫ��������" << endl;
    JudgeCBT(root);
    cout << "����������Ƕ��٣�" << endl;
    cout << maxWidth(root) << endl;

    system("pause");
    return 0;
}
