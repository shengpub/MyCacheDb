#pragma once
#include <iostream>
#include <vector>
#include <string.h>
#include "msg.pb.h"

using namespace std ;
using namespace Messages ;


class cmdProcess
{
public:
    cmdProcess() {}
    ~cmdProcess() {}
    static void  setGet(vector<string>& res, Command& cmd) ;
    static void setSet(vector<string>&res, Command&com) ;
    static void setSave(vector<string>&res,Command& com) ;
    static void setHset(vector<string>&res,Command& com) ;
    static void setBgSave(vector<string>&res,Command& com) ;
    static void setHget(vector<string>&res,Command& com) ;
    static void getBlpop(vector<string>& res, Command& com) ;
    static void getListObject(vector<string>& res, Command& com) ;
    static void setLPopObject(vector<string>&res, Command& com) ;
    static void setZadd(vector<string>&res, Command& com) ;
    static void setZRange(vector<string>&res, Command& com) ;
    static void setSadd(vector<string>&res, Command& com) ;
    static void setSpop(vector<string>&res, Command& com) ;
private:
    
};

