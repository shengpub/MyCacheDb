#pragma once
#include<iostream>
#include <string>
#include <list>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include "msg.pb.h"
using namespace Messages ;
using namespace std ;

class redisDb ;
class dbObject ;
class setCommand ;
class factory ;
//数据库对象
class redisDb {
public :
    redisDb() {  }
    ~redisDb() {  } 
private :
    //数据库编号
    int num ;
    vector<shared_ptr<dbObject>> db ;
public :
    string findGetRequest(string name) ;
    void queryDb(shared_ptr<Response>& res, shared_ptr<Command>& cmd) ;
    void append(shared_ptr<dbObject>rdb) { db.push_back(rdb); }
    //命令键
    int isExist(shared_ptr<Command>&cmds) ;
    //获取key
    //删除当前数据库中的一个对象
    void del() {
    }
} ;

class dbObject {
public:
    dbObject() {}
    virtual ~dbObject() {}
public :
    //set操作
    virtual void setNum(int num) = 0;
    virtual void setKey(string k) = 0;
    virtual void setValue(string v) = 0;
    virtual void setName(string name) = 0;

    virtual string getKey() = 0;
    virtual string getValue() = 0;
    //获取命令编号
    virtual int getNum() = 0 ;
    virtual string  getName() = 0;
private :
    //保存所有键的过期时间
    //redis对象管理dict对象
    //shared_ptr<dict>dic ;
};

//set对象
class setCommand : public dbObject {
public :
    setCommand() {}
    ~setCommand() {}
public :
    void setKey(string k) { this->key = k ; } 
    void setValue(string value)  { this->value = value ; }
    void setName(string name) { this->name = name ; }
    void setNum(int num) { this->num = num ; }

    string  getName() { return name ; }
    string getKey() { return key ; }
    int getNum() { return num ; }
    string getValue() { return value ; }
    
public :
    //命令名称
    string name ;
    //当前设置的超时时间
    map<string, long long> expire ;
    //所在数据库编号
    int num ;
    //命令键值
    string key ;
    string value ;
} ;

class getCommand : public dbObject {
    
} ;

class hsetCmd : public dbObject {
public :
    int num ;
    map<string, map<string, string>>hset ;
} ;
/*
//字典
class dict {
private:
    //redisDb中的list对象，键值对，键不能有重复
    map<string, list<string>> ls ;
    map<string, set<string>> comset ;
    //hash集合
    map<string, string>common ;
} ;*/
class factory {
public :
    static shared_ptr<dbObject> getObject(string cmd) {
        if(cmd == "set") {
            shared_ptr<setCommand> tmp(new setCommand) ;
            return tmp ;
        }   
        else {
            return nullptr ;
        }
    }
} ;

