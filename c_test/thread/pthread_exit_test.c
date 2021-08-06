#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


struct foo
{
    int a;
    int b;
    int c;
    int d;
};

void printfoo(const char* s, const struct foo* fp)
{
    printf("%s", s);

    printf(" structure at 0x%lx\n", (unsigned long)fp);
    printf(" foo.a = %d\n", fp->a);
    printf(" foo.b = %d\n", fp->b);
    printf(" foo.c = %d\n", fp->c);
    printf(" foo.d = %d\n", fp->d);
}

void
printids(const char* s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void*
thr_fn1(void* arg)
{
    printids("thread1:");
    struct foo* f = malloc(sizeof(struct foo));

    f->a = 1;
    f->b = 2;
    f->c = 3;
    f->d = 4;

    printfoo("thread 1:\n", f);
    pthread_exit((void*)f);
}


void*
thr_fn2(void* arg)
{
    printids("thread2:");
    pthread_exit((void*)0);
}

int main()
{
    pthread_t ntid1, ntid2;
    int err;

    struct foo* fp;

    err = pthread_create(&ntid1, NULL, thr_fn1, NULL);
    if (err != 0)
    {
        printf("can't create thread1\n");
    }

    err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
    if (err != 0)
    {
        printf("can't create thread2\n");
    }

    err = pthread_join(ntid1,(void*) &fp);

    err = pthread_join(ntid2,NULL);
    sleep(1);

    printfoo("parent:\n", fp);
}
