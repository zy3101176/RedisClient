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
using namespace std;
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

    bool HMGet(const string &key, const vector<string> &field, vector<string> &value);
    bool HMSet(const string &key, const vector<string> &field, const vector<string> &value);

    bool SelectDataBase(unsigned int dbnumber);
    bool SetTimeoutTime(unsigned int time);      //us

private:
    bool CommandInteger(const char* cmd, ...);
    bool CommandString(string &data, const char* cmd, ...);
    bool RedisReConnection();
    bool CheckReply(const redisReply *reply);
    void FreeReply(const redisReply *reply);

private:
    string mHost;
    unsigned int mPort;
    string mPassword;
    unsigned int mTimeout;
    unsigned int mOperatorTimeout;
    unsigned long mReconnectIntervalTime;
    struct timeval mLastFalseTime;
    redisContext *mCtx;
    bool mIsConnectOk;
};

#endif //REDISCLIENT_REDIS_CLIENT_H
