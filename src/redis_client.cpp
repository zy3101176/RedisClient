//
// Created by 朱原熯 on 2017/6/13.
//

#include "redis_client.h"

RedisClient::RedisClient() {

}

RedisClient::~RedisClient() {
    if(mCtx != NULL)
        redisFree(mCtx);
    mCtx = NULL;
}

void RedisClient::ClientInit(const string &host, unsigned int port, const string &password,
                             unsigned int reconnectIntervalTime) {
    mHost = host;
    mPort = port;
    mPassword = password;
    mReconnectIntervalTime = reconnectIntervalTime;
    mIsConnectOk = false;
}

bool RedisClient::Get(const string &key, string &value) {
    return CommandInteger( "SET %s %s", key.c_str(), value.c_str());
}

bool RedisClient::Set(const string &key, const string &value) {

}

bool RedisClient::Del(const string &key) {

}

bool RedisClient::HGet(const string &key, const string &field, string &value) {

}

bool RedisClient::HSet(const string &key, const string &field, const string &value) {

}

bool RedisClient::HDel(const string &key, const string &field) {

}

bool RedisClient::MGet(const vector <string> &keys, vector <string> &value) {

}

bool RedisClient::MSet(const vector <string> &keys, vector <string> &value) {

}

bool RedisClient::HMGet(const string &key, const vector <string> &field, vector <string> &value) {

}

bool RedisClient::HMSet(const string &key, const vector <string> &field, const vector <string> &value) {

}

bool RedisClient::SelectDataBase(unsigned int dbnumber) {

}

bool RedisClient::SetTimeoutTime(unsigned int time) {

}

bool RedisClient::RedisConnection() {
    bool bRet = false;
    struct timeval timeoutVal;
    timeoutVal.tv_sec = mTimeout;
    timeoutVal.tv_usec = 0;
    if(mTimeout == 0){
        mCtx = redisConnect(mHost.c_str(), mPort);
    }
    else {
        mCtx = redisConnectWithTimeout(mHost.c_str(), mPort, timeoutVal);
    }
    if(mCtx == NULL || mCtx->err ) {
        if(mCtx != NULL){
            redisFree(mCtx);
            mCtx = NULL;
        }
    }
    if(mPassword.size() == 0){
        bRet = true;
    }
    else{
        redisReply *reply = static_cast<redisReply *>(this->mCtx, "AUTH %s", mPassword.c_str());
        if(reply == NULL || strcasecmp(reply ->str, "OK") != 0){
            bRet = false;
        }
        else{
            bRet = true;
        }
        freeReplyObject(reply);
    }
    //if(!bRet) {
    //
    //}
    return bRet;
}

bool RedisClient::RedisReConnection() {

}

bool RedisClient::ChickReply(const redisReply *reply) {

}

void RedisClient::FreeReply(const redisReply *reply) {
    if(reply != NULL){
        freeReplyObject((void *) reply);
    }
}

bool RedisClient::CommandInteger(const char *cmd, ...) {
    bool bRet = false;
    if(this->mCtx == NULL){
        return bRet;
    }
    va_list args;
    va_start(args,cmd);
    redisReply *reply = static_cast<redisReply *>(redisCommand(this->mCtx, cmd, args));
    va_end(args);
    if(ChickReply(reply)){
        bRet = true;
    }
    FreeReply(reply);
    return bRet;
}
