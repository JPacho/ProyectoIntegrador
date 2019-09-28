#include <main_thread_adc.h>
#include <main_thread.h>
#include "main_thread_pwm.h"
/*
 * variables
 */
uint16_t dutyCycle2 = 50;
uint16_t u16ADC_Data2 = 50;
uint16_t contPulsos = 0;
int RPM = 0;
ULONG my_message[3] =
{ 0, 0, 0 };
/* thread_adc entry function */
void main_thread_adc_entry(void)
{
    /* TODO: add your own code here */

    /*
     * abrir, configurar ADC
     */
    g_adc0.p_api->open (g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg (g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart (g_adc0.p_ctrl);

    /*
     * abrir, correr timer1
     */
    g_timer1.p_api->open (g_timer1.p_ctrl, g_timer1.p_cfg);
    g_timer1.p_api->start (g_timer1.p_ctrl);

    g_external_irq0.p_api->open(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);

    while (1)
    {
        //g_ioport.p_api->pinRead (IOPORT_PORT_00_PIN_07, &sw4);


        g_adc0.p_api->read (g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data2);

        g_timer1.p_api->dutyCycleSet (g_timer1.p_ctrl, dutyCycle2, TIMER_PWM_UNIT_PERCENT, 1);

        /*
         * establecer rango 0-100
         */
        //dutyCycle = (dutyCycle * 100) / 255;
        /*almacenamiento*/
        my_message[0] = dutyCycle2;
        /*enviar msj a thread 1*/
        tx_queue_send (&g_main_queue_display, my_message, TX_NO_WAIT);
        tx_thread_sleep (10);
    }
}

void pulseInterruption(external_irq_callback_args_t *p_args)
{
    contPulsos++;
}

