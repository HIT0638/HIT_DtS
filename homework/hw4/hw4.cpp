#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <queue>

using namespace std;

const int N = 110;
const int INF = 0x3f3f3f3f;

typedef struct MatrixGraph{
    string vertex[N]; // ���涥����Ϣ
    int edge[N][N]; // ��¼����֮��ߵ���Ϣ�Լ�Ȩֵ
    int n, e; // �ֱ��¼�������ͱ���
}MTG;

// �ڽӱ�ָ�뽨��
typedef struct node{
    int adjtex; // ��¼�����±�
    int cost; // ��¼Ȩֵ
    struct node * next; // ��¼��һ�� 
}edgeNode;

typedef struct {
    string vertex;
    edgeNode * firstedge;  // ��һ���ٽ�Ԫ��
    int vi; // ��¼���
    int vo; // ��¼����
    int vio; // ��¼��
}vertexNode;

typedef struct adjGraph{
    vertexNode vexList[N];
    int n, e;
}AG;

bool visited[N];  // ��ʾ�����Ƿ��Ѿ�����
int dfn[N]; // ��¼�����������
int cot; // ��¼�ѱ�������
queue<int> Q;

// �����ڽӱ�ͼ�ĳ����
    // ʱ�临�Ӷ� O( n + m )
void cal_io(AG* G)
{
    int n = G->n;

    for(int i = 1; i <= n; i ++)
    {
        edgeNode* p = G->vexList[i].firstedge;

        while(p)
        {
            G->vexList[i].vo ++;  // i ����ȼ�һ
            G->vexList[ p->adjtex ].vo ++; // ��ָ�����ȼ�һ
            p = p->next;
        }
    }

    for(int i = 1; i <= n; i ++)
        G->vexList[i].vio = G->vexList[i].vi + G->vexList[i].vo;
}

// ʱ�ո��Ӷ�
    // ʱ�临�Ӷȣ�O( n + e )
    // �ռ�ռ�������O( n^2 )
void createMTG(MTG* G)
{
    int n, m;
    scanf("%d%d", &n, &m);
    G->n = n;
    G->e = m;

    cout << "���������붥����Ϣ��";
    for(int i = 1; i <= n; i ++)
        scanf("%c ", &G->vertex[i]);

    memset(G->edge, 0x3f, sizeof G->edge);

    while( m-- )
    {
        cout << "���������붥���źͱ�Ȩֵ��";
        int a, b, c;
        scanf("%d%d%d\n", &a, &b, &c);

        G->edge[a][b] = G->edge[b][a] = min(G->edge[a][b], c);
    }

}

// ʱ�ո��Ӷ�
    // ʱ�临�Ӷȣ�O( n + e )
    // �ռ�ռ������� O( n + e )
void createAG(AG * G)
{
    cin >> G->n >> G->e;
    int n = G->n;
    int m = G->e;
    getchar();

    cout << "���������붥����Ϣ��";
    for(int i = 1; i <= n; i ++)
    {
        cin >> G->vexList[i].vertex;
        G->vexList[i].firstedge = NULL;
    }

    for(int i = 1; i <= m; i ++)
    {
        cout << "\n�������������������Լ���Ȩֵ��";
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
     * @brief ��Ҫ���Ƶ���Ϣ��
     * 1.������Ϣ
     * 2.����Ϣ
     * 3.��Ȩֵ
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

    // ������Ϣ����
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

    // ����������� �ݹ�ִ�к���
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

// ������������ǵݹ���ʽ �������� 
// �ж϶����Ƿ������������ڽӵ�
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

    // �ǵݹ�ִ�к���
void DFS(AG* G, int k)
{
     /**
     * @brief ��Ҫ�Ѷ����� ����ҵ� ��Ƕ�ס� ����
     * Ҳ�����ҹ��ɣ�������ɱ����ǳ���ģ�һ�㻯�ģ������������Ե�
     * �ҳ����Ĺ��ɱ�д��whileѭ����
     * 
     * �÷ǵݹ���������㷨�Ĺ��ɾ���
     * 1.����ÿ�� ��������˵ ��������������������ȱ��� �ڽӵ� : 
     * ��˵�����������֮�󣬽�����Ϊ �ѷ��� ����һ��Ӧ���ҵ�����һ��δ�����ʵ��ڽӵ�
     * ����ҵ�����������Ϊ�����㲢�ظ�����1
     * ��δ�ҵ������ջ����ʾ����Ϊ��ʼ��ĺ���������ѱ�����ɣ�
     * 
     * ���������н����������ݽṹ ջ ��������ȱ���·�ߵĻ������¼
     * 
     * �˹���ģ���� �ݹ� �ĵݹ���̣��ݹ鼴�ҵ��ݹ�ʱ
     * ���ڳ���ĵݹ飬�����ҵ����ɲ�����ѭ�������ҵ�һ�����ڲ�����ѭ��
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
// �ڽӱ������������
    // ʱ�临�Ӷȣ�O( n + e )
    // �ռ临�Ӷȣ�O( n )
void DFSTraverse(AG* G)
{
    int n = G->n;
    for(int i = 1; i <= n; i ++)
        visited[i] = false;

    for(int i = 1; i <= 1; i ++)
    {
        DFS_R(G, i);
        printf("�Զ��� %d Ϊ����������������Ķ���˳����Ϊ��\n", i);

        for(int j = 1; j <= n; j ++)
        {
            printf("���� %d �ı������Ϊ No.%d.\n", j, dfn[j]);
        }
    }
    cout << "��������Ϊ��";
    
    while(!Q.empty())
    {
        cout << Q.front() << ' ';
        Q.pop();
    }
    
}


    // ִ�к���
void BFS(AG* G, int k)
{
    queue<int> q;
    Q.push(k);  // �������м�¼
    q.push(k);  // ���м�¼

    edgeNode* p;
    visited[k] = true;  // ���Ϊ�ѷ���
    dfn[k] = ++cot; // �����ż�¼

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
                dfn[b] = ++cot;  // �����ż�¼
            }
            p = p->next;
        }
    }
}

// �����������
    // ʱ�临�Ӷȣ� O( n + e)
    // �ռ临�Ӷȣ� O( n )
void BFSTraverse(AG* G)
{
    int n = G->n;
    for(int i = 1; i <= n; i ++)
        visited[i] = false;
    
    for(int i = 1; i <= 1; i ++)
    {
        BFS(G, i);

        printf("�Զ��� %d Ϊ���Ĺ�����������Ķ���˳����Ϊ��\n", i);

        for(int j = 1; j <= n; j ++)
        {
            printf("���� %d �ı������Ϊ No.%d.\n", j, dfn[j]);
        }
    }
    cout << "��������Ϊ��";
    
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