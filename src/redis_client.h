//
// Created by 朱原熯 on 2017/6/13.
//

#ifndef REDISCLIENT_REDIS_CLIENT_H
#define REDISCLIENT_REDIS_CLIENT_H
#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <strings.h>

using std::string;
using std::iostream;
using std::vector;

class RedisClient
{
public:
    RedisClient();
    ~RedisClient();

    void ClientInit (const string &host, unsigned int port,
                     const string &password, unsigned int ReconnectIntervalTime = 5000000);  //us
    bool RedisConnection();
    bool Get(const string &key, string &value);
    bool Set(const string &key, const string &value);
    bool Del(const string &key);
    bool Del(const vector<string> &keys);

    bool HGet(const string &key, const string &field, string &value);
    bool HSet(const string &key, const string &field, const string &value);
    bool HDel(const string &key, const string &field);
    bool HDel(const string &key, const vector<string> &fields);

    bool MGet(const vector<string> &keys, vector<string> &values);
    bool MSet(const vector<string> &keys, const vector<string> &values);

    bool HMGet(const string &key, const vector<string> &fields, vector<string> &values);
    bool HMSet(const string &key, const vector<string> &fields, const vector<string> &values);

    bool SelectDataBase(const string & dbnumber);
    bool SetOperateTimeout(struct timeval time);      //us
    void SetReconnectIntervalTime(unsigned long ReconnectIntervalTime);

    bool CommandInteger(const char* cmd, ...);
    bool CommandString(string &data, const char* cmd, ...);
    bool CommandArrey(vector<string> &datas, const char *cmd, ...);

private:
    bool RedisReConnection();
    int CheckReply(const redisReply *reply);
    void FreeReply(const redisReply *reply);
    void MarkError();
    bool CheckConnectionStatus();

private:
    string mHost;
    unsigned int mPort;
    string mPassword;
    unsigned int mTimeout;
    unsigned long mReconnectIntervalTime;
    struct timeval mLastFalseTime;
    redisContext *mCtx;
    bool mIsConnectOk;
    string mLastDatabase;
};

#endif //REDISCLIENT_REDIS_CLIENT_H
