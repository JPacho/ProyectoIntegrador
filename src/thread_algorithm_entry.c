#include "thread_algorithm.h"
#include <time.h>
#include <main_thread_adc.h>

/*
 * Data received from Thread Reading
 */
ULONG received_data[3] = {0, 0, 0};

const double Kp = 2;    /*0.290*/
const double Ki = 5;    /*0.121*/
const double Kd = 1;    /*0.174*/

double error = 0;
double last_error = 0;
double acumulated_error=0, rate_error = 0;
double speedMotor_U16=0, setPoint_U16 = 0;
double elapsed_time_U32 = 0;
double  previous_time = 0;
double timer = 0;
double PWM_output, current_time = 0;

ULONG dataToReading[3] = { 0, 0, 0 };


void computePID();

/* Algorithm Thread entry function */
void thread_algorithm_entry(void)
{



    Algorithm_Timer.p_api->open (Algorithm_Timer.p_ctrl, Algorithm_Timer.p_cfg);
    Algorithm_Timer.p_api->start (Algorithm_Timer.p_ctrl);

    /* TODO: add your own code here for the PID control*/
    while (1)
    {
        /* should receive set point value from Reading Thread */

        /* should compute the PID control*/

        computePID();

        /* should send output value to Display Thread */

        tx_thread_sleep (1);
    }


}

void computePID()
{
    clock_t t ;
    t=clock();
    //t=clock()-t;
    //current_time=t/CLOCKS_PER_SEC;
    current_time = (((double)t)/CLOCKS_PER_SEC) * 1000;

    /*Add logic for computing PID*/
    tx_queue_receive(&g_main_queue_algorithm, received_data, 20);

    speedMotor_U16 = received_data[0];
    setPoint_U16 = received_data[1];

   // setPoint_U16 = 3750;

    //current_time = timer;

    if (previous_time > current_time)
    {
        elapsed_time_U32 = (previous_time - current_time);
    }
    else
    {
        elapsed_time_U32 = current_time - previous_time;
    }


   // elapsed_time_U32 = current_time - previous_time;
    /* Usar metodo Ziegler-Nichols para obtener ganacias del PID de forma empirica. */

    /* Se necesita saber el tiempo transcurrido*/

    error = setPoint_U16 - speedMotor_U16;

    /*
     * La integral del error es el error acumulativo en el tiempo
     */

    acumulated_error += error *  current_time;

    /*
     * La derivada del error es la tasa de cambio del error
     */

    rate_error = ((error - last_error) / current_time);

    PWM_output = (Kp * error) + (Ki * acumulated_error) + (Kd * rate_error);

    last_error = error;
    previous_time = current_time;

    dataToReading[0] = PWM_output;
    tx_queue_send (&g_main_queue_reading, dataToReading, TX_NO_WAIT);
}

void algorithmTimer_callback(timer_callback_args_t *p_args)
{
    (void)p_args;
    timer++;
}
