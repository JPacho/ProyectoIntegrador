/* generated thread header file - do not edit */
#ifndef MAIN_THREAD_PWM_H_
#define MAIN_THREAD_PWM_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void main_thread_pwm_entry(void);
#else
extern void main_thread_pwm_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1;
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer0;
#ifndef g_timer0_interrupt
void g_timer0_interrupt(timer_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* MAIN_THREAD_PWM_H_ */