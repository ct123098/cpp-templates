#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

namespace myFastInput
{
	const int SIZE = 65536;
	char buff[2 * SIZE], *st = buff, *ed = buff;
	char getchar()
	{
		if(st == ed)
			st = buff, ed = st + fread(buff, 1, SIZE, stdin), *ed = 0;
		return *(st++);
	}
	int read()
	{
		int ret = 0;
		char c = getchar();
		while(c < '0' || c > '9') c = getchar();
		while('0' <= c && c <= '9') ret = 10 * ret + c - '0', c = getchar();
		return ret;
	}
	int readSign()
	{
		bool neg = false;
		int ret = 0;
		char c = getchar();
		while(c != '-' && (c < '0' || c > '9')) c = getchar();
		if(c == '-') neg = true, c = getchar();
		while('0' <= c && c <= '9') ret = 10 * ret + c - '0', c = getchar();
		return neg ? -ret : ret;
	}
}

using myFastInput::read;
using myFastInput::readSign;

int main()
{
	ios::sync_with_stdio(false);

	cout << read() << endl;
	cout << readSign() << endl;

	return 0;
}
