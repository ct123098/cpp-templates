#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 100;
const int MAXM = 1000000 + 100;
const int INF = 0x3f3f3f3f;

namespace ISAP
{
	struct Edge
	{
		int next, to, w;
	}
	e[MAXM];
	int p[MAXN], head[MAXN], l = 2;

	void addE(int a, int b, int c)
	{
		e[l] = (Edge){p[a], b, c};
		p[a] = l++;
	}
	void ins2(int a, int b, int c)
	{
		addE(a, b, c);
		addE(b, a, 0);
	}

	int S, T, N;
	int dis[MAXN], num[MAXN];
	int flow = 0;

	int dfs(int x, int s)
	{
		if(x == T)
			return s;
		int ret = 0;
		for(int &i = head[x]; i; i = e[i].next)
			if(e[i].w > 0 && dis[e[i].to] + 1 == dis[x])
			{
				int t = dfs(e[i].to, min(e[i].w, s));
				e[i].w -= t, e[i ^ 1].w += t;
				s -= t, ret += t;
				if(dis[S] >= N || s <= 0)
					return ret;
			}
		int ndis = N;
		for(int i = p[x]; i; i = e[i].next)
			if(e[i].w > 0)
				ndis = min(ndis, dis[e[i].to] + 1);
		if(!(--num[dis[x]])) dis[S] = N;
		num[dis[x] = ndis]++;
		head[x] = p[x];
		return ret;
	}

	int isap()
	{
		memset(dis, 0, sizeof(dis));
		memset(num, 0, sizeof(num));
		num[0] = N;
		memcpy(head, p, sizeof(p));
		flow = 0;
		while(dis[S] < N)
			flow += dfs(S, INF);
		return flow;
	}
}


int main()
{
	ios::sync_with_stdio(false);

	using namespace ISAP;
	
	int n, m;
	cin >> n >> m;
	S = 1, T = n, N = n;
	for(int i = 1; i <= m; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		ins2(x, y, z);
	}

	int ans = isap();

	cout << ans << endl;


	return 0;
}
