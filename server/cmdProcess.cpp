#include "cmdProcess.h"

//将结果集返回
int cmdProcess :: findCmd(shared_ptr<Command>tmp) {
    int ret = 0 ;
    pair<string, vector<string>>t;
    string cc = tmp->cmd() ;
    //查找消息
    ret = cmdSet_->findCmd(cc) ;
    return ret ;
}

//向数据库中导入数据
int cmdProcess :: initRedis() {
    //导入数据库中的数据
    cmdSet_->initRedis() ;
}
//消息回调
void cmdProcess :: timeCb() {
    //保存当前数据中的所有数据
}

void cmdProcess :: initCmdCb() {
    cmdSet_->initCmdCb() ;
}

//处理消息
int cmdProcess :: processMsg(shared_ptr<aeEvent>&tmp) {
    if(ptr == nullptr) {
        ptr = aofRecord::getLogObject() ;
    }
    string seq = "" ;
    int flag = 0 ;
    buffer* bf = tmp->getBuf() ;
    //获取到对端序列化的结果
    const char* buff = bf->getBuf() ;
    //获取对端序列化到结果
    //反序列化,弱引用
    shared_ptr<Command>wcmd = rc->getParseString(buff) ;
    //是修改类型的命令
    //获取到相应的智能指针后，进行解析
    int ret = findCmd(wcmd) ;
    //记录日志
    shared_ptr<Response> res = nullptr;
    //解析命令不合法
    if(ret == NOT_FOUND) {
        //给客户端发送处理结果
        //序列化，并向客户端发送消息，暂时不做处理
        res = backInfo :: notFind() ;
    } 
    else {
        //处理命令
        string cc = wcmd->cmd() ;
        int num = wcmd->num() ;
        //获取当前所在数据库
        //没找到
        //只需要关注blpop是否成功，不成功将当前处理的事件加到
        //队列中，并设置定时器
        cmdSet_->redisCommandProc(num, wcmd) ;
        res = cmdSet_->getResponse() ;
    } 

    if(flag != 1) {
        res->set_seq(seq) ;
        rc->response(res, tmp->getConnFd()) ;
        bf->clear() ;
    }
    //获取到响应的结果
    return 1 ;
}

int cmdProcess :: sendMsg(shared_ptr<aeEvent>tmp) {
    int fd = tmp->getConnFd() ;
    Command cmd ;
    char buf[SIZE] ;
    cmd.set_status(0) ;
    int ret = write(fd, buf, sizeof(buf)) ;
    if(ret < 0) {
        cout << __FILE__ << "     " << __LINE__ << endl ;
        return -1 ;
    }
    return 1 ;
}

