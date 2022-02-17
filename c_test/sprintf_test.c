#include <stdio.h>
#include <string.h>
#include <inttypes.h>

int main()
{
    uint64_t trackuid = 1;
    char buff[21];

    // copy to buffer
    sprintf(buff, "%" PRIu64, trackuid);

    printf("str:%s len:%d\n", buff, strlen(buff));
}
