#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 200000 + 100;
const int MOD = 998244353;

int fpow(int x, int p)
{
	if(p == 0) return 1;
	int t = fpow(x, p / 2);
	t = (long long)t * t % MOD;
	if(p & 1) return (long long)t * x % MOD;
	else return t;
}

int get_inv(int x)
{
	return fpow(x, MOD - 2);
}

namespace myNTT
{
	int rev[4 * MAXN], w1[4 * MAXN], w2[4 * MAXN];
	void NTT_core(int n, int *a, int *w)
	{
		for(int i = 0; i < n; i++)
			if(rev[i] < i)
				swap(a[rev[i]], a[i]);
		for(int i = 1; i < n; i <<= 1)
			for(int j = 0; j < n; j += 2 * i)
				for(int k = 0; k < i; k++)
				{
					int x = a[j + k], y = (long long)a[j + k + i] * w[i + k] % MOD;
					a[j + k] = (x + y) % MOD;
					a[j + k + i] = (x - y + MOD) % MOD;
				}
	}
	void NTT(int n, int *a)
	{
		NTT_core(n, a, w1);
	}
	void INTT(int n, int *a)
	{
		NTT_core(n, a, w2);
		int inv = get_inv(n);
		for(int i = 0; i < n; i++)
			a[i] = (long long)a[i] * inv % MOD;
	}
	void init(int n)
	{
		int l = log2(n) + 0.5, half = n / 2;
		rev[0] = 0;
		for(int i = 1; i < n; i++)
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
		// for(int i = 0; i < n; i++)
		// 	cout << rev[i] << endl;
		int wn = fpow(3, (MOD - 1) / n);
		// cout << n << ' ' << l << ' ' << wn << endl;
		w1[half] = 1;
		for(int i = 1; i < half; i++)
			w1[half + i] = (long long)w1[half + i - 1] * wn % MOD;
		for(int i = half - 1; i >= 0; i--)
			w1[i] = w1[i << 1];
		wn = get_inv(wn);
		w2[half] = 1;
		for(int i = 1; i < half; i++)
			w2[half + i] = (long long)w2[half + i - 1] * wn % MOD;
		for(int i = half - 1; i >= 0; i--)
			w2[i] = w2[i << 1];
	}
	void conv_ntt(int n, int *a, int m, int *b, int *c)
	{
		static int A[4 * MAXN], B[4 * MAXN], C[4 * MAXN];
		int len = 1;
		while(len <= n + m - 1)
			len <<= 1;
		for(int i = 0; i < len; i++)
			A[i] = B[i] = C[i] = 0;
		for(int i = 0; i <= n - 1; i++)
			A[i] = a[i];
		for(int i = 0; i <= m - 1; i++)
			B[i] = b[i];
		init(len);
		NTT(len, A), NTT(len, B);
		for(int i = 0; i < len; i++)
			C[i] = (long long)A[i] * B[i] % MOD;
		INTT(len, C);
		for(int i = 0; i <= n + m - 2; i++)
			c[i] = C[i];
	}
	void conv_force(int n, int *a, int m, int *b, int *c)
	{
		static int C[4 * MAXN];
		for(int i = 0; i <= n + m - 2; i++)
			C[i] = 0;
		for(int i = 0; i <= n - 1; i++)
			for(int j = 0; j <= m - 1; j++)
				C[i + j] = (C[i + j] + (long long)a[i] * b[j]) % MOD;
		for(int i = 0; i <= n + m - 2; i++)
			c[i] = C[i];
	}
	void conv(int n, int *a, int m, int *b, int *c)
	{
		if((long long)n * m <= 2333)
			conv_force(n, a, m, b, c);
		else
			conv_ntt(n, a, m, b, c);
	}
}

using myNTT::conv;

int main()
{
	ios::sync_with_stdio(false);

	int a[] = {1, 2, 1}, b[] = {1, 1};
	int lena = sizeof(a) / sizeof(a[0]), lenb = sizeof(b) / sizeof(b[0]);
	int lenc = lena + lenb - 1;
	int *c = new int[lenc];

	conv(lena, a, lenb, b, c);

	for(int i = 0; i < lenc; i++)
		cout << c[i] << ' ';
	cout << endl;

	return 0;
}
