#include <main_thread_adc.h>
#include <thread_display.h>
#include <thread_algorithm.h>

const uint32_t MAX_COUNTS = 0xFFFFFFFF + 1;
const uint32_t frequency  = 120000000;

ULONG ulongMy_rcv_msg2[3] = {0,0,0};
uint32_t u32DutyCycle = 0;
uint16_t u16ADC_Data = 0;

double f64Elapsed_time = 0;
double f64Speed = 0;
uint16_t u16SetPoint = 0;

ULONG f64DataToDisplay[3] = { 0, 0, 0 };
ULONG f64DataToAlgorithm[3] = {0, 0, 0 };

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
        tx_queue_receive(&g_main_queue_reading,ulongMy_rcv_msg2, 20);

        g_adc0.p_api->read (g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);

        /* Set 0-100 range */
        //u32DutyCycle = ((u16ADC_Data * 100) / 4095);

        u16SetPoint = (uint16_t)((u16ADC_Data * 3750) / 4095);

        u32DutyCycle = (uint32_t)(ulongMy_rcv_msg2[0]);
        g_timer_pwm.p_api->dutyCycleSet (g_timer_pwm.p_ctrl, u32DutyCycle, TIMER_PWM_UNIT_PERCENT, 1);

        /* Queue storage for display thread */

        f64DataToDisplay[0] = u32DutyCycle;
        f64DataToDisplay[1] = (ULONG)(f64Speed);
        f64DataToDisplay[2] = u16SetPoint;

        /* Queue storage for algorithm thread */
        f64DataToAlgorithm[0] = (ULONG)(f64Speed);
        f64DataToAlgorithm[1] = u16SetPoint;

        /*Send message to Display thread.*/
        tx_queue_send (&g_main_queue_display, f64DataToDisplay, TX_NO_WAIT);

        /* Send message to Algorithm Thread */
        tx_queue_send (&g_main_queue_algorithm, f64DataToAlgorithm, TX_NO_WAIT);

        f64Speed = 0;

        tx_thread_sleep (1);
    }
}

void input_capture_callback(input_capture_callback_args_t *p_args)
{
    f64Elapsed_time = ((p_args->overflows * MAX_COUNTS) + p_args->counter) * 1000 / frequency;
    f64Speed = (15 / f64Elapsed_time) * 1000;
}

void systemTimer_callback(timer_callback_args_t *p_args)
{
    (void)p_args;
}
