#define _CRT_SECURE_NO_WARNINGS 1
#include<stack>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

#define fi first
#define sd second
typedef pair<int, int> P;
typedef long long ll;
const int N = 200005;

char a[N], b[N];
int n, s[N], sa[N], rk[N], oldrk[N << 1];
int cnt[N], ht[N], px[N], id[N];

bool cmp(int x, int y, int w) 
{
	return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

void da(int s[], int n, int m) {
	int i, p = 0, w, k;
	
	for (i = 1; i <= n; i++) ++cnt[rk[i] = s[i]];
	for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
	for (i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
	for (w = 1; w < n; w <<= 1, m = p) 
	{
		memset(cnt, 0, sizeof(cnt));
		memcpy(oldrk, rk, sizeof(rk));
		for (p = 0, i = n; i > n - w; i--) id[++p] = i;
		for (i = 1; i <= n; i++) if (sa[i] > w) id[++p] = sa[i] - w;
		for (i = 1; i <= n; i++) ++cnt[px[i] = rk[id[i]]];
		for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
		for (i = n; i >= 1; i--) sa[cnt[px[i]]--] = id[i];
		for (p = 0, i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
	}

	for (i = 1, k = 0; i <= n; i++) {
		if (k) --k;
		while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
		ht[rk[i]] = k;
	}
}

P H[N];  //单调栈，sd 记录非递减序列值，fi 记录数量；
int K, Y;

void work() 
{
	ll ANS = 0;
	ll tot = 0, len = 0;
	for (int i = 2; i <= n; i++) {
		if (ht[i] < K) tot = len = 0;
		else {
			int cnt = 0;
			if (sa[i - 1] < Y) tot += ht[i] - K + 1, cnt++;
			while (len > 0 && H[len].sd >= ht[i]) {    //相当于统计相同值的数量；
				P top = H[len]; len--;
				tot -= (top.sd - ht[i]) * top.fi;
				cnt += top.fi;
			}
			H[++len] = P(cnt, ht[i]);
			if (sa[i] > Y) ANS += tot;
		}
	}
	tot = 0, len = 0;
	for (int i = 2; i <= n; i++) {
		if (ht[i] < K) tot = len = 0;
		else {
			int cnt = 0;
			if (sa[i - 1] > Y) tot += ht[i] - K + 1, cnt++;
			while (len > 0 && H[len].sd >= ht[i]) {
				P top = H[len]; len--;
				tot -= (top.sd - ht[i]) * top.fi;
				cnt += top.fi;
			}
			H[++len] = P(cnt, ht[i]);
			if (sa[i] < Y) ANS += tot;
		}
	}
	printf("%lld\n", ANS);
}

int main()
{
	while (scanf("%d", &K) && K) 
	{
		memset(cnt, 0, sizeof(cnt));
		scanf("%s%s", a + 1, b + 1);
		n = strlen(a + 1);
		for (int i = 1; i <= n; i++) s[i] = a[i];
		Y = n + 1;
		n = strlen(b + 1);
		for (int i = 1; i <= n; i++) s[i + Y] = b[i];
		s[Y] = '@';
		n += Y;
		da(s, n, 128);
		work();
	}
}