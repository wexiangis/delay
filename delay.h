#ifndef _DELAY_H_
#define _DELAY_H_

// ----- 不太准确的延时 -----

void sleepUs(long int us);

// ----- 稍微准确的延时 -----

void delayUs(long int us);

// ----- 自己矫正的延时 -----

#define DELAY_INIT \
    long int _tick1 = 0, _tick2;

#define DELAY_US(us)                             \
    _tick2 = getTickUs();                        \
    if (_tick2 > _tick1 && _tick2 - _tick1 < us) \
        delayUs(us - (_tick2 - _tick1));         \
    _tick1 = getTickUs();

// ----- 逐级逼近式延时 -----

#define DELAY_INIT2 \
    long int _tick = 0, _tickErr;

#define DELAY_US2(us, err)             \
    _tickErr = getTickUs() - _tick;    \
    if (_tickErr > 0 && us > _tickErr) \
    {                                  \
        _tickErr = us - _tickErr;      \
        if (_tickErr > err)            \
        {                              \
            delayUs(_tickErr / 2);     \
            continue;                  \
        }                              \
    }                                  \
    _tick = getTickUs();

// 获取系统tick可以作为us时长参考
long int getTickUs(void);

// 打印时间戳
void showTickUs(long int targetUs);

// ----- 假装在干活 -----

// 固定时长的干活
void worker(long int us);

// 随机时长的干活[1, us]之间
void workerRandom(long int us);

#endif
