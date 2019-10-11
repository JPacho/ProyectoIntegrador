/* generated thread header file - do not edit */
#ifndef MAIN_THREAD_ADC_H_
#define MAIN_THREAD_ADC_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void main_thread_adc_entry(void);
#else
extern void main_thread_adc_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_gpt_input_capture.h"
#include "r_input_capture_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_pwm;
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const input_capture_instance_t g_input_capture;
#ifndef input_capture_callback
void input_capture_callback(input_capture_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t systemTimer;
#ifndef systemTimer_callback
void systemTimer_callback(timer_callback_args_t *p_args);
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;
#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif
extern TX_QUEUE g_main_queue_reading;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* MAIN_THREAD_ADC_H_ */
