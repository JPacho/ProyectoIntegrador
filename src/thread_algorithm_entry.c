#include "thread_algorithm.h"
#include <time.h>
#include <main_thread_adc.h>

/*
 * Data received from Thread Reading
 */
ULONG received_data[3] = {0, 0, 0};

const double Kp = 0.290;
const double Ki = 0;//0.121;
const double Kd = 0;//0.174;

double error = 0;
double last_error = 0;
double acumulated_error=0, rate_error = 0;
double speedMotor_U16=0, setPoint_U16 = 0;
double timer = 0;
double PWM_output = 0;
double dummy = 0;

ULONG dataToReading[3] = { 0, 0, 0 };


void computePID();

/* Algorithm Thread entry function */
void thread_algorithm_entry(void)
{
    Algorithm_Timer.p_api->open (Algorithm_Timer.p_ctrl, Algorithm_Timer.p_cfg);
    Algorithm_Timer.p_api->start (Algorithm_Timer.p_ctrl);

    while (1)
    {
        /* should compute the PID control*/

        computePID();

        /* should send output value to Display Thread */

        tx_thread_sleep (1);
    }


}

void computePID()
{
    /*Add logic for computing PID*/
    tx_queue_receive(&g_main_queue_algorithm, received_data, 20);

    speedMotor_U16 = (double)(received_data[0]);
    setPoint_U16 = received_data[1];


    /* Use Ziegler-Nichols method in order to get PID constants. */

    error = setPoint_U16 - speedMotor_U16;

    /*
     * La integral del error es el error acumulativo en el tiempo
     */

    acumulated_error += error;

    /*
     * La derivada del error es la tasa de cambio del error
     */

    rate_error = (error - last_error);

    PWM_output = (Kp * error) + (Ki * acumulated_error) + (Kd * rate_error);
    dummy = PWM_output;

    PWM_output *= -1;

    if (PWM_output > 100)
        PWM_output = 100;

    else if(PWM_output < 0)
        PWM_output = 0;

    last_error = error;

    dataToReading[0] = (ULONG)(PWM_output);
    tx_queue_send (&g_main_queue_reading, dataToReading, TX_NO_WAIT);
}

void algorithmTimer_callback(timer_callback_args_t *p_args)
{
    (void)p_args;
    timer++;
}
