#include "thread_algorithm.h"

/* Algorithm Thread entry function */
void thread_algorithm_entry(void)
{
    /* TODO: add your own code here for the PID control*/
    while (1)
    {
        /* should receive set point value from Reading Thread */

        /* should compute the PID control */

        /* should send output value to Display Thread */

        tx_thread_sleep (1);
    }
}
