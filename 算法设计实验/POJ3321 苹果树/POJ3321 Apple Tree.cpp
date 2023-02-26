// POJ3321 苹果树.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#define MAXN 100005
#define lowbit(x) ((x) & (-x))
using namespace std;
int N;    //N<=100000
int M;    //M<=100000
int cnt;
int tree[MAXN],from[MAXN],to[MAXN],ans[MAXN];
bool visited[MAXN],apple[MAXN];//apple保存节点上有没有苹果，visited用于dfs
//vector <int >  v[MAXN];
typedef vector<int >  INT;   
vector<INT>  v(MAXN);
void update(int  tree[], int i, int x)
{
    for (int pos = i; pos < MAXN; pos += lowbit(pos))
        tree[pos] += x;
}

int  query(int  tree[], int n)
{
    int  ans = 0;
    for (int pos = n; pos; pos -= lowbit(pos))
        ans += tree[pos];
    return ans;
}

int  query(int  tree[], int i, int j)
{
    return query(tree, j ) - query(tree, i-1);
}

void dfs(int cur) {
    from[cur] = ++cnt; 
    visited[cur] = true;
    for (int i = 0; i < v[cur].size(); i++) {
        int u = v[cur][i];
        if (!visited[u])
            dfs(u);
    }
    to[cur] = cnt;
    return;
}

int main()
{
    //首先用dfs将子树用区间映射，之后用树状数组输出结果
    int a, b,num=0;
    char  op;
    scanf("%d", &N);
    for (int i = 0; i < N - 1; i++) {
        scanf("%d%d", &a, &b);
        v[a].push_back(b);
        v[b].push_back(a);
    }
    memset(from, 0, MAXN);
    memset(to, 0, MAXN);
    memset(visited, false, MAXN);
    memset(apple, true, MAXN);
    dfs(1);
    for (int i = 1; i <= N; i++)
    {
        update(tree, from[i], 1);
    }
    scanf("%d", &M);
    for (int i = 1; i <= M; i++)
    {
        getchar();
        scanf("%c", &op);
        if (op== 'Q') 
        {
            scanf("%d", &a);
            ans[num++] = query(tree, from[a], to[a]);
        }
        else 
        {
            scanf("%d", &a);
            if (apple[from[a]])
            {
                apple[from[a]] = false;
                update(tree, from[a], -1);
            }
            else
            {
                apple[from[a]] = true;
                update(tree, from[a], 1);
            }
        }
    }
    for (int i = 0; i < num; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}



