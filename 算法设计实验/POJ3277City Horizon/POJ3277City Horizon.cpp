// POJ3277City Horizon.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
#define ll long long
const int N = 1000005;
int n;
int l[N], r[N], h[N];
set<int>s;
set<int>::iterator it;
int map[2 * N];
ll ans;

void init()
{
    s.clear();
    memset(map, 0, sizeof(map));
    memset(l, 0, sizeof(l));
    memset(r, 0, sizeof(r));
    memset(h, 0, sizeof(h));
}

struct Node
{
    int l, r;
    int Ma;
}seg[4 * N];

void PushDown(int rt)
{
    int t = seg[rt].Ma;
    if (t > seg[2 * rt].Ma)seg[2 * rt].Ma = t;
    if (t > seg[2 * rt + 1].Ma)seg[2 * rt + 1].Ma = t;
}

void Build(int rt, int l, int r)
{
    seg[rt].l = l, seg[rt].r = r;
    seg[rt].Ma = 0;
    if (l != r)
    {
        Build(2 * rt, l, (l + r) / 2);
        Build(2 * rt + 1, (l + r) / 2 + 1, r);
    }
}

void Update(int rt, int l, int r, int val)
{
    if (seg[rt].l == l && seg[rt].r == r)
    {
        if (val > seg[rt].Ma)seg[rt].Ma = val;
        return;
    }
    PushDown(rt);
    int mid = (seg[rt].l + seg[rt].r) / 2;
    if (r <= mid)Update(2 * rt, l, r, val);
    else if (l > mid)Update(2 * rt + 1, l, r, val);
    else
    {
        Update(2 * rt, l, mid, val);
        Update(2 * rt + 1, mid + 1, r, val);
    }
}

void solve(int rt, int l, int r)
{
    PushDown(rt);
    if (l == r)
    {
        if (r % 2 == 0)
        {
            int mi = seg[rt].r;
            ans += (ll)(seg[rt].Ma) * (map[mi + 1] - map[mi - 1]);
        }
        return;
    }
    else
    {
        int mid = (l + r) / 2;
        solve(2 * rt, l, mid);
        solve(2 * rt + 1, mid + 1, r);
    }
}

int main()
{
    while (~scanf("%d", &n))
    {
        init();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d", l + i, r + i, h + i);
            s.insert(l[i]), s.insert(r[i]);
        }
        int cnt = 1;
        for (it = s.begin(); it != s.end(); it++) 
        {
            int t = *it;
            map[cnt] = t;
            map[cnt + 1] = t;
            cnt += 2;
        }
        cnt -= 2;
        Build(1, 1, cnt);
        for (int i = 1; i <= n; i++)
        {
            int L = l[i], R = r[i];
            L = lower_bound(map + 1, map + cnt + 1, L) - map;
            R = lower_bound(map + 1, map + cnt + 1, R) - map;
            Update(1, L, R, h[i]);
        }
        ans = 0;
        solve(1, 1, cnt);
        printf("%I64d\n", ans);
    }
    return 0;
}