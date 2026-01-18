#include <iostream>
#define NF -1
#define DELETED -2 //从而支持删除操作
#define TAB_SIZE 103
#include <vector>
using namespace std;
vector<long> index_vec(TAB_SIZE,NF);
long h1(long key)
{
    return key%TAB_SIZE;
}
long h2(long key)
{
    return 1+key%(TAB_SIZE-1);
}
long H(long key,long i)
{
    return (h1(key)+i*h2(key))%TAB_SIZE;
}
long search(long key);
long insert(long key)
{
    long pos = search(key);
    if (pos != NF) {
        // key已存在，可以选择更新或直接返回(设计得非常逻辑自洽啊！！！)
        // 这里我们选择更新
        index_vec[pos] = key;
        return pos;
    }
    long i = 0;
    while(i < TAB_SIZE) //限制尝试次数
    {
        long j = H(key,i);
        if(index_vec[j] == NF || index_vec[j] == DELETED)
        {
            index_vec[j] = key;
            return j;
        }
        else i++;
    }
    return NF;
}
long search(long key)
{
    long i = 0;
    while(i < TAB_SIZE)
    {
        long j = H(key,i);
        if(index_vec[j] == NF) return NF;
        else if(index_vec[j] == key) return j;
        i++;
    }
    return NF;
}
long deleted(long key)
{
    long i = 0;
    while(i < TAB_SIZE)
    {
        long j = H(key,i);
        if(index_vec[j] == NF) return NF;
        else if(index_vec[j] == key)
        {
            index_vec[j] = DELETED;
            return j;
        }
        i++;
    }
    return NF;
}
int main()
{
    int num;
    cin >> num;
    insert(num);
    if(search(num) != NF) cout << "YES!\n";
    else cout << "NOTFOUND\n";
}