#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    char str[] = "13654914070187343873";

    uint64_t seid;// = (uint64_t)strtoll(str, NULL, 10);
    sscanf(str, "%lu", &seid);

    printf("seid is dec:%lu hex:%lx\n", seid, seid);

}
