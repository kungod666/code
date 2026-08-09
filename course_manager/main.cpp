//运行方法：.\run.bat
/*还未实现功能模块
1.用户勾选哪些任务已经完成
2.搭建远程服务器，实现账户登录后user各操作自己的数据库*/
#include "sodium/crypto_pwhash.h"
#include <cstddef>
#include <unordered_map>
#include <mysql.h>
#include <cstring>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <string>
#include <sodium.h>
#include <stdexcept>
using namespace std;
string hash_password(const string& password){
    char hash[crypto_pwhash_STRBYTES];
    //对hash后的hash密码预处理一个容器
    if(crypto_pwhash_str_alg( //加密函数
        hash, //容器
        password.c_str(),
        password.size(),
        crypto_pwhash_OPSLIMIT_INTERACTIVE, //表示时间值越大，hash越满,暴力破解越慢
        crypto_pwhash_MEMLIMIT_INTERACTIVE, //计算hash时最多使用多少内存(卡攻击者显卡与硬件战备)
        /*这两行参数后跟着"interactive",表示这两个参数适合于
        登录这种交互式场景，使用户体验既不慢也不快*/ 
        crypto_pwhash_ALG_ARGON2ID13 //明确使用hash算法的Argon2id 1.3版本
    ) != 0){
        throw runtime_error("密码hash失败"); //运行时错误
    }

    return string(hash);
}
bool verify_password(const string& password,const string& password_hash){
    return crypto_pwhash_str_verify( //sodium.h内置的库
        password_hash.c_str(),
        password.c_str(),
        password.size() 
    ) == 0; //此函数返回0 or -1,-1表示验证失败
}
/*
一.对上述hash加密算法的机制讲解:
-- 一般的hash:对同一密码hash后结果相同，增加破解风险！
-- 加入salt的hash:即使是同一密码的hash，但因为加入了salt(随机字符串)，结果不尽相同


二.用户流程解析
1.用户注册:
输入login_pass--->Argon2id算法hash加密(明文密码+盐一起hash)存入user数据库
2.用户登录:
输入login_pass-->借助verify函数,读取对应username下的hash_password，再通过传入login_pass
去除salt后去hash再与login_pass比较




三 .关于hash后加密的字符串
包含信息:
算法
算法版本
计算参数
salt
最终 hash 结果
eg:
$argon2id$v=19$m=65536,t=2,p=1$随机salt$最终hash*
v->算法版本
m->内存成本
t->计算次数
p->并行度
最终hash:用明文密码+salt+参数算出来的结果


四.关于hash密码很难被破解的关键要素
--->单向函数
即加密很简单，反推极难
这也是为什么verify是"验证"而非破解
即拿钥匙去验证是不是对应的锁，但不能靠锁反造钥匙(虽然也有不少锁匠这么干的)
(注:其实理论上密文可逆，但时间成本太大!)
*/


int main(){
    //对hash加密算法所需的libsodium进行初始化
    if(sodium_init() < 0){
        cout << "libsodium 初始化失败" << endl;
        return 1;
    }
    MYSQL* conn  = mysql_init(nullptr);//创建一个数据库连接对象
    if(conn == nullptr){
        cout << "初始化失败" << endl;
        return 1;
    }
    MYSQL* result = mysql_real_connect(
        conn,
        "localhost", //数据库环境
        "root", //用户名
        "Pkunz20060915", //mysql密码
        "course_manager", //mysql数据库
        3306, //mysql端口
        nullptr,
        0
    );
    //成功：返回连接指针，通常就是 conn
    //失败：返回 nullptr
    //通过指针赋值，判定连接成功还是不是

    //conn = C++ 程序和 MySQL 服务器之间的通信通道,电话线，有时候mysql_query结果会留在这条电话线

    if(result == nullptr){
        cout << "连接失败:" << mysql_error(conn) << endl;
        mysql_close(conn);
        return 1; //告诉这个程序是异常结束的
    }

    cout << "连接成功" << endl;
    const char* sql =
    "use course_manager";

    if(mysql_query(conn,sql)){//mysql_query()里面，返回0表示执行成功
        cout << "无法连接课程管理助手" << endl;
        cout << "失败原因:" << mysql_error(conn) << endl;
        return 1;
    }
    else{
        cout << "连接课堂管理助手成功" << endl;
    }
    cout << "请输入用户名称及密码以登录！" << endl << endl;
    string login_name;
    string login_pass;
    getline(cin,login_name);
    int user_id;//user_id
    string klt =
    string("select * from users where user_name = '") +login_name +"'";
    if(mysql_query(conn,klt.c_str())){
        cout << "无法正常访问用户表！错误如下:" << mysql_error(conn) << endl;
        return 0;
    }
    else{
        WUTHER:
        cin >> login_pass;
        MYSQL_RES* ktll = mysql_store_result(conn);
        my_ulonglong wwqy = mysql_num_rows(ktll);
        if(wwqy == 0){
            cout << "当前用户尚未创建！已为您注册用户！" << endl << endl;
            string login_pshash = hash_password(login_pass);
            string ddy =
            string("insert into users(user_name,password_hash) values('")+login_name+string("','")+login_pshash+string("')");
            if(mysql_query(conn,ddy.c_str())){
                cout << "创建用户失败！失败原因" << mysql_error(conn) << endl << endl;
                return 1;
            }
            else{
                string jbd =
                string("select id from users where user_name = '")+login_name+string("'");
                mysql_query(conn,jbd.c_str());
                MYSQL_RES* bingo = mysql_store_result(conn);
                MYSQL_ROW temp = mysql_fetch_row(bingo);
                user_id = stoi(string(temp[0]));
                mysql_free_result(bingo);
            }
        }
        else{
            cout << "当前用户已存在！请输入密码以登录" << endl << endl;
            string jbd =
            string("select * from users where user_name = '")+login_name+string("'");
            mysql_query(conn,jbd.c_str());
            MYSQL_RES* bingo = mysql_store_result(conn);
            MYSQL_ROW temp = mysql_fetch_row(bingo);
            if(temp && temp[2] && verify_password(login_pass, string(temp[2]))){
                cout << "密码正确！已登录" << endl << endl;
                user_id = stoi(string(temp[0]));
            }
            else{
                cout << "密码不当!请重新输入!" << endl << endl;
                goto WUTHER;
            }
        }
        mysql_free_result(ktll);
    }
    string m4 =
    string("select * from setting where user_id = " ) + to_string(user_id);
    if(mysql_query(conn,m4.c_str())){
        cout << "无法获取设置信息！错误原因：" << mysql_error(conn) << endl << endl;
    }
    else{
        MYSQL_RES* fll = mysql_store_result(conn);
        my_ulonglong ind = mysql_num_rows(fll);
        if(ind == 0){
            cout << "您尚未对系统初始化！请按指引对系统初始化！" << endl;
            cout << "是否要设置任务自更新？(每次上线时对已经完成的任务或过期任务进行清理)" << endl << endl;
            int m;
            cout << "0:否;1:是" << endl;
            FLAG:
            cin >> m;
            if(m != 0 && m != 1){
                cout << "当前输入m值无效！请重新输入" << endl;
                goto FLAG;
            }
            cout << "请设置红线天数(任务临期几天时着重提醒)(取值1~100天)" << endl << endl;
            int xglk;
            label:
            cin >> xglk;
            if(xglk < 1|| xglk > 100) {
                cout << "输入值无效！重新输入" << endl;
                goto label;
            }
            string fb =
            string("insert into setting values(") + (m==0?("0,"):("1,")) + to_string(xglk) + string(",") +to_string(user_id) +string(")");
            //c风格不能直接相互拼接
            if(mysql_query(conn,fb.c_str())){
                cout << "设置失败!失败原因：" << mysql_error(conn) << endl << endl;
            }
            else{
                cout << "设置成功！" << endl << endl;
            }
        }
        mysql_free_result(fll);
    }
    //此处未来还想加个数据库自更新操作，即检测到某项任务已经比current_timestamp小
    //则标注已过期，会选择展示给用户后自删除
    string dny =
    "select * from setting where user_id = " + to_string(user_id);
    int red_day = -1;
    int situation = 0;
    if(mysql_query(conn,dny.c_str())){
        cout << "调取设置详情失败！失败原因:" << mysql_error(conn) << endl << endl;
    }
    else{
        MYSQL_RES* wcnm = mysql_store_result(conn);
        MYSQL_ROW fk = mysql_fetch_row(wcnm);
        if(fk && fk[0] && fk[0] == "1"){//boolean存储0或1,返回为"0"or"1"
            //逐一检查是否为null，保证始终合法查询
            situation = 1;
        }
        if(fk && fk[1] && atoi(fk[1])){
            red_day = atoi(fk[1]);
        }
        mysql_free_result(wcnm);
    }
    if(situation){
        string sql5 =
        "select * from tasks where (due_date < current_timestamp or done = true) and user_id = " + to_string(user_id);
        mysql_query(conn,sql5.c_str());
        MYSQL_RES* kl = mysql_store_result(conn);
        my_ulonglong rows = mysql_num_rows(kl);
        /*
        由上式引出的几个知识延申:
        1.my_ulonglong是MYSqL C API定义的一个整数类型,不用int原因是rows可能很大
        2.关于检测sql语句的影响结果
        (1)对于insert,update,selete,replace,用mysql_affected_rows()判定;
        (2)对于select,我们常通过对结果集mysql_num_rows确定选出表的行数
        ----->底层原因:两种语句返回的结果类型不同
        前者返回"状态信息集装箱"
        后者返回"结果集"
        */
        if(rows > 0){
            cout << "当前存在过期或者已完成任务!" << endl;
            cout << "过期或已完成任务如下:" << endl;
            cout << endl;
            MYSQL_ROW row;
            while((row = mysql_fetch_row(kl))){
                int jb = stoi(row[0]);
                cout << row[0] << "|"
                << row[1] << "|"
                << row[2] << "|"
                << row[3] << "|";
                if(row[4][0] == '0'){
                    cout << "未完成|";
                }
                else{
                    cout << "完成|";
                }
                cout << row[5]<<endl;
            }
            string sqljb = 
            "delete from tasks where (due_date < curdate() or done = true) and user_id = " + to_string(user_id);
            if(mysql_query(conn, sqljb.c_str()) == 0){
                cout << "已经为您自动删除过期任务!" << endl;
                cout << endl;
            }
            else{
                cout << "任务无法删除，原因:" << mysql_error(conn) << endl;
                cout << endl;
            }
        }
        mysql_free_result(kl);
    }
    while(true){
        int tp;
        cout << "--------------------" << endl;
        cout << "请输入当前想执行操作" << endl;
        cout << "1:插入task" << endl;
        cout << "2:删除task" << endl;
        cout << "3:展示任务清单" << endl; //想在后期实现重要事务提示功能，即距离五天任务
        //按距现在日期远近升序排(越紧急越靠前)
        cout << "4.标注已完成任务" << endl;
        cout << "0:退出" << endl;
        cout << "--------------------" << endl;
        cin >> tp;
        if(!tp){
            break;
        }
        switch(tp){
            case 1:{
            int T;
            cout << "请输入插入任务个数" << endl;
            cin >> T;

            //此处存在潜在bug，如输入2\n,cin只拿2.剩下\n在缓冲区
            //与后方getline()形成bug
            /*
            cin读取机制:跳过空白字符(空格，tab，\n);
            getline读取机制:从当前位置开始读，直到遇到\n为止*/

            cin.ignore(10000,'\n');
            /*从当前缓冲区位置开始，一个一个丢字符。最多10000 个。
            如果中途遇到 '\n'，把这个 '\n' 也丢掉，然后立刻停止。*/
            while(T--){
                cout << "请依次输入课程，内容，截止日期(YYYY-MM-DD)" << endl;
                string course;
                string title;
                string dueDate;
                getline(cin,course);
                getline(cin,title);
                getline(cin,dueDate);
                string sql1 = 
                "insert into tasks(course,title,due_date,user_id) values('"
                +course+"','"+title+"','"+dueDate+"',"+to_string(user_id) +")";
                if(mysql_query(conn,sql1.c_str())){ //将sql1转换成c风格字符串char*
                    cout << "插入失败" << endl;
                    cout << "失败原因:" << mysql_error(conn) << endl;
                }
                else{
                    cout << "插入成功" << endl;
                }
            }
            break;
        }

            case 2:{
            string sql3 =
            "select * from tasks where user_id = " + to_string(user_id);
            if(mysql_query(conn,sql3.c_str())){
                cout << "确认表结构失败，无法删除！" << endl;
                break;
            }
            else{
                MYSQL_RES* res = mysql_store_result(conn);
                MYSQL_ROW row;
                unordered_map<int,int> check;
                while((row = mysql_fetch_row(res))){
                    int op = stoi(row[0]);
                    check[op]++;
                    cout << row[0] << "|"
                    << row[1] << "|"
                    << row[2] << "|"
                    << row[3] << "|";
                    if(row[4][0] == '0'){
                        cout << "未完成|";
                    }
                    else{
                        cout << "完成|";
                    }
                    cout << row[5]<<endl;
                }
                mysql_free_result(res);
                int tmp;
                cout << "请输入您想删除的数据(以id为索引)" << endl;
                cin >> tmp;
                if(check[tmp] == 0){
                    cout << "您输入的索引在当前数据不存在！" << endl;
                    break;
                }
                string sql4 =
                "delete from tasks where id = " + to_string(tmp);
                if(mysql_query(conn,sql4.c_str())){
                    cout << "删除失败！失败原因" << mysql_error(conn) << endl;
                    break;
                }
                else{
                    cout << "删除成功!" << endl;
                }
            }
            break;
        }
            case 3:{
            string sql2 =
            "select * from tasks where user_id = "+to_string(user_id) + " order by due_date";
            if(mysql_query(conn,sql2.c_str())){
                cout << "查找失败！" << endl;
                cout << "失败原因:" << mysql_error(conn) << endl;
                break;
            }
            else{
                MYSQL_RES* res = mysql_store_result(conn);
                //mysql_store_result()实际上就是返回一个MYSQL_RES类型结果
                MYSQL_ROW row;//约为char** row,可以理解为row是char*类型二维字符数组
                while((row = mysql_fetch_row(res))){
                    cout << row[0] << "|"
                    << row[1] << "|"
                    << row[2] << "|"
                    << row[3] << "|";
                    if(row[4][0] == '0'){
                        cout << "未完成|";
                    }
                    else{
                        cout << "完成|";
                    }
                    cout << row[5]<<endl;
                }
                string sql7 =
                string("select * from tasks where done = 0 and due_date >= curdate() and timestampdiff(day,now(),due_date) < ")+(red_day== -1?(string("5")):(string(to_string(red_day))))+" and user_id = "+to_string(user_id)+" "+string(" order by due_date");
                mysql_query(conn,sql7.c_str());
                MYSQL_RES* res2 = mysql_store_result(conn);
                my_ulonglong total = mysql_num_rows(res2);
                if(total > 0){
                    cout << endl;
                    cout << string("其中，临近的(距离不到")+(red_day== -1?(string("5")):(string(to_string(red_day))))+string("天)未完成任务如下(要快点完成喵!)") << endl;
                    MYSQL_ROW phg;
                    while((phg = mysql_fetch_row(res2))){
                    cout << phg[0] << "|"
                    << phg[1] << "|"
                    << phg[2] << "|"
                    << phg[3] << endl;
                    }
                }
                mysql_free_result(res);
                mysql_free_result(res2);
            }
        }
        }
        cout << endl;
        cout << "3 秒后继续执行..." << endl;

        this_thread::sleep_for(chrono::seconds(3));
    
        cout << "继续执行" << endl;
    }
    mysql_close(conn);
    return 0;
}