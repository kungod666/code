#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;
    
    if (s.empty()) {
        return 0;
    }
    
    if (s.length() == 1) {
        std::cout << "";
        return 0;
    }
    
    int pos_to_remove = 0;
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] > s[i + 1]) {
            pos_to_remove = i;
            break;
        }
    }
    
    if (pos_to_remove == 0 && s[0] <= s[s.length() - 1]) {
        pos_to_remove = s.length() - 1;
    }
    
    std::string result = s.substr(0, pos_to_remove) + s.substr(pos_to_remove + 1);
    
    std::cout << result;
    return 0;
}