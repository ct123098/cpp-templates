#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <complex>
#include <cmath>

using namespace std;

const int MAXN = 100000 + 100;

namespace myFFT
{
	const double PI = acos(-1.0);
	int rev[4 * MAXN];
	complex<double> w1[4 * MAXN], w2[4 * MAXN];
	void FFT_core(int n, complex<double> *a, complex<double> *w)
	{
		for(int i = 0; i < n; i++)
			if(i < rev[i])
				swap(a[i], a[rev[i]]);
		for(int i = 1; i < n; i <<= 1)
			for(int j = 0; j < n; j += 2 * i)
				for(int k = 0; k < i; k++)
				{
					complex<double> x = a[j + k], y = a[i + j + k] * w[i + k];
					a[j + k] = x + y;
					a[i + j + k] = x - y;
				}
	}
	void DFT(int n, complex<double> *a)
	{
		FFT_core(n, a, w1);
	}
	void IDFT(int n, complex<double> *a)
	{
		FFT_core(n, a, w2);
		for(int i = 0; i < n; i++)
			a[i] /= n;
	}
	void init(int n)
	{
		int l = log2(n) + 0.5, half = n / 2;
		rev[0] = 0;
		for(int i = 1; i < n; i++)
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
		for(int i = 0; i < half; i++)
			w1[half + i] = complex<double>(cos(2 * PI * i / n), sin(2 * PI * i / n));
		for(int i = half - 1; i >= 0; i--)
			w1[i] = w1[i << 1];
		for(int i = 0; i < n; i++)
			w2[i] = conj(w1[i]);
	}
	void conv_fft(int n, int *a, int m, int *b, int *c)
	{
		static complex<double> A[4 * MAXN], B[4 * MAXN], C[4 * MAXN];
		int len = 1;
		while(len < n + m - 1) len <<= 1;
		for(int i = 0; i < len; i++) A[i] = B[i] = C[i] = complex<double>(0.0, 0.0);
		for(int i = 0; i < n; i++) A[i] = a[i];
		for(int i = 0; i < m; i++) B[i] = b[i];
		init(len);
		DFT(len, A), DFT(len, B);
		for(int i = 0; i < len; i++)
			C[i] = A[i] * B[i];
		IDFT(len, C);
		for(int i = 0; i < n + m - 1; i++)
			c[i] = C[i].real() + 0.5;
	}
	void conv_force(int n, int *a, int m, int *b, int *c)
	{
		static int C[4 * MAXN];
		for(int i = 0; i < n + m - 1; i++)
			C[i] = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				C[i + j] = C[i + j] + a[i] * b[j];
		for(int i = 0; i < n + m - 1; i++)
			c[i] = C[i];
	}
	void conv(int n, int *a, int m, int *b, int *c)
	{
		if((long long)n * m <= 2333)
			conv_force(n, a, m, b, c);
		else
			conv_fft(n, a, m, b, c);
	}
}

using myFFT::conv;

int n, m;
int a[MAXN], b[MAXN], c[MAXN];

int main()
{
	ios::sync_with_stdio(false);

	cin >> n >> m;
	n += 1, m += 1;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < m; i++)
		cin >> b[i];
	conv(n, a, m, b, c);
	for(int i = 0; i < n + m - 1; i++)
		cout << c[i] << ' ';
	cout << endl;

	return 0;
}
