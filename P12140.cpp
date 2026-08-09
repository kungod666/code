#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,m;
vector<ll> pos(4,1);
vector<vector<ll>> wheels;
vector<vector<ll>> nums;
ll getNum(int type,ll trial){
	if(pos[type] + (trial%n) > n){
		pos[type] = (pos[type]+(trial%n))%n;
	}
	else pos[type] += (trial%n);
	return wheels[type][pos[type]];
}
ll getScore(){
	ll sum = 0;
	for(int i = 1;i <= m;i++){
		int flag1 = 0;
		int flag2 = 0;
		int flag3 = 0;
		int flag4 = 0;
		vector<ll> check = nums[i];
		map<ll,ll> hash;
		sort(check.begin()+1,check.end());
		hash[nums[i][1]]++;
		for(int j = 2;j <= 3;j++){
			if(abs(check[j]-check[j-1]) != 1){
				flag1 = 1;
				flag2 = 1;
			}
			if(!flag1 && !flag2&&nums[i][j] < nums[i][j-1]){
				flag2 = 1;
			}
			hash[nums[i][j]]++;
		}
		for(auto it : hash){
			if(it.second == 2){
				flag3 = 1;
				break;
			}
			else if(it.second == 3){
				flag4 = 1;
				break;
			}
		}
		if(!flag1&&!flag2) {
			sum+=200;
		}
		else if(flag4){
			sum+= 200;
		}
		else if(!flag1 || flag3){
			sum+=100;
		}
	}
	return sum;
}
int main(){
	cin >> n;
	vector<vector<ll>> tmp(4,vector<ll>(n+1));
	wheels = tmp;
	//有效为1~3,1~n
	for(int i = 1;i <= 3;i++){
		for(int j = 1;j <= n;j++){
			cin >> wheels[i][j];
		}
	}
	cin >> m;
	vector<vector<ll>> trials(m+1,vector<ll>(4));
	//1~m,1~3
	for(int i = 1;i <= m;i++){
		for(int j = 1;j <= 3;j++){
			cin >> trials[i][j];
		}
	}
	vector<vector<ll>> tmp2(m+1,vector<ll>(4));
	//1~m,1~3
	nums = tmp2;
	for(int i = 1;i <= m;i++){
		for(int j = 1;j <= 3;j++){
			nums[i][j] = getNum(j,trials[i][j]);
		}
	}
	cout << getScore();
}
