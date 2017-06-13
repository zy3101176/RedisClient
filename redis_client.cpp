//
// Created by 朱原熯 on 2017/6/13.
//

#include "redis_client.h"

RedisClient::RedisClient() {

}

RedisClient::~RedisClient() {

}

void RedisClient::ClientInit(const stirng &host, unsigned int port, const string &password,
                             unsigned int ReconnectIntervalTime) {

}

bool RedisClient::Get(const string &key, string &value) {

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

bool RedisClient::MSet(const vector <string> &keys, vector <string> &value) {

}

bool RedisClient::HMGet(const string &key, const vector <string> &field, vector <string> &value) {

}

bool RedisClient::HMSet(const string &key, const vector <string> &field, const vector <string> &value) {

}

bool RedisClient::HMGet(const string &key, const vector <string> &field, vector <string> &value) {

}

bool RedisClient::SelectDataBase(unsigned int dbnumber) {

}

bool RedisClient::SetTimeoutTime(unsigned int time) {

}

bool RedisClient::RedisConnection() {

}

bool RedisClient::RedisReConnection() {

}

bool RedisClient::ChickReply(const redisReply *reply) {

}

bool RedisClient::FreeReply(const redisReply *reply) {

}