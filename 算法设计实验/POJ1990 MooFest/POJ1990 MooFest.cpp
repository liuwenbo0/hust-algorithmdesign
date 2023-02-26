// POJ1990 MooFest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#define MAXN 25000
#define lowbit(x) ((x) & (-x))
__int64 volume[MAXN];
__int64 pos[MAXN];
__int64 count[MAXN];
__int64 total[MAXN];//query(count,pos[i])返回比第i头牛volume小且pos小的牛的个数   
//query(total,pos[i])返回上述牛到第i头牛的距离

void update(__int64  tree[], int i, int x)
{
    for (int pos = i; pos < MAXN; pos += lowbit(pos))
        tree[pos] += x;
}

__int64  query(__int64  tree[], int n)
{
    __int64  ans = 0;
    for (int pos = n; pos; pos -= lowbit(pos))
        ans += tree[pos];
    return ans;
}

__int64  query(__int64  tree[], int i, int j)
{
    return query(tree, j) - query(tree, i - 1);
}

void swap(__int64& a, __int64& b)
{
    __int64  temp = a;
    a = b;
    b = temp;
}

void quick_sort(__int64  volume[], __int64  pos[], int l, int r)
{
    if (l >= r) return;
    int i = l - 1, j = r + 1;
    __int64  x = volume[(l + r) >> 1];
    while (i < j)
    {
        do i++; while (volume[i] > x);
        do j--; while (volume[j] < x);
        if (i < j)
        {
            swap(volume[i], volume[j]);
            swap(pos[i], pos[j]);
        }
    }
    quick_sort(volume, pos, l, j);
    quick_sort(volume, pos, j + 1, r);
}

int main()
{
    int N;
    __int64  ans = 0, alltotal = 0;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        scanf("%lld%lld", &volume[i], &pos[i]);
        alltotal += pos[i];
    }
    quick_sort(volume, pos, 1, N);
    //这里音量大的牛排在前面
    //printf("\n");
    /*for (int i = 1; i <= N; i++)
    {
        printf("%l64d %l64d\n", volume[i], pos[i]);
    }*/
    memset(count, 0, sizeof(count));
    memset(total, 0, sizeof(total));
    for (int i = 1; i <= N; i++)
    {
        update(count, pos[i], 1);
        update(total, pos[i], pos[i]);
    }
    /*printf("\n");*/
    /*for (int i = 1; i < N; i++)
    {
        update(count, pos[i], -1);
        update(total, pos[i], -pos[i]);
        printf("%l64d %l64d\n", query(count,pos[i]), query(total,pos[i]));
    }*/

    for (int i = 1; i < N; i++)
    {
        alltotal -= pos[i];
        update(count, pos[i], -1);
        update(total, pos[i], -pos[i]);
        /* ans += (query(count, pos[i]) * pos[i] - query(total, pos[i]))*volume[i];
         ans += (alltotal - query(total, pos[i]) - (N - i - query(count, pos[i])) * pos[i])*volume[i];*/
        ans += (alltotal - 2 * query(total, pos[i]) - (N - i - 2 * query(count, pos[i])) * pos[i]) * volume[i];
    }
    printf("%lld", ans);
}

