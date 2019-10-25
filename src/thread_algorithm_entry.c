#include "thread_algorithm.h"
#include <time.h>
#include <main_thread_adc.h>

const double Kp = 0.290;
const double Ki = 0;//0.121;
const double Kd = 0;//0.174;

/*
 * Data received from Thread Reading
 */
ULONG f64Received_data[3] = {0, 0, 0};
ULONG f64DataToReading[3] = { 0, 0, 0 };

double f64Error = 0;
double f64Last_error = 0;
double f64Acumulated_error=0, f64Rate_error = 0;
double f64SpeedMotor=0, f64SetPoint = 0;
double f64timer = 0;
double f64PWM_output = 0;




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
    tx_queue_receive(&g_main_queue_algorithm, f64Received_data, 20);

    f64SpeedMotor = (double)(f64Received_data[0]);
    f64SetPoint = f64Received_data[1];


    /* Use Ziegler-Nichols method in order to get PID constants. */

    f64Error = f64SetPoint - f64SpeedMotor;

    /*
     * La integral del error es el error acumulativo en el tiempo
     */

    f64Acumulated_error += f64Error;

    /*
     * La derivada del error es la tasa de cambio del error
     */

    f64Rate_error = (f64Error - f64Last_error);

    f64PWM_output = (Kp * f64Error) + (Ki * f64Acumulated_error) + (Kd * f64Rate_error);


    f64PWM_output *= -1;

    if (f64PWM_output > 100)
        f64PWM_output = 100;

    else if(f64PWM_output < 0)
        f64PWM_output = 0;

    f64Last_error = f64Error;

    f64DataToReading[0] = (ULONG)(f64PWM_output);
    tx_queue_send (&g_main_queue_reading, f64DataToReading, TX_NO_WAIT);
}

void algorithmTimer_callback(timer_callback_args_t *p_args)
{
    (void)p_args;
    f64timer++;
}
