#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>

using namespace std;

const int N = 110;
const int INF = 0x3f3f3f3f;

typedef struct MatrixGraph{
    int edge[N][N];
    int n, e;
}MTG;

struct Edge{
    int a, b, w;

    bool operator < (const Edge W) const {
        return w < W.w ? true : false;
    };
}edge[N];

int q[N];
bool visited[N];

void creatMTG(MTG* G)
{
    int n, e, a, b, w;
    memset(G->edge, INF, sizeof G->edge);

    fstream fst1;
    fst1.open("E:/code/c++/hit_dts//vertex.txt");
    fstream fst2;
    fst2.open("E:/code/c++/hit_dts/edge.txt");

    fst1 >> n;
    fst1 >> e;
    G->n = n;
    G->e = e;


    while( fst2 >> a && fst2 >> b && fst2 >> w)
    {
        G->edge[a][b] = G->edge[b][a] = min(G->edge[a][b], w);
    }

}

// prim 算法求最小生成树
void prim(MTG G)
{
    /**
     * @brief prim算法求最小生成树算法简介：
     * 主要思想：设置两个集合：最小生成树集合及图集合，每次从图集合中选择�? 最小生成树集合 路径最短的顶点，并将其与最短边一同并入最小生成树集合�?
     * 点到集合的路径定义为：点�? 集合中顶点边集合中的最小边的权值�?
     * 
     * 数据定义�?
     * 1.lowcost[i] 记录�? i 到最小生成树集合的最短路�?
     * 2.costedge[i] = j 表示顶点 i 到最小生成树集合的最短边的另一个顶点为 j，j属于最小生成树集合
     * 3.cost 记录最小生成树的代�?
     * 4.st[i] 表示 i 是否以及并入最小生成树集合�?
     * 
     * 算法步骤�?
     * 1. 首先默认将编号为 1 的顶点并入， 并初始化lowcost �? costedge
     * 2. 循环 n-1 次：
     *      2.1 找到 待并顶点集合 中到 最小生成树集合 路径最短的顶点
     *      2.2 将其并入并记录cost
     *      2.3 更新 lowcost �? costedge
     */
    int lowcost[N];
    int costedge[N]; 
    int cost = 0;
    bool st[N];

    lowcost[1] = 0;

    for(int i = 2; i <= G.n; i ++)
    {
        lowcost[i] = G.edge[1][i];
        costedge[i] = 1;
    }
    
    int k; int min;
    for(int i = 2; i <= G.n; i ++)
    {
        min = INF;
        
        // 找到未并集合中到最小生成树集合的最短路径的顶点
        for(int j = 2; j <= G.n; j ++)
        {
            if(!st[j] && lowcost[j] < min)
            {
                k = j;
                min = lowcost[j];
            }
        }
        cout << '(' << k << ',' << costedge[k] << ',' << min << ')' << endl;
        cost += min;
        st[k] = true; // 将顶点k并入生成树集�?
        
        // 更新未并集合中顶点的lowcost �? costedge
        for(int j = 2; j <= G.n; j ++)
        {
            if(!st[j] && lowcost[j] > G.edge[k][j])
            {
                lowcost[j] = G.edge[k][j];
                costedge[j] = k;
            }
        }

    }
    cout << "total cost: " << cost;
}

int find(int a)
{
    if( q[a] != a) q[a] = find(q[a]);
    return q[a];
}

void loadedge(MTG* G)
{
    int n = G->n;

    int k = 0;
    for(int i = 1; i <= n; i ++)
        for(int j = i; j <= n; j ++)
        {
            if(G->edge[i][j] != INF)
            {
                edge[ k ].a = i;
                edge[ k ].b = j;
                edge[ k ].w = G->edge[i][j];
                k ++;
            }
        }
}

int kruskal(MTG G)
{
    loadedge(&G);

    sort(edge, edge + G.e);

    for(int i = 1; i <= G.n; i ++) q[i] = i;

    int res = 0, cnt = 0;
    for(int i = 0; i < G.e; i ++)
    {
        int a = edge[i].a, b = edge[i].b;
        int c = edge[i].w;

        a = find(a), b = find(b);
        if( a != b )
        {
            cout << '(' << a << ',' << b << ',' << c << ')' << endl;
            q[a] = b;
            res += c;
            cnt ++;
        }
    }

    if(cnt < G.n - 1) return INF;
    else return res;

}

void printMG(MTG* G)
{
    int n = G->n;

    for(int i = 1; i <= n; i ++)
    {
        if(i<10)
            cout << "\t[" << i << " ]";
        else 
              cout << "\t[" << i << ']';
    }

    cout <<'\n';    
    for(int i = 1; i <= n; i ++)
    {
        cout << '[' << i%10 << "]    ";
        for(int j = 1; j <= n; j ++)
        {
            if( G->edge[i][j] == INF )
                cout << "\tINF ";
            else 
                printf("\t%d  ", G->edge[i][j]);
        }
        cout << '\n';
    }
}

int main()
{
    MTG mg;

    creatMTG(&mg);
    printMG(&mg);

    cout << "Kruskal�㷨������С��������" << endl;
    int t = kruskal(mg);
    if( t == INF) puts("impossible");
    else cout << "total cost :" << t;

    cout << endl << "prim�㷨������С��������" << endl;
    prim(mg);

    system("pause");
    return 0;
}