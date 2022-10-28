#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <queue>

using namespace std;

const int N = 110;
const int INF = 0x3f3f3f3f;

typedef struct MatrixGraph{
    string vertex[N]; // 储存顶点信息
    int edge[N][N]; // 记录顶点之间边的信息以及权值
    int n, e; // 分别记录顶点数和边数
}MTG;

// 邻接表指针建立
typedef struct node{
    int adjtex; // 记录顶点下标
    int cost; // 记录权值
    struct node * next; // 记录下一个 
}edgeNode;

typedef struct {
    string vertex;
    edgeNode * firstedge;  // 第一个临街元素
    int vi; // 记录入度
    int vo; // 记录出度
    int vio; // 记录度
}vertexNode;

typedef struct adjGraph{
    vertexNode vexList[N];
    int n, e;
}AG;

bool visited[N];  // 表示顶点是否已经遍历
int dfn[N]; // 记录顶点的先深编号
int cot; // 记录已遍历个数
queue<int> Q;

// 计算邻接表图的出入度
    // 时间复杂度 O( n + m )
void cal_io(AG* G)
{
    int n = G->n;

    for(int i = 1; i <= n; i ++)
    {
        edgeNode* p = G->vexList[i].firstedge;

        while(p)
        {
            G->vexList[i].vo ++;  // i 点出度加一
            G->vexList[ p->adjtex ].vo ++; // 被指向点入度加一
            p = p->next;
        }
    }

    for(int i = 1; i <= n; i ++)
        G->vexList[i].vio = G->vexList[i].vi + G->vexList[i].vo;
}

// 时空复杂度
    // 时间复杂度：O( n + e )
    // 空间占用情况：O( n^2 )
void createMTG(MTG* G)
{
    int n, m;
    scanf("%d%d", &n, &m);
    G->n = n;
    G->e = m;

    cout << "请依次输入顶点信息：";
    for(int i = 1; i <= n; i ++)
        scanf("%c ", &G->vertex[i]);

    memset(G->edge, 0x3f, sizeof G->edge);

    while( m-- )
    {
        cout << "请依次输入顶点编号和边权值：";
        int a, b, c;
        scanf("%d%d%d\n", &a, &b, &c);

        G->edge[a][b] = G->edge[b][a] = min(G->edge[a][b], c);
    }

}

// 时空复杂度
    // 时间复杂度：O( n + e )
    // 空间占用情况： O( n + e )
void createAG(AG * G)
{
    cin >> G->n >> G->e;
    int n = G->n;
    int m = G->e;
    getchar();

    cout << "请依次输入顶点信息：";
    for(int i = 1; i <= n; i ++)
    {
        cin >> G->vexList[i].vertex;
        G->vexList[i].firstedge = NULL;
    }

    for(int i = 1; i <= m; i ++)
    {
        cout << "\n请依次输入两个顶点以及边权值：";
        int a, b, c;
        cin >> a >> b >> c;

        edgeNode* p = new edgeNode;
        p->adjtex = b;
        p->cost = c;
        p->next = G->vexList[a].firstedge;
        G->vexList[a].firstedge = p;
    }

    cal_io(G);
}

MTG* AG2MTG(AG* ag)
{
    /**
     * @brief 需要复制的信息有
     * 1.顶点信息
     * 2.边信息
     * 3.边权值
     * 
     */
    MTG* G;
    
    int n = ag->n;
    int m = ag->e;

    memset(G->edge, 0x3f, sizeof G->edge);

    for(int i = 1; i <= n; i ++)
    {
        G->vertex[i] = ag->vexList[i].vertex;

        edgeNode* p = ag->vexList[i].firstedge;

        while(p)
        {
            int b = p->adjtex;
            int c = p->cost;
            G->edge[i][b] = c;
            p = p->next;
        }
    }

    return G;
}

AG* MTG2AG(MTG* mg)
{
    AG* G;

    int n = mg->n;
    int m = mg->e;

    // 顶点信息复制
    for(int i = 1; i <= n; i ++)
        G->vexList[i].vertex = mg->vertex[i];
    
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            {
                if(mg->edge[i][j] != 0x3f)
                {
                    int c = mg->edge[i][j];
                    edgeNode* p = new edgeNode;
                    p->adjtex = j;
                    p->cost = c;
                    p->next = G->vexList[i].firstedge;
                    G->vexList[i].firstedge = p;
                }
            }

    return G;
}

    // 深度优先搜索 递归执行函数
void DFS_R(AG* G, int k)
{
    Q.push(k);
    visited[k] = true;
    dfn[k] = ++cot;
    edgeNode* p = G->vexList[k].firstedge;

    while(p)
    {
        if(!visited[p->adjtex])
            DFS_R(G, p->adjtex);
        p = p->next;
    }
}

// 深度优先搜索非递归形式 辅助函数 
// 判断顶点是否遍历完成所有邻接点
bool isDone(AG* G, int i)
{
    edgeNode* p;

    p = G->vexList[i].firstedge;

    while(p)
    {
        if(!visited[p->adjtex])
            return false;
        p = p->next;
    }

    return true;
}

    // 非递归执行函数
void DFS(AG* G, int k)
{
     /**
     * @brief 主要难度在于 如何找到 “嵌套” 部分
     * 也就是找规律，这个规律必须是抽象的，一般化的，而且是周期性的
     * 找出来的规律边写入while循环中
     * 
     * 该非递归深度优先算法的规律就是
     * 1.对于每个 主顶点来说 它的任务是依次深度优先遍历 邻接点 : 
     * 因此当设置主顶点之后，将其标记为 已访问 后，下一步应该找到它的一个未被访问的邻接点
     * 如果找到，则将它设置为主顶点并重复步骤1
     * 若未找到，则出栈（表示以它为起始点的后续顶点均已遍历完成）
     * 
     * 整个过程中借助抽象数据结构 栈 来进行深度遍历路线的回溯与记录
     * 
     * 此过程模仿了 递归 的递归过程，递归即找到递归时
     * 对于抽象的递归，则是找到规律并加以循环，即找到一个周期并加以循环
     * 
     */
    stack<int> stk;

    visited[k] = 1;
    dfn[k] = ++cot;
    Q.push(k);

    stk.push(k);

    while(!stk.empty())
    {   
        int t = stk.top();

        edgeNode* p = G->vexList[t].firstedge;

        while(p && visited[ p->adjtex ])
        {
            p = p->next;
        }

        if(p)
        {
            int a = p->adjtex;
            stk.push(a);
            visited[a] = 1;
            dfn[ a ] = ++cot;
            Q.push( a );
        }

        if(isDone(G, stk.top()))
            stk.pop();   
    }
    
}
// 邻接表深度优先搜索
    // 时间复杂度：O( n + e )
    // 空间复杂度：O( n )
void DFSTraverse(AG* G)
{
    int n = G->n;
    for(int i = 1; i <= n; i ++)
        visited[i] = false;

    for(int i = 1; i <= 1; i ++)
    {
        DFS_R(G, i);
        printf("以顶点 %d 为起点的深度优先搜索的顶点顺序编号为：\n", i);

        for(int j = 1; j <= n; j ++)
        {
            printf("顶点 %d 的遍历编号为 No.%d.\n", j, dfn[j]);
        }
    }
    cout << "遍历序列为：";
    
    while(!Q.empty())
    {
        cout << Q.front() << ' ';
        Q.pop();
    }
    
}


    // 执行函数
void BFS(AG* G, int k)
{
    queue<int> q;
    Q.push(k);  // 搜索序列记录
    q.push(k);  // 队列记录

    edgeNode* p;
    visited[k] = true;  // 标记为已访问
    dfn[k] = ++cot; // 顶点编号记录

    while(!q.empty())
    {
        int t = q.front();
        q.pop();

        p = G->vexList[t].firstedge;

        while(p)
        {
            int b = p->adjtex;
            if(!visited[b])
            {
                q.push(b);
                visited[b] = true;
                Q.push(b);
                dfn[b] = ++cot;  // 顶点编号记录
            }
            p = p->next;
        }
    }
}

// 广度优先搜索
    // 时间复杂度： O( n + e)
    // 空间复杂度： O( n )
void BFSTraverse(AG* G)
{
    int n = G->n;
    for(int i = 1; i <= n; i ++)
        visited[i] = false;
    
    for(int i = 1; i <= 1; i ++)
    {
        BFS(G, i);

        printf("以顶点 %d 为起点的广度优先搜索的顶点顺序编号为：\n", i);

        for(int j = 1; j <= n; j ++)
        {
            printf("顶点 %d 的遍历编号为 No.%d.\n", j, dfn[j]);
        }
    }
    cout << "遍历序列为：";
    
    while(!Q.empty())
    {
        cout << Q.front() << ' ';
        Q.pop();
    }
}

int main()
{
    AG ag;
    createAG(&ag);

    DFSTraverse(&ag);
    // BFSTraverse(&ag);

    system("pause");
    return 0;
}