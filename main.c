#include "delay.h"

int main(void)
{
    //DELAY_INIT;
    DELAY_INIT2;

    while (1)
    {
        //DELAY_US(500000);
        DELAY_US2(500000, 50);

        showTickUs(500000);

        workerRandom(499000);
        // worker(499000);
    }
    return 0;
}
