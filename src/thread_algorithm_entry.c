#include "thread_algorithm.h"


const double Kp = 2;    /*0.290*/
const double Ki = 5;    /*0.121*/
const double Kd = 1;    /*0.174*/

uint16_t error, last_error = 0;
uint16_t acumulated_error, rate_error = 0;

double PWM_output = 0;

void computePID();

/* Algorithm Thread entry function */
void thread_algorithm_entry(void)
{

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
    /*Add logic for computing PID*/

    /* Usar metodo Ziegler-Nichols para obtener ganacias del PID de forma empirica. */

    /* Se necesita saber el tiempo transcurrido*/

    /* error = setPoint - input */

    /*
     * La integral del error es el error acumulativo en el tiempo
     */

    /* acumulated_error += error * tiempo transcurrido */

    /*
     * La derivada del error es la tasa de cambio del error
     */

    /* rate_error = (error - last_error) / tiempo transcurrido*/

    PWM_output = (Kp * error) + (Ki * acumulated_error) + (Kd * rate_error);


}
