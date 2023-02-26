// True Liars.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#define YES 1
#define NO 0
#include<stdio.h>
#include<cstring>
int ans[1500][700];//这里并不是神族成员越多越好 故不能压缩维度
int num = 0;
int answer[200000];
int p[1400];  //p[x]表示和x同一族 p[x+p]表示和x不同族
int flag[1400];   //flag=0表示1~num为神族 flag=1表示num+1~2*num为神族
int count[1400][2];  //count【i】表示属于同一并查集（root=i）的元素的数目
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
void unity(int x, int y)
{
    p[find(x)] = find(y);
    return;
}
//int min(int a, int b)
//{
//    return a < b ? a : b;
//}
int create(int n, int p1, int p2)
{
    int sum;
    sum = p1 + p2;
    num = 0;
    int x, y;
    char c[6];
    for (int i = 0; i < 1400; i++)
    {
        p[i] = i;
    }
    memset(flag, 0, sizeof(flag));
    memset(count, 0, sizeof(count));
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d %s", &x, &y, c);
        if (c[0] == 'y')
        {
            unity(x, y);//x与y同族
            unity(x + sum, y + sum);//x的敌人与y的敌人同族
        }
        else
        {
            unity(x + sum, y);//x的敌人和y同族
            unity(x, y + sum);//x与y的敌人同族
        }
    }
    //每个root（包含一个族的序号 和 另一族的序号+sum）
    for (int i = 1; i <= sum; i++)
    {
        count[find(i)][0]++;
    }
    for (int i = sum + 1; i <= 2 * sum; i++)
    {
        count[find(i)][1]++;
    }
    for (int i = 1; i <= sum; i++)
    {
        if (count[i][0] || count[i][1]) num++;
    }
    return 0;
}

int judge(int p1, int p2, int i, int sum)
{
    //使用dp 计算ans[i][j] 表示前i个root中有j个神的方案数 最后判断ans[num][p1];
    //状态转移方程 
    // ans[i][j]
    //=ans[i-1][j-root=i的集合中小于num的序号的个数count[i][0]]
    // +ans[i-1][j-root=i的集合中大于num的序号的个数count[i][1]]

    ans[0][0] = 1;
    int root = 1;
    for (int i = 1; i <= num; i++)
    {
        while (count[root][0] == 0 && count[root][1] == 0 && root < sum) root++;

        for (int j = p1; j >= count[root][0]; j--)
        {
            ans[i][j] += ans[i - 1][j - count[root][0]];
        }
        for (int j = p1; j >= count[root][1]; j--)
        {
            ans[i][j] += ans[i - 1][j - count[root][1]];
        }
        root++;
    }
    if (ans[num][p1] != 1) return NO;

    root = sum;
    for (int i = num; i >= 1; i--)
    {
        while (count[root][0] == 0 && count[root][1] == 0 && root > 1) root--;
        if (p1 >= count[root][0] && ans[i - 1][p1 - count[root][0]])
        {
            flag[root] = 0;
            p1 -= count[root][0];
        }
        else
        {
            flag[root] = 1;
            p1 -= count[root][1];
        }
        root--;
    }
    return YES;
}

int main()
{
    int n, p1, p2, j = 0;
    int sum;
    for (int i = 0; i < 100005; i++)
    {
        answer[i] = 0;
    }

    do
    {
        scanf("%d%d%d", &n, &p1, &p2);
        sum = p1 + p2;
        create(n, p1, p2);//建立数据结构 
        if (judge(p1, p2, 1, sum))
        {
            for (int i = 1; i <= sum; i++)
            {
                if (find(i) <= sum && !flag[find(i)]) answer[j++] = i;
                else if (find(i + sum) <= sum && flag[find(i + sum)]) answer[j++] = i;
            }
            answer[j++] = 0;
            if (sum > 0) answer[j++] = -1;
        }
        else
        {
            answer[j++] = 0;
            answer[j++] = -2;
        }
    } while (!(n == 0 && p1 == 0 && p2 == 0));
    for (int i = 0; i < j; i++)
    {
        while (answer[i])
        {
            printf("%d\n", answer[i]);
            i++;
        }
        i++;
        if (answer[i] == -1)
        {
            printf("end\n");
        }
        if (answer[i] == -2)
        {
            printf("no\n");
        }
    }
    return 0;
}

//int judge(int p1, int p2, int i, int sum)
//{
//    int tag = 0;
//    if (ans >= 2) return NO;//出现多于一种可能
//    if (p1 == 0 && p2 == 0)
//    {
//        ans++;
//        return YES;
//    }//出现一种解，递归边界
//    while (count[i][0] == 0 && count[i][1] == 0 && i <= sum) i++;
//    if (i > sum) return NO;//找不到解，递归边界
//    if (judge(p1 - count[i][0], p2 - count[i][1], i + 1, sum)) //如果向下递归有解
//    {
//        flag[i] = 0;
//        tag = 1;//标记有解
//    }
//    if (judge(p1 - count[i][1], p2 - count[i][0], i + 1, sum)) //如果向下递归有解
//    {
//        flag[i] = 1;
//        tag = 1;//标记有解
//    }
//    if (ans >= 2) return NO;//出现多于一种可能
//    if (tag) return YES;
//    else return NO;
//    
// 
// 
//    递归输 dp赢
//}