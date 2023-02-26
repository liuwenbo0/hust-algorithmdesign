// Count Color.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#define ls u << 1
#define rs u << 1 | 1
using namespace std;
const int N = 100010;

struct Node {
    int l, r;
    int add, sum;
} color[N << 2];

void pushup(int u)
{
    color[u].sum = color[ls].sum | color[rs].sum; 
}
void pushdown(int u) 
{
    if (color[u].add) {                         
        color[ls].add = color[rs].add = color[u].add; 
        color[ls].sum = color[rs].sum = color[u].add; 
        color[u].add = 0;                       
    }
}
void build(int u, int l, int r) 
{
    color[u].l = l;
    color[u].r = r;
    if (l == r) 
    {
        color[u].sum = 1; 
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
unsigned int __builtin_popcount(int u)
{
    u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
    u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
    u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
    u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
    u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
    return u;
}
void modify(int u, int l, int r, int v) 
{
    if (l <= color[u].l && color[u].r <= r) 
    { 
        color[u].add = 1 << (v - 1);
        color[u].sum = 1 << (v - 1);
        return;
    }
    int mid = (color[u].l + color[u].r) >> 1;      
    pushdown(u);                              
    if (l <= mid) modify(u << 1, l, r, v);    
    if (r > mid) modify(u << 1 | 1, l, r, v); 
    pushup(u);                                
}

int query(int u, int l, int r) 
{
    if (l > color[u].r || r < color[u].l) return 0;
    if (l <= color[u].l && color[u].r <= r) return color[u].sum;
    pushdown(u); 
    return query(ls, l, r) | query(rs, l, r);
}

int main() 
{
    int n, t, m;
    char op[2];
    scanf("%d%d%d", &n, &t, &m);
    build(1, 1, n);
    for (int i = 0; i < m; i++) 
    {
        int l, r;
        scanf("%s%d%d", op, &l, &r);
        if (l > r) swap(l, r); 
        if (op[0] == 'C') 
        {
            int v;
            scanf("%d", &v);
            modify(1, l, r, v);
        }
        else 
        {
            int ans = query(1, l, r);
            int cnt = __builtin_popcount(ans);
            printf("%d\n", cnt);
        }
    }
    return 0;
}