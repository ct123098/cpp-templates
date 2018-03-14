#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

namespace myPrimes
{
	typedef unsigned long long u64;
	u64 xrand()
	{
		u64 ret = 0;
		for(int i = 0; i <= 60; i += 15)
			ret |= ((u64)rand() & 0x7fff) << i;
		return ret;
	}
	u64 gcd(u64 x, u64 y)
	{
		return x == 0 ? y : gcd(y % x, x);
	}
	u64 qmul(u64 x, u64 y, u64 mod)
	{
		u64 ret = 0;
		for(; y; x = (x + x) % mod, y >>= 1)
			if(y & 1)
				ret = (ret + x) % mod;
		return ret;
	}
	u64 qpow(u64 x, u64 y, u64 mod)
	{
		u64 ret = 1;
		for(; y; x = qmul(x, x, mod), y >>= 1)
			if(y & 1)
				ret = qmul(ret, x, mod);
		return ret;
	}

	bool miller_rabin(long long n)
	{
		if(n == 2) return true;
		long long a = n - 1, b = 0;
		while(~a & 1)
			a >>= 1, b += 1;
		for(int t = 0; t < 20; t++)
		{
			long long r = xrand() % (n - 2) + 2, v = qpow(r, a, n);
			for(int i = 1; i <= b && v != 1; i++)
			{
				long long vv = qmul(v, v, n);
				if(vv == 1 && v != n - 1)
					return false;
				v = vv;
			}
			if(v != 1)
				return false;
		}
		return true;
	}

	long long next(long long x, long long n, long long a)
	{
		return (qmul(x, x, n) + a) % n;
	}
	vector<long long> pollard_rho(long long n)
	{
		if(n == 1)
			return vector<long long>();
		if(miller_rabin(n))
			return vector<long long>(1, n);
		vector<long long> ret;
		for(int t = 1; ; t++)
		{
			long long a = xrand() % n, b = next(a, n, t), p = 0;
			while(a != b)
			{
				if(gcd(abs(a - b), n) > 1)
				{
					p = gcd(abs(a - b), n); break;
				}
				a = next(a, n, t), b = next(next(b, n, t), n, t);
			}
			if(p != 0)
			{
				vector<long long> tmp = pollard_rho(p);
				ret.insert(ret.end(), tmp.begin(), tmp.end());
				tmp = pollard_rho(n / p);
				ret.insert(ret.end(), tmp.begin(), tmp.end());
				return ret;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);

	using namespace myPrimes;

	cout << 1000000003ll << ' ' << miller_rabin(1000000003ll) << endl;
	cout << 1000000007ll << ' ' << miller_rabin(1000000007ll) << endl;

	cout << 1000000007ll * 1000000009ll << " : ";
	vector<long long> ans = pollard_rho(1000000007ll * 1000000009ll);
	sort(ans.begin(), ans.end());
	for(int i = 0; i < ans.size(); i++)
		cout << ans[i] << ' ';
	cout << endl;

	return 0;
}
