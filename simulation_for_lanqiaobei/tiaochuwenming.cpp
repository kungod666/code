#include <iostream>
#include <vector>
using namespace std;
int main(){
    int T;
    cin >> T;
    int count = 0;
    while(count++ < T){
        int N,X;
        cin >> N >> X;
        vector<int> zhuzi(N);
        for(int i = 0;i < N;i++){
            cin >> zhuzi[i];
        }
        int flag = 1;
        for(int i = 0;i < N-1;i++){
            if(zhuzi[i] < zhuzi[i+1]){
                if(zhuzi[i+1] - zhuzi[i] > 1){
                    flag = 0;
                    break;
                }
            }
            else if(zhuzi[i] > zhuzi[i+1]){
                if(zhuzi[i] - zhuzi[i+1] > X){
                    flag = 0;
                    break;
                }
            }
        }
        if(flag) {
            cout << "Win" << "\n";
            continue;
        }
        cout << "Lose" << "\n";
    }
    return 0;
}