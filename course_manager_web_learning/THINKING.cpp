#define WIN32_LEAN_AND_MEAN
/*计划：
HttpRequest      (done)
->HttpResponse   (done)
->toString()
->route()
->send()
->静态文件服务*/
#include <winsock2.h>
#include <mysql.h>
#include <sodium.h>

#include <cctype>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const int SERVER_PORT = 8088;


typedef struct httpRequest{
    string method;
    string rawPath;
    string path;
    string query;
    string version;
    map<string, string> headers;
    string body;
}httpRequest;

/*httpResponse格式:
eg:
HTTP/1/1 200 OK
Content-Type: text/html
Content-length: 13

hello world!*/
typedef struct httpResponse{
    int statusCode;
    string statusMessage;
    map<string,string> headers;
    string body;

}httpResponse;

//respnse字符串搭建
string buildResponse(httpResponse resp){
    string result = "HTTP/1/1 ";
    if(stoi(resp.statusMessage)/100 == 2){
        result += to_string(200)+ " OK\r\n";
        for(auto& [key,value] : resp.headers){
            string tmp;
            for(auto ch : key){
                tmp += to_string(tolower(ch));
            }
            if(tmp == "content-length") break;
            result += key +": " + value+"\r\n";
        }
        result += "Content-Length: " + to_string(resp.body.size());
        result += "\r\n\r\n";
        result += resp.body;
        return result;
    }
    return "Can not bulid";
}

//request字符串拆分提取
httpRequest parseRequest(const string& m){
    httpRequest cp;
    istringstream stream(m);
    string line;
    if(getline(stream,line)){
        if(!line.empty()&&line.back() == '\r'){
            line.pop_back();
        }
    }
    istringstream tmp(line);
    tmp >> cp.method >> cp.rawPath >> cp.version;
    while(getline(stream,line) && line.find(":") != string::npos){
        if(!line.empty()&&line.back()){
            line.pop_back();
        }
        size_t pos = line.find(":");
        string t1 = line.substr(0,pos);
        string t2 = line.substr(pos+1);
        if(t2[0] == ' '){
            t2.erase(t2.begin());
        }
        cp.headers[t1] = t2;
    }
    if(cp.method == "POST"){
        if(size_t pro = m.find("\r\n\r\n")){
            cp.body = m.substr(pro+4);
        }
    }
    cp.path = cp.rawPath;
    if((cp.rawPath).find("?") != string::npos){
        size_t  mmp = (cp.rawPath).find("?");
        cp.path = (cp.rawPath).substr(0,mmp);
        cp.query = (cp.rawPath).substr(mmp+1);
    }
}
