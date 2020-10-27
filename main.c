#include "delay.h"

int main(void)
{
    // DELAY_INIT;
    DELAY_INIT2;

    while (1)
    {
        // DELAY_US(499000);
        DELAY_US2(500000, 10000, 5000, 1000, 200);//4级逼近

        showTickUs(500000);

        workerRandom(499000);
        // worker(499000);
    }
    return 0;
}
