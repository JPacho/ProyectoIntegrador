#include <main_thread_adc.h>
   /* thread_adc entry function */
    uint16_t u16ADC_Data2 =50;
/* thread_adc entry function */
void main_thread_adc_entry(void)
{
    /* thread_adc entry function */
   // uint16_t u16ADC_Data2 =50;

    /* TODO: add your own code here */
    /* TODO: add your own code here */
    g_adc0.p_api->open (g_adc0.p_ctrl, g_adc0.p_cfg);

    g_adc0.p_api->scanCfg (g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart (g_adc0.p_ctrl);

    while (1)
    {
        g_adc0.p_api->read (g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data2);
        tx_thread_sleep (1);
    }
}

