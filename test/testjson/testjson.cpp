#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

//json序列化示例1
string func1(){
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello , what are you doing?";

    //网络里用字符串表示
    string sendBuf = js.dump(); //json数据对象 => 序列化成 json字符串
    //cout<<sendBuf.c_str()<<endl;

    //键值对(类似链式哈希表，无序)
    //cout<<js<<endl;

    return sendBuf;
}

//json序列化示例2
string func2(){
    json js;
    //添加数组
    js["id"] ={1,2,3,4,5};
    //添加key-value
    js["name"] = "zhang san";
    //添加对象
    js["msg"]["zhang san"] = "hello";
    js["msg"]["li si"] = "hello";
    //相当于下面一次性添加数组对象
    js["msg"]={{"zhang san","hello"},{"li si","hello"}};
    
    string sendBuf = js.dump();
    return sendBuf;
}

//json序列化示例3
string func3(){
    json js;
    //直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
    //直接序列化一个map容器
    map<int,string> m;
    m.insert({1,"黄山"});
    m.insert({2,"华山"});
    m.insert({3,"泰山"});
    js["path"] = m;

    string sendBuf = js.dump();
    return sendBuf;
}


int main(){
    string recvBuf = func1();
    //数据的反序列化  json字符串 =》反序列化成 数据对象（看作容器，方便访问）
    json jsbuf = json::parse(recvBuf);
    cout<<jsbuf["msg_type"]<<endl;
    cout<<jsbuf["from"]<<endl;
    cout<<jsbuf["to"]<<endl;
    cout<<jsbuf["msg"]<<endl;

    string recvBuf2 = func2();
    //数据的反序列化  json字符串 =》反序列化成 数据对象（看作容器，方便访问）
    json jsbuf2 = json::parse(recvBuf2);
    cout<<jsbuf2["id"]<<endl;
    auto arr = jsbuf2["id"];
    cout<<arr[2]<<endl;
    cout<<jsbuf2["name"]<<endl;
    cout<<jsbuf2["msg"]<<endl;
    auto msgjs = jsbuf2["msg"];
    cout<<msgjs["zhang san"]<<endl;
    cout<<msgjs["li si"]<<endl;
    
    string recvBuf3 = func3();
    //数据的反序列化  json字符串 =》反序列化成 数据对象（看作容器，方便访问）
    json jsbuf3 = json::parse(recvBuf3);
    vector<int> vec = jsbuf3["list"]; //js对象里面的数组类型，直接放入vector容器中
    for(int &v: vec){
        cout<<v<<" ";
    }
    cout<<endl;

   map<int,string> mymap = jsbuf3["path"];
   for(auto &p :mymap){
    cout<<p.first<<" "<<p.second<<endl;
   }

    return 0;
}