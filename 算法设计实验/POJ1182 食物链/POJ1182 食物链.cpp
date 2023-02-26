#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<cmath>
int p[150005];/*祖宗节点*/   //x+N 表示吃 x+2*N 表示被吃
long sum = 0;
int N, K;

int find(int x)
{
	if (p[x] != x) p[x] = find(p[x]);//路径压缩
	return p[x];
}
void unity(int x, int y)
{
	p[find(x)] = find(y);
	return;
}
void judge(int D, int x1, int x2)
{

	if (x1 > N || x2 > N)
	{
		sum++;
		return;
	}//规则2

	if (D == 1)
	{

		if (find(x1) == find(x2))
			return;
		if (find(x1 + N) == find(x2) || find(x1 + 2 * N) == find(x2))//无法并入食物链中
		{
			sum++;
			return;
		}

		//并入食物链
		unity(x1, x2);

		unity(x1 + N, x2 + N);

		unity(x1 + 2 * N, x2 + 2 * N);
		return;

	}
	if (D == 2)
	{
		if (find(x1) == find(x2))
		{
			sum++;
			return;
		}//与前面语句矛盾 规则3
		if (find(x1 + 2 * N) == find(x2))
		{
			sum++;
			return;
		}//与前面语句矛盾
		unity(x1, x2 + 2 * N);
		unity(x1 + N, x2);
		unity(x1 + 2 * N, x2 + N);
		return;
	}
}

int main()
{
	int D, x1, x2;
	for (int i = 0; i <= 150004; i++)
	{
		p[i] = i;
	}
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= K; i++)
	{
		scanf("%d%d%d", &D, &x1, &x2);
		judge(D, x1, x2);//判断语句正确性
		//printf("%d\n", i);
	}
	printf("%ld", sum);
	return 0;
}