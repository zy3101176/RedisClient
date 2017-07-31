#include <iostream>
#include "redis_client.h"
using namespace std;
int main()
{
    RedisClient a;
    a.ClientInit("127.0.0.1", 6379, "zhuyuanhan");
    a.RedisConnection();
    a.Set("1","2");
    return 0;
}