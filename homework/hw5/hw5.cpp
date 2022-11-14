#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

const int N = 3010;

typedef struct celltype{
    int key;
    struct celltype* lchild, *rchild;
}BSTNode;

typedef BSTNode* BST;

int q1[N], q2[N];  // 辅助数组
int s[N];
double sum = 0.0;
int c = 0;

void InsertBST(BST &T, int k)
{
    if(T == NULL)
    {
        T = new BSTNode;
        T->key = k;
        T->lchild = T->rchild = NULL;
    }
    else if(k < T->key)
        InsertBST(T->lchild, k);
    else
        InsertBST(T->rchild, k);
}

void BST_p(BST T)
{
    if(T==NULL)
        return;
    else
    {
        BST_p(T->lchild);
        s[++c] = T->key;
        BST_p(T->rchild);
    }
}

BST CreateBST()
{
    BST F = NULL;
    int k;
    cin >> k;

    while(k)
    {
        InsertBST(F, k);
        cin >> k;
    }

    return F;
}

BST CreateBST(int a[], int n)
{
    BST F = NULL;

    for(int i = 1; i <= n; i ++)
        InsertBST(F, a[i]);

    return F;
}

BST SearchBST(BST T, int k)
{
    BST p = T;

    while( p != NULL && k != p->key)
    {
        if(k < p->key)
            p = p->lchild;
        else 
            p = p->rchild;
    }

    return p;
}

int delmin(BST &T)
{
    /**
     * @brief 删除某树的最小结点并返回其值，即删除左子树的最左结点，并右链继??
     * 
     */
    int tmp;
    BST p;
    if(T->lchild == NULL)
    {
        p = T;
        tmp = p->key;
        T = T->rchild;
        delete(p);

        return tmp;
    }
    else
        return delmin(T->lchild);

}

void DelBST(BST &T, int k)
{
    /**
     * @brief 删除二叉查找树某一结点总共有三种情??
     * 1.若待删除结点左孩子为 NULL?? 则直接右链继??
     * 2.若待删除结点右孩子为 NULL?? 则直接左链继??
     * 3.若待删除结点左右孩子均存在， 则用结点的后继结点来替换当前结点
     * 
     * pos：某结点的后继结点为结点右子树的最左结点，即右子树的最小结??
     */
    if(T != NULL)
        if(k < T->key)
            DelBST(T->lchild, k);
        else if(k > T->key)
            DelBST(T->rchild, k);
        else  
            if(T->lchild == NULL)
                T = T->rchild;
            else if(T->rchild == NULL)
                T = T->lchild;
            else   
                T->key = delmin(T->rchild);

}

int BinaryS1(int a[], int key, int n)
{
    int low = 1, high = n;
    int mid;

    while(low <= high)
    {
        mid = (low + high) >> 1;
        if(a[mid] == key)
            return mid;
        else if(a[mid] < key)
            low = mid + 1;
        else 
            high = mid - 1;
    }

    return 0;
}

int BinaryS2(int a[], int low, int high, int k)
{
    if(low > high) return 0;

    int mid = (low + high) >> 1;

    if(a[mid] == k) 
        return mid;
    else if(a[mid] < k)
        return BinaryS2(a, mid + 1, high, k);
    else 
        return BinaryS2(a, low, mid - 1, k);
}

void readtxt()
{
    string file = "record.txt";

    fstream f;
    f.open(file, ios::out);

    f << "q2:";
    for(int i = 1; i <= 1024; i ++)
    {
        f << q2[i] << '\n';
    }
}

double AST_BST(BST T, int t)
{
    if(T == NULL)
        return 0;
    else
    {
        sum += t;
        AST_BST(T->lchild, ++t);
        AST_BST(T->rchild, t++);
    }

    return sum;
}

double AST_BST_f(BST T, int t)
{
    if(T == NULL)
        sum += t-1;
    else
    {
        AST_BST_f(T->lchild, ++t);
        AST_BST_f(T->rchild, t++);
    }
    return sum;
}

double AST_BS(int low, int high, int t)
{
    if(low > high)
        return 0;
    else
    {
        int mid = (low + high) >> 1;
        sum += t;
        AST_BS(mid + 1, high, ++t);
        AST_BS(low, mid - 1, t++);
    }
    
    return sum;
}

double AST_BS_f(int low, int high, int t)
{
    if(low > high)
    {
        sum += t-1;
        return 0;
    }
    else
    {
        int mid = (low + high) >> 1;
        AST_BS(mid + 1, high, ++t);
        AST_BS(low, mid - 1, t++);
    }
    
    return sum;
}


int main()
{
    for(int i = 1, j = 1; i < 2048; i += 2)
    {
        q1[j] = i;
        q2[j++] = i;
    }
    
    random_shuffle(q2+1, q2+1024);

    readtxt();

    BST T1 = CreateBST(q1, 1024);
    BST T2 = CreateBST(q2, 1024);

    // AST_BST(T1, 1);
    cout << AST_BST(T1, 1) / 1024<< endl;
    sum = 0;
    cout << AST_BST(T2, 1) / 1024<< endl;

    cout << AST_BST_f(T1, 1) / 1025 << endl;
    sum = 0;
    cout << AST_BST_f(T2, 1) / 1025 << endl;
    sum = 0;
    
    cout << AST_BS(1, 1024, 1) / 1024 << endl;
    sum = 0;
    cout << AST_BS_f(1, 1024, 1) / 1025 << endl;
    sum = 0;

    BST_p(T2);
    cout << '\n' << "排序后的数组：" << endl;
    for(int i = 1; i <= 1024; i ++)
        cout << s[i] << ' ';

    system("pause");
    return 0;
}