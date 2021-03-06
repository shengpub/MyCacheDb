#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include "aeEvent.h"
#include "msg.pb.h"

using namespace std ;
using namespace Messages ;

class rpc ;


shared_ptr<::Command> requestMethod(const char* s) ;

class rpc {
    typedef function<void(shared_ptr<Response>res, int fd)> request ;
    typedef function<shared_ptr<::Command>(const char*)> parse ;
public:
    rpc() ;
    ~rpc() {}
public :
    static string getParseString() ;
    //设置相应的callMethod方法
    shared_ptr<Command>getParseString(const char* buff) ;
    int response(shared_ptr<Response>res, int fd) ;
    //设置相应的callMethod方法
    //反序列化函数
    void setCallMethod(parse par) { parseMethod = move(par) ;}
    ///反序列化
private : 
    shared_ptr<Command>cmd ;
 //   request requestMethod ;
    //反序列化函数
    parse parseMethod ;   
    int a ;
};

