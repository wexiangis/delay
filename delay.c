#include <stdio.h>    // 引入 NULL
#include <unistd.h>   // 引入 usleep()
#include <string.h>   // 引入 memcpy()
#include <stdlib.h>   // 引入 rand()
#include <time.h>     // 引入 time()
#include <sys/time.h> // 引入 struct timeval

// 不太准确的延时
void sleepUs(long int us)
{
    usleep(us);
}

// 稍微准确的延时
void delayUs(long int us)
{
    struct timeval tv;
    tv.tv_sec = us / 1000000;
    tv.tv_usec = us % 1000000;
    select(0, NULL, NULL, NULL, &tv);
}

// 固定时长的干活
void worker(int us)
{
    delayUs(us);
}

// 随机时长的干活[1, us]之间
void workerRandom(int us)
{
    static char srandFlag = 0;
    int randUs;
    //以当前时间为随机种子(只需初始化一次)
    if (!srandFlag) {
        srand((int)time(0));
        srandFlag = 1;
    }
    //取一个[1, us]之间的随机数
    randUs = rand() % us + 1;
    //随机延时一段时间
    delayUs(randUs);
}

// 获取系统tick可以作为us时长参考
long int getTickUs(void)
{
    struct timeval tv = {0};
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000u + tv.tv_usec;
}

// 打印时间戳
void showTickUs(int targetUs)
{
    static struct timeval tv_old = {0};
    struct timeval tv = {0};
    int hour, min, sec, ms, us, err, err2;
    gettimeofday(&tv, NULL);
    hour = (int)(tv.tv_sec / 3600 % 24 + 8);
    if (hour >= 24)
        hour -= 24;
    min = (int)(tv.tv_sec % 3600 / 60);
    sec = (int)(tv.tv_sec % 60);
    ms = (int)(tv.tv_usec / 1000);
    us = (int)(tv.tv_usec % 1000);
    if (tv_old.tv_usec == 0)
        err = err2 = 0;
    else {
        err = (int)((tv.tv_sec - tv_old.tv_sec) * 1000000 + (tv.tv_usec - tv_old.tv_usec));
        err2 = err - targetUs;
    }
    printf("[%02d:%02d:%02d:%03d:%03d -- %02d:%03d:%03d] %5d\r\n",
           hour, min, sec, ms, us, err / 1000000, err % 1000000 / 1000, err % 1000, err2);
    memcpy(&tv_old, &tv, sizeof(struct timeval));
}
