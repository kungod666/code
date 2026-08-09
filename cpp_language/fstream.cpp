#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    int num[] = {3,244,37,42,49,22,46,37,19};
    ofstream fout("Cpplesson.txt",ios::app);
    //app使不让覆盖(否则打开旧文件后输出到文件内容会覆盖旧文件)
    fout << "hello world\n";
    fout << "123\n";
    fout.close();

    ifstream fin("Cpplesson.txt");
    string s;
    while(fin >> s){
        cout << s << endl;
    }
    //fin这种模式默认遇到空格停止fin

    //更常见:按行读取
    string line;
    while(getline(fin,line)){
        cout << line << endl;
    }
    fin.close();
}