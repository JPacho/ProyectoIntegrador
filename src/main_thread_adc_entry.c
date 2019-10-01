#include <main_thread_adc.h>
#include <main_thread.h>
/*
 * variables
 */
uint32_t dutyCycle2 = 50;
uint32_t u16ADC_Data2 = 50;
/*
 Almacena el numero de pulsos por revoulción
 */
uint16_t PulsesPerRevolution = 0;

/*
 Almacena el valor incrementado por el timer cada 100 microsegundos.
 */
uint32_t timer = 0;

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

    systemTimer.p_api->open (systemTimer.p_ctrl, systemTimer.p_cfg);
    systemTimer.p_api->start (systemTimer.p_ctrl);

    g_timer_pwm.p_api->open (g_timer_pwm.p_ctrl, g_timer_pwm.p_cfg);
    g_timer_pwm.p_api->start (g_timer_pwm.p_ctrl);

    g_input_capture.p_api->open (g_input_capture.p_ctrl, g_input_capture.p_cfg);
    g_input_capture.p_api->enable (g_input_capture.p_ctrl);

    while (1)
    {

        g_adc0.p_api->read (g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data2);

        /*
         * establecer rango 0-100
         */

        dutyCycle2 = ((u16ADC_Data2 * 100) / 4095);

        g_timer_pwm.p_api->dutyCycleSet (g_timer_pwm.p_ctrl, dutyCycle2, TIMER_PWM_UNIT_PERCENT, 1);

        /*almacenamiento*/

        for (uint32_t i = 0; i > 99; i++)
        {
            i = i ^ dutyCycle2;
            dutyCycle2 = i ^ dutyCycle2;
            i = i ^ dutyCycle2;
        }
        my_message[0] = dutyCycle2;
        /*enviar msj a thread 1*/
        tx_queue_send (&g_main_queue_display, my_message, TX_NO_WAIT);
        tx_thread_sleep (10);
    }
}

void input_capture_callback(input_capture_callback_args_t *p_args)
{
    PulsesPerRevolution++;
}

void systemTimer_callback(timer_callback_args_t *p_args)
{
    timer++;
}
