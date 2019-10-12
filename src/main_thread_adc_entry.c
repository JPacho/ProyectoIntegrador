#include <main_thread_adc.h>
#include <thread_display.h>
#include <thread_algorithm.h>

const uint32_t MAX_COUNTS = 0xFFFFFFFF + 1;
const uint32_t frequency  = 120000000;

ULONG my_rcv_msg2[3] = {0,0,0};
//uint32_t dutyCycle = 0;
uint32_t u16ADC_Data = 0;

double elapsed_time = 0;
double RPM = 0;
uint32_t setPoint = 3750;

/*
uint16_t PulsesPerRevolution = 0;
 *
 */
ULONG dataToDisplay[3] = { 0, 0, 0 };

ULONG dataToAlgorithm[3] = {0, 0, 0 };

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
        tx_queue_receive(&g_main_queue_reading,my_rcv_msg2, 20);

        g_adc0.p_api->read (g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);

        /* Set 0-100 range*/
        //dutyCycle = ((u16ADC_Data * 100) / 4095);

        setPoint=(u16ADC_Data*3750)/4095;

        g_timer_pwm.p_api->dutyCycleSet (g_timer_pwm.p_ctrl, my_rcv_msg2[0], TIMER_PWM_UNIT_PERCENT, 1);

        /*Queue storage for display thread*/

        dataToDisplay[0] = my_rcv_msg2[0];
        dataToDisplay[1] = RPM;
        dataToDisplay[2] = setPoint;

        dataToAlgorithm[0] = RPM; //se deberia llamar speedMotor o algo asi
        dataToAlgorithm[1] = setPoint;


        /*Send message to Display thread.*/
        tx_queue_send (&g_main_queue_display, dataToDisplay, TX_NO_WAIT);

        /* Send message to Algorithm Thread */
        tx_queue_send (&g_main_queue_algorithm, dataToAlgorithm, TX_NO_WAIT);


        RPM=0;

        tx_thread_sleep (10);
    }
}

void input_capture_callback(input_capture_callback_args_t *p_args)
{
    elapsed_time = ((p_args->overflows * MAX_COUNTS) + p_args->counter) * 1000 / frequency;
    RPM = (15 / elapsed_time) * 1000;
}

void systemTimer_callback(timer_callback_args_t *p_args)
{
    (void)p_args;
}
