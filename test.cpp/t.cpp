#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <cctype>
#include <cstring>
#include <utility>
#include <set>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>
using namespace std;
int main()
{
	int a[5];
	int b[3];
	string s;
	for(int i = 1;i <= 6;i++)
	{
		int tp;
		cin >> tp;
		if(i == 1 || i == 2) a[i] = tp;
		if(i == 5) a[4] = tp;
		if(i == 6) a[3] =tp;
		if(i == 3) b[2] = tp;
		if(i == 4) b[1] = tp;
	}
	while(cin >> s)
	{
		for(int i = 0;i < s.size();i++)
		{
			if(s[i] == 'N')
			{
				int temp = a[1];
				for(int j = 1;j <=3;j++)
				{
					a[j] = a[j+1];
				}
				a[4] = temp;
			}
			if(s[i] == 'S')
			{
				int temp = a[4];
				for(int j = 4;j >=2;j--)
				{
					a[j] = a[j-1];
				}
				a[1] = temp;
			}
			if(s[i] == 'E')
			{
				int n,p;
				n = a[1];
				p = a[3];
				a[1] = b[1];
				a[3] = b[2];
				b[2] = n;
				b[1] = p; 
			}
			if(s[i] == 'W')
			{
				int n,p;
				n = a[1];
				p = a[3];
				a[1] = b[2];
				a[3] = b[1];
				b[2] = p;
				b[1] = n; 
			}
		}
	}
	cout << a[1];
	return 0;
}