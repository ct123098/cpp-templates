#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 100000 + 100;
const int MAXM = 1000000 + 1000;
const int INF = 0x3f3f3f3f;

namespace myDinic
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
	int dis[MAXN];
	queue<int> q;
	int flow = 0;

	bool bfs()
	{
		memset(dis, 0, (N + 2) * sizeof(dis[0]));
		dis[S] = 1, q.push(S);
		while(!q.empty())
		{
			int x = q.front();
			q.pop();
			for(int i = p[x]; i; i = e[i].next)
				if(e[i].w > 0 && !dis[e[i].to])
				{
					int y = e[i].to;
					dis[y] = dis[x] + 1, q.push(y);
				}
		}
		return dis[T];
	}

	int dfs(int x, int s)
	{
		if(x == T)
			return s;
		int ret = 0;
		for(int i = head[x]; i; i = e[i].next)
			if(e[i].w > 0 && dis[x] + 1 == dis[e[i].to])
			{
				int t = dfs(e[i].to, min(e[i].w, s));
				e[i].w -= t, e[i ^ 1].w += t;
				s -= t, ret += t;
				if(s <= 0)
					break;
			}
		return ret;
	}

	int dinic()
	{
		flow = 0;
		while(bfs())
		{
			memcpy(head, p, (N + 2) * sizeof(p[0]));
			flow += dfs(S, INF);
		}
		return flow;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);

	using namespace myDinic;

	int n, m;
	cin >> n >> m;
	S = 1, T = n, N = n;

	for(int i = 1; i <= m; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		ins2(x, y, z);
	}

	int ans = dinic();

	cout << ans << endl;

	return 0;
}
