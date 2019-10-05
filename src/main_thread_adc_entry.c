#include <main_thread_adc.h>
#include <main_thread.h>

#define MAX_COUNTS 0xFFFFFFFF + 1
uint16_t dutyCycle = 0;
uint16_t u16ADC_Data = 0;

uint32_t time = 0;
uint32_t RPM = 0;
uint32_t frecuencia = 0;

uint32_t timer = 0;

ULONG my_message[3] =
{ 0, 0, 0 };

/* thread_adc entry function */
void main_thread_adc_entry(void)
{
    /*
     * Open, start ADC
     */
    g_adc0.p_api->open (g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg (g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart (g_adc0.p_ctrl);

    /*
     * Open, start system Timer
     */
    systemTimer.p_api->open (systemTimer.p_ctrl, systemTimer.p_cfg);
    systemTimer.p_api->start (systemTimer.p_ctrl);

    /*
     * Open, start PWM Timer
     */
    g_timer_pwm.p_api->open (g_timer_pwm.p_ctrl, g_timer_pwm.p_cfg);
    g_timer_pwm.p_api->start (g_timer_pwm.p_ctrl);

    /*
     * Open, enable Input Capture
     */
    g_input_capture.p_api->open (g_input_capture.p_ctrl, g_input_capture.p_cfg);
    g_input_capture.p_api->enable (g_input_capture.p_ctrl);


    while (1)
    {
        g_adc0.p_api->read (g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);

        /* Set 0-100 range*/
        dutyCycle = (u16ADC_Data * 100) / 4095;

        g_timer_pwm.p_api->dutyCycleSet (g_timer_pwm.p_ctrl, dutyCycle, TIMER_PWM_UNIT_PERCENT, 1);

        /*Queue storage*/
        my_message[0] = dutyCycle;
        my_message[1] = RPM;

        /*Send message to Display thread.*/
        tx_queue_send (&g_main_queue_display, my_message, TX_NO_WAIT);
        tx_thread_sleep (10);
    }
}

void input_capture_callback(input_capture_callback_args_t *p_args)
{
    g_cgc.p_api->systemClockFreqGet(CGC_SYSTEM_CLOCKS_PCLKD, &frecuencia);
    time = ((p_args->overflows * MAX_COUNTS) + p_args->counter) * 1000 / frecuencia;
    RPM = (15 / time) * 1000;
}

void systemTimer_callback(timer_callback_args_t *p_args)
{
    (void)p_args;
    timer++;
}
