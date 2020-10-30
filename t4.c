#include <math.h>
#include <pthread.h>
#include "delay.h"

void busy(void)
{
    int count;
    double sum = 1.23456;
    while(1) {
        sleepUs(5);
        for (count = 0; count < 10000; count++)
            sum *= atan2(1.23456, 3.45678);
    }
}

int main(void)
{
    DELAY_INIT2;

    pthread_t ph;
    pthread_create(&ph, NULL, (void*)&busy, NULL);

    while (1)
    {
        DELAY_US2(500000, 50);
        showTickUs(500000);

        //working
        workerRandom(499000);
    }
    return 0;
}
