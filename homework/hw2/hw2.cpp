#include <iostream>
#define MAX_SIZE 1010

using namespace std;

typedef struct Llist* Lnode;
typedef struct Slist* Snode;

// 链式链表
struct Llist{
    int val;
    Llist* ne = NULL;
};
// 顺序链表
struct Slist{
    int val[MAX_SIZE];
    int last = -1;
};

// 创建链表
Lnode creatLlist()
{
    Lnode head = new Llist;
    int num;
    cin >> num;
    Lnode p = head;
    while(num--)
    {   
        int input;
        cin >> input;

        p->ne = new Llist;
        p = p->ne;
        p->val = input;
    }

    return head;
}

Snode creatSlist()
{
    Snode s = new Slist;
    int num;
    cin >> num;

    while(num--)
    {
        int input;
        cin >> input;
        s->val[ ++s->last ] = input;
    }

    return s;
}

// 获取链式链表长度
int getLengh_Llist(Lnode head)
{   
    int len = 1;
    Lnode p = head;

    while (p->ne != NULL)
    {
        len ++;
        p = p->ne;
    } 

    return len;
}

// 链式链表删除指定元素
void del_speItem_Llist(Lnode head, int item)
{
    Lnode p = head->ne;

    while (p->val != item)
        p = p->ne;
    if (p == NULL)
        return ;
    else
    {
        Lnode p = head->ne;
        Lnode pre = head;

        while(p != NULL && p->val != item)
        {
            pre = pre->ne;
            p = p->ne;
        }
        if(p->val == item)
            pre->ne = p->ne;
    }
}

// 链式链表 删除已排好序的链表中的重复元素
void del_mulItem_Llist(Lnode head)
{
    if (!head->ne || !head->ne->ne) return;

    Lnode pre = head;
    Lnode p = pre->ne;

    while(p != NULL)
    {
        if (p->val == pre->val)
        {
            pre->ne = p->ne;
            p = p->ne;
        }
        else
        {
            p = p->ne;
            pre = pre->ne;
        }
    }

}

// 链式链表 逆置
void re_Llist(Lnode head)
{
    int val[MAX_SIZE];
    int tt = -1;

    Lnode p = head->ne;

    while(p != NULL)
    {
        val[ ++tt ] = p->val;
        p = p->ne;
    }

    p = head->ne;
    while( tt != -1)
    {
        p->val = val[tt--];
        p = p->ne;
    }
}

// 链式链表 左移
void move_left_Llist(Lnode head, int k)
{
    if (!head->ne) return ;

    int len = getLengh_Llist(head->ne);  // 得到链表长度
    Lnode p = head->ne;

    while(p->ne != NULL)
    {
        p = p->ne;
    }
    p->ne = head->ne;   //形成环形链表

    k %= len;   

    p = head->ne;   // 初始化指针头

    while( --k )
        p = p->ne;
    // 此时 p 指针指向位置为末位链表
    head->ne = p->ne;
    p->ne = NULL;
}

// 链式链表 右移
void move_right_Llist(Lnode head, int k)
{
    if (!head->ne) return ;

    int len = getLengh_Llist(head->ne);  // 得到链表长度

    move_left_Llist( head, len - k );
}

// 链式链表 合并两个已排好序的链表
Lnode merge_Llist(Lnode l1, Lnode l2)
{
    l1 = l1->ne;
    l2 = l2->ne;
    Lnode newhead = new Llist;
    Lnode p = newhead;

    while (l1 && l2)
    {
        if(l1->val < l2->val)
        {
            p->ne = l1;
            p = p->ne;
            l1 = l1->ne;
        }
        else 
        {
            p->ne = l2;
            p = p->ne;
            l2 = l2->ne;
        }
    }
    while(l1)
    {
        p->ne = l1;
        l1 = l1->ne;
    }
    while(l2)
    {
        p->ne = l2;
        l2 = l2->ne;
    }

    return newhead;
}

// 顺序表删除指定元素
void del_speItem_Slist(Slist* s, int k)
{   
    for (int i = 0; i <= s->last; i ++)
    {
        if(s->val[i] == k)
        {
            for(int j = i + 1; j <= s->last; j++)
                s->val[j - 1] = s->val[j];
            s->last--;
            i--;
        }
    }
}

// 对于已排好序的顺序表，删除重复元素
void del_mulItem_Slist(Slist* s)
{
    for(int i = 0; i + 1 <= s->last; i++ )
    {
        if(s->val[i] == s->val[ i + 1])
        {
            for(int j = i + 1; j <= s->last; j++ )
                s->val[ j - 1 ] = s->val[j];
            s->last--;
            i--;
        }
    }
}

// 顺序表逆置
void re_Slist(Slist* s)
{
    for(int i = 0, j = s->last; i < j; i++, j-- )
    {
        int temp = s->val[i];
        s->val[i] = s->val[j];
        s->val[j] = temp;
    }
}

// 顺序表左移
void move_left_Slist(Slist* s, int k)
{
    int newlast = -1;
    int i = s->last - k;
    s->last -= k;

    while( i >= 0 )
    {
        newlast ++;
        s->val[ newlast ] = s->val[ (newlast) + k];
        i--;
    }
}

// 顺序表右移
void move_right_Slist(Slist* s, int k)
{
    for(int i = s->last; i >= 0; i-- )
        s->val[i + k] = s->val[i];
    s->last += k;
}

// 合并两个已经排好序的线性表
Slist* merge_Slist(Slist* s1, Slist* s2)
{
    Slist* s = new Slist;
    int size1 = s1->last + 1, size2 = s2->last + 1;
    int i = 0, j = 0, k = 0;

    while(size1 && size2)
    {
        if(s1->val[i] < s2->val[j])
        {
            s->val[ k++ ] = s1->val[ i++ ];
            s->last++;
            size1--;
        }
        else 
        {
            s->val[ k++ ] = s2->val[ j++ ];
            s->last++;
            size2--;
        }
    }
    while(size1)
    {
        s->val[ k++ ] = s1->val[ i++ ];
         s->last++;
        size1--;
    }
    while(size2)
    {
        s->val[ k++ ] = s2->val[ j++ ];
        s->last++;
        size2--;
    }

    return s;
}

void print_Llist(Lnode head)
{
    Lnode p = head->ne;
    while(p != NULL)
    {
        cout << p->val;
        p = p->ne;
    }
    cout << endl;
}

void print_Slist(Snode s)
{
    for(int i = 0; i <= s->last; i++)
        cout << s->val[i];
    cout << endl;
}

// 测试 Llist 函数功能
void test_Llist()
{
    Lnode head = creatLlist();

    cout << "Init LinkedList:";
    print_Llist(head);

    cout << "Delete item 3:";
    del_speItem_Llist(head, 3);
    print_Llist(head);

    cout << "Delete repeat item:";
    del_mulItem_Llist(head);
    print_Llist(head);

    cout << "Re the Llist:";
    re_Llist(head);
    print_Llist(head);

    cout << "Move Llist right 2:";
    move_right_Llist(head, 2);
    print_Llist(head);

    cout << "Move Llist left 2:";
    move_left_Llist(head, 2);
    print_Llist(head);

    cout << "Merge two Llist:" << endl;
    Lnode head1 = creatLlist();
    head = merge_Llist(head, head1);
    print_Llist(head);

}

// 测试 SList 函数功能
void test_Slist()
{
    Snode s = creatSlist();

    cout << "Init SeqList:";
    print_Slist(s);

    cout << "Delete item 3:";
    del_speItem_Slist(s, 3);
    print_Slist(s);

    cout << "Delete repeat item:";
    del_mulItem_Slist(s);
    print_Slist(s);

    cout << "Re the Slist:";
    re_Slist(s);    
    print_Slist(s);

    // move_left_Slist(s, 2);
    // print_Slist(s);

    // move_right_Slist(s, 2);
    // print_Slist(s);

    cout << "Merge two Slist:" << endl;
    Snode s1 = creatSlist();
    s = merge_Slist(s, s1);
    print_Slist(s);
}

int main()
{
    // test_Llist();
    // system("cls");
    test_Slist();
    system("pause");
    return 0;
}