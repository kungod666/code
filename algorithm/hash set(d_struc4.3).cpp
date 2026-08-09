#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    unordered_set<string> dictionary;
    
    for (int i = 0; i < n; i++) {
        string command, str;
        cin >> command >> str;
        
        if (command == "insert") {
            dictionary.insert(str);
        } 
        else if (command == "find") {
            if (dictionary.find(str) != dictionary.end()) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }
    
    return 0;
}