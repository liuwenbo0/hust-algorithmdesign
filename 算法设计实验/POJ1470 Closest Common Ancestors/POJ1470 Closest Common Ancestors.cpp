// POJ1470 Closest Common Ancestors.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#define MAXN 1005
using namespace std;
vector<int>son[MAXN];
bool root[MAXN];
int pos[MAXN],ouler[MAXN<<1],lg[MAXN<<1],st[11][MAXN<<1],ans[MAXN]; //pos保存节点按dfs第一次出现的顺序，ouler保存按dfs顺序出现的节点
int n,oulertot;
void swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}
void dfs(int rt) {
	ouler[++oulertot] = rt;
	pos[rt] = oulertot;
	for (int i = 0; i<son[rt].size(); i++) 
	{
		dfs(son[rt][i]);	
		ouler[++oulertot] = rt;
	}
	
}
void st_preprocess() 
{

	for (int i = 1; i <= (n << 1) - 1; ++i) st[0][i] = ouler[i]; //按ouler序从i位置处走1格的pos的最小值对应的节点
	for (int i = 1; i <= lg[(n << 1) - 1]; ++i)
		for (int j = 1; j + (1 << i) - 1 <= ((n << 1) - 1); ++j)
			st[i][j] = pos[st[i - 1][j]] < pos[st[i - 1][j + (1 << (i - 1))]] ? st[i - 1][j] : st[i - 1][j + (1 << (i - 1))];
	//按欧拉序从j走2^i格的pos的最小值对应的节点 可以根据两段合并得到
}
int LCA(int nd1,int nd2)
{
	if (pos[nd1] < pos[nd2])
	{
		swap(nd1, nd2);
	}
	//保证nd1的欧拉序大于nd2
	int s = lg[pos[nd1] - pos[nd2] + 1];
	if (pos[st[s][pos[nd2]]] < pos[st[s][pos[nd1] - (1 << (s)) + 1]])
		return st[s][pos[nd2]];
	else
		return st[s][pos[nd1] - (1 << (s)) + 1];
}
int main()
{
	int pa, num, so,rt,nd1,nd2;
	int qnum;
	lg[0] = -1;
	for (int i = 1; i <= (MAXN<< 1); ++i) lg[i] = lg[i >> 1] + 1;
	while (~scanf("%d", &n))
	{
		qnum = 0, num = 0, pa = 0, so = 0, rt = 0, nd1 = 0, nd2 = 0;
		memset(root, colorue, MAXN);
		memset(ans, 0, MAXN);
		for (int i = 1; i <= n; i++)
		{
			son[i].clear();
		}
		for (int i = 1; i <= n; i++)
		{
			scanf("%d:(%d)", &pa, &num);
			for (int i = 1; i <= num; i++)
			{
				scanf("%d", &so);
				son[pa].push_back(so);
				root[so] = false;
			}
		}
		

		for (int i = 1; i <= n; i++)
		{
			if (root[i])
			{
				rt = i;
				break;
			}
		}
		memset(ouler, 0, MAXN << 1);
		memset(st, 0, sizeof(st));
		oulertot = 0;
		dfs(rt);
		st_preprocess();
		scanf("%d", &qnum);
		for (int i = 1; i <= qnum; i++)
		{
			scanf(" (%d %d)", &nd1, &nd2);
			ans[LCA(nd1,nd2)]++;  //找到两段中pos最小值对应的节点的pos的较小值对应的节点
		}
		for (int i = 1; i <= n; i++)
			if (ans[i] != 0) printf("%d:%d\n", i, ans[i]);
	}
	return 0;
}


