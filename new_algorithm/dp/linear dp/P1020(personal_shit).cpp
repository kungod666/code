#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
int n = 0;
vector<int> attack;
vector<pair<int,int>> series;
struct cmp{
    bool operator()(const pair<int,int>& a,const pair<int,int>& b)const{
        return a.first < b.first;
    }
};
int pos = 0;
int main(){
    int counts;
    while(cin >> counts){
        attack.push_back(counts);
        n++;
    }
    vector<pair<int,int>> temp2(n,pair<int,int>(0,-1));
    series = temp2;
    int begin = 0;
    int end = 0;
    series[pos].first = begin;
    series[pos].second = end;
    for(int i = 1;i < n;i++){
        if(attack[i] < attack[i-1]){
            end = i;
            series[pos].second = end;
        }
        else{
            pos++;
            begin = i;
            end = i;
            series[pos].first = begin;
            series[pos].second = end;
        }
    }
    sort(series.begin(),series.end(),cmp());//结构体比较器在sort应该cmp()，优队则cmp
    pair<int,int> pivot = series[0];
    int stand = 0;
    int ans1 = 0;
    for(int i = 0;i < n;i++){
        int tmp = 0;
        stand = i;
        pivot = series[i];
        tmp += series[i].second-series[i].first+1;
        for(int m = i+1;m < n;m++){
        if(series[m].first == -1 || m == stand) continue;
        if(attack[series[m].first] > attack[pivot.first]){
            int num = 1;
            for(int j = series[m].first+1;j <= series[m].second;j++){
                if(attack[j] > attack[pivot.first]) num++;
                else break;
            }
            tmp += num;
        }
        ans1 = max(tmp,ans1);
    }
    }
    int ans2 = pos+1;
    cout << ans1 << "\n";
    cout << ans2 << "\n";
}