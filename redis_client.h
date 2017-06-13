//
// Created by 朱原熯 on 2017/6/13.
//

#ifndef REDISCLIENT_REDIS_CLIENT_H
#define REDISCLIENT_REDIS_CLIENT_H
#include "hiredis.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

class RedisClient
{
public:
    RedisClient();
    ~RedisClient();

    void ClientInit (const stirng &host, unsigned int port,
                     const string &password, unsigned int ReconnectIntervalTime = 5000000);  //us

    bool Get(const string &key, string &value);
    bool Set(const string &key, const string &value);
    bool Del(const string &key);

    bool HGet(const string &key, const string &field, string &value);
    bool HSet(const string &key, const string &field, const string &value);
    bool HDel(const string &key, const string &field);

    bool MGet(const vector<string> &keys, vector<string> &value);
    bool MSet(const vector<string> &keys, vector<string> &value);

    bool HMGet(const string &key, const vector<string> &field, vector<string> &value);
    bool HMSet(const string &key, const vector<string> &field, const vector<string> &value);

    bool SelectDataBase(unsigned int dbnumber);
    bool SetTimeoutTime(unsigned int time);      //us

private:
    bool RedisConnection();
    bool RedisReConnection();
    bool ChickReply(const redisReply *reply);
    bool FreeReply(const redisReply *reply);
};

#endif //REDISCLIENT_REDIS_CLIENT_H
