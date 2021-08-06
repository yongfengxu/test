#include <stdio.h>
#include <hiredis/hiredis.h>

int main(void) {
    redisContext *context;
    redisReply *reply;

    context = redisConnect("127.0.0.1", 6379);
    if (!context) {
        fprintf(stderr, "Error:  Can't connect to Redis\n");
        return -1;
    }

    reply = redisCommand(context, "SET %s %s", "foo", "bar");
    if (!reply || context->err) {
        fprintf(stderr, "Error:  Can't send command to Redis\n");
        return -1;
    }

    freeReplyObject(reply);

    reply = redisCommand(context, "GET foo");
    if (!reply || context->err || reply->type != REDIS_REPLY_STRING) {
        fprintf(stderr, "Error:  Can't send command to Redis\n");
        return -1;
    }

    printf("foo = %s\n", reply->str);
    freeReplyObject(reply);

    return 0;
}
