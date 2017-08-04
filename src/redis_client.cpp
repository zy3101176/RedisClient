//
// Created by 朱原熯 on 2017/6/13.
//

#include "redis_client.h"

RedisClient::RedisClient():mCtx(NULL) {}

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
    mIsConnectOk = true;
    mLastDatabase = "0";
}

bool RedisClient::Get(const string &key, string &value) {
    return CommandString(value, "GET %s", key.c_str());
}

bool RedisClient::Set(const string &key, const string &value) {
    return CommandInteger("SET %s %s", key.c_str(), value.c_str());
}

bool RedisClient::Del(const string &key) {
    return CommandInteger("DEL %s", key.c_str());
}

bool RedisClient::Del(const vector<string> &keys){
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(keys.empty()){
        return false;
    }
    int len = 0;
    char *msg[keys.size()+1];
    msg[len++] = (char *)"DEL";
    for(int i = 0; i < keys.size(); i++){
        msg[len++] = (char *)keys[i].c_str();
    }
    const char **argv = (const char **)msg;
    redisReply *reply = static_cast<redisReply*> (redisCommandArgv(this->mCtx, len, argv, NULL));
    if(CheckReply(reply)){
        bRet = true;
    }
    FreeReply(reply);
    return bRet;
}

bool RedisClient::HGet(const string &key, const string &field, string &value) {
    return CommandString(value, "HGET %s %s", key.c_str(), field.c_str());
}

bool RedisClient::HSet(const string &key, const string &field, const string &value) {
    return CommandInteger("HSET %s %s %s", key.c_str(), field.c_str(), value.c_str());
}

bool RedisClient::HDel(const string &key, const string &field) {
    return CommandInteger("HDEL %s %s", key.c_str(), field.c_str());
}

bool RedisClient::HDel(const string &key, const vector<string> &fields){
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(fields.empty()){
        return false;
    }
    int len = 0;
    char *msg[fields.size()+2];
    msg[len++] = (char *)"HDEL";
    msg[len++] = (char *)key.c_str();
    for(int i = 0; i < fields.size(); i++){
        msg[len++] = (char *)fields[i].c_str();
    }
    const char **argv = (const char **)msg;
    redisReply *reply = static_cast<redisReply*> (redisCommandArgv(this->mCtx, len, argv, NULL));
    if(CheckReply(reply)){
        bRet = true;
    }
    FreeReply(reply);
    return bRet;
}
bool RedisClient::MGet(const vector <string> &keys, vector <string> &values) {
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(keys.empty()){
        return false;
    }
    int len = 0;
    char *msg[keys.size()+1];
    msg[len++] = (char *)"MGET";
    for(int i = 0; i < keys.size(); i++){
        msg[len++] = (char *)keys[i].c_str();
    }
    const char **argv = (const char **)msg;
    redisReply *reply = static_cast<redisReply*>(redisCommandArgv(this->mCtx, len, argv, NULL));
    if(CheckReply(reply)){
        for(size_t i = 0; i < reply->elements; i++){
            string value;
            value.assign(reply->element[i]->str, reply->element[i]->len);
            values.push_back(value);
        }
        bRet = true;
    }
    FreeReply(reply);
    return bRet;
}

bool RedisClient::MSet(const vector <string> &keys, const vector <string> &values) {
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(keys.size() != values.size()) {
        return false;
    }
    int len = 0;    //指令长度
    char *msg[keys.size()*2+1];
    msg[len++] = (char *)"MSET";
    for(int i = 0; i < keys.size(); i++) {
        msg[len++] = (char *)keys[i].c_str();
        msg[len++] = (char *)values[i].c_str();
    }
    const char **argv = (const char **) msg;
    redisReply *reply = static_cast<redisReply*>(redisCommandArgv(this->mCtx, len, argv, NULL));
    if (CheckReply(reply)) {
        bRet = true;
    }
    FreeReply(reply);
    return bRet;
}

bool RedisClient::HMGet(const string &key, const vector <string> &fields, vector <string> &values) {
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(fields.empty()){
        return false;
    }
    int len = 0;
    char *msg[fields.size()+2];
    msg[len++] = (char *)"HMGET";
    msg[len++] = (char *)key.c_str();
    for(int i = 0; i < fields.size(); i++){
        msg[len++] = (char *)fields[i].c_str();
    }
    const char **argv = (const char **)msg;
    redisReply *reply = static_cast<redisReply*>(redisCommandArgv(this->mCtx, len, argv, NULL));
    if(CheckReply(reply)){
        for(size_t i = 0; i < reply->elements; i++){
            string value;
            value.assign(reply->element[i]->str, reply->element[i]->len);
            values.push_back(value);
        }
        bRet = true;
    }
    FreeReply(reply);
    return bRet;
}

bool RedisClient::HMSet(const string &key, const vector <string> &fields, const vector <string> &values) {
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(fields.size() != values.size()) {
        return false;
    }
    int len = 0;    //指令长度
    char *msg[fields.size()*2+2];
    msg[len++] = (char *)"HMSET";
    msg[len++] = (char *)key.c_str();
    for(int i = 0; i < fields.size(); i++) {
        msg[len++] = (char *)fields[i].c_str();
        msg[len++] = (char *)values[i].c_str();
    }
    const char **argv = (const char **) msg;
    redisReply *reply = static_cast<redisReply*>(redisCommandArgv(this->mCtx, len, argv, NULL));
    if (CheckReply(reply)) {
        bRet = true;
    }
    FreeReply(reply);
    return bRet;
}

bool RedisClient::SelectDataBase(const string &dbnumber) {
    string status;
    mLastDatabase = dbnumber;
    return CommandString(status,"select %s",dbnumber.c_str()) && !strcasecmp(status.c_str(), "OK");
}

bool RedisClient::SetOperateTimeout(struct timeval time) {
    if(!redisSetTimeout(mCtx, time)){
        return true;
    }
}

void RedisClient::SetReconnectIntervalTime(unsigned long ReconnectIntervalTime){
    mReconnectIntervalTime = ReconnectIntervalTime;
    return ;
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
        redisReply *reply = static_cast<redisReply *>(redisCommand(this->mCtx, "AUTH %s", mPassword.c_str()));
        if(reply == NULL || strcasecmp(reply ->str, "OK") != 0){
            bRet = false;
        }
        else{
            bRet = true;
            SelectDataBase(mLastDatabase);
        }
        FreeReply(reply);
    }
    if(!bRet) {
        MarkError();
    }
    return bRet;
}

bool RedisClient::RedisReConnection() {
    if(mCtx != NULL){
        redisFree(mCtx);
        mCtx = NULL;
    }
    return RedisConnection();
}

int RedisClient::CheckReply(const redisReply *reply) {
    if(reply == NULL){
        MarkError();
        return 0;
    }
    switch(reply->type){
        case REDIS_REPLY_STRING:{
            return REDIS_REPLY_STRING;
        }
        case REDIS_REPLY_ARRAY:{
            return REDIS_REPLY_ARRAY;
        }
        case REDIS_REPLY_INTEGER:{
            return REDIS_REPLY_INTEGER;
        }
        case REDIS_REPLY_NIL:{
            return REDIS_REPLY_NIL;
        }
        case REDIS_REPLY_STATUS:{
            if(strcasecmp(reply->str,"OK") == 0){
                return REDIS_REPLY_STATUS;
            }
            else{
                MarkError();
                return 0;
            }
        }
        case REDIS_REPLY_ERROR:{
            MarkError();
            return 0;
        }
        default:{
            MarkError();
            return 0;
        }
    }
}

void RedisClient::FreeReply(const redisReply *reply) {
    if(reply != NULL){
        freeReplyObject((void *) reply);
    }
}

bool RedisClient::CommandInteger(const char *cmd, ...) {
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(this->mCtx == NULL){
        return bRet;
    }
    va_list args;
    va_start(args,cmd);
    redisReply *reply = static_cast<redisReply *>(redisvCommand(this->mCtx, cmd, args));
    va_end(args);
    if(CheckReply(reply)){
        bRet = true;
    }
    FreeReply(reply);
    return bRet;
}

bool RedisClient::CommandString(string &data, const char *cmd, ...) {
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(this->mCtx == NULL){
        return bRet;
    }
    va_list args;
    va_start(args, cmd);
    redisReply *reply = static_cast<redisReply *>(redisvCommand(this->mCtx, cmd, args));
    va_end(args);
    if(CheckReply(reply)){
        data.assign(reply->str, reply->len);
        bRet = true;
    }
    return bRet;
}

bool RedisClient::CommandArrey(vector<string> &datas, const char *cmd, ...) {
    if(!CheckConnectionStatus()){
        return false;
    }
    bool bRet = false;
    if(this->mCtx == NULL){
        return bRet;
    }
    va_list args;
    va_start(args, cmd);
    redisReply *reply = static_cast<redisReply *>(redisvCommand(this->mCtx, cmd, args));
    va_end(args);
    if(CheckReply(reply)){
        for(size_t i = 0; i < reply->elements; i++){
            string data;
            data.assign(reply->element[i]->str, reply->element[i]->len);
            datas.push_back(data);
        }
        bRet = true;
    }
    return bRet;
}

void RedisClient::MarkError() {
    mIsConnectOk = false;
    gettimeofday(&mLastFalseTime,NULL);
    return;
}

bool RedisClient::CheckConnectionStatus() {
    if(mIsConnectOk) return true;
    struct timeval now;
    gettimeofday(&now, NULL);
    unsigned long intervalTime = (unsigned long) (1000000 * (now.tv_sec - mLastFalseTime.tv_sec) + now.tv_usec - mLastFalseTime.tv_usec);
    if(intervalTime > mReconnectIntervalTime){
        if(RedisReConnection()){
            mIsConnectOk = true;
        }
    }
    return mIsConnectOk;
}

