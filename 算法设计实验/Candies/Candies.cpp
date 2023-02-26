// Candies.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#include<stack>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
stack<int>que;
int a[150010], to[150010], p[150010], val[150010], tot;
int dis[150010];
int n, m;
bool b[150010];
inline void add(int x, int y, int z)
{
    tot++; a[tot] = y; to[tot] = p[x]; p[x] = tot;
    val[tot] = z;
    return;
}

inline void spfa(int s, int e)
{
    memset(dis, 127 / 3, sizeof(dis));
    memset(b, true, sizeof(b));
    que.push(s);  b[s] = false;
    dis[s] = 0;
    while (!que.empty())
    {
        int u, v;
        u = que.top(); que.pop();
        v = p[u]; b[u] = true;
        while (v)
        {
            if (dis[a[v]] > dis[u] + val[v])
            {
                dis[a[v]] = dis[u] + val[v];
                if (b[a[v]])
                {
                    b[a[v]] = false;
                    que.push(a[v]);
                }
            }
            v = to[v];
        }
    }
    printf("%d\n", dis[e]);
    return;
}

int main()
{
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }
    spfa(1, n);
    return 0;
}