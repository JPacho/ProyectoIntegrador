/* generated thread header file - do not edit */
#ifndef THREAD_ALGORITHM_H_
#define THREAD_ALGORITHM_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void thread_algorithm_entry(void);
#else
extern void thread_algorithm_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t Algorithm_Timer;
#ifndef algorithmTimer_callback
void algorithmTimer_callback(timer_callback_args_t *p_args);
#endif
extern TX_QUEUE g_main_queue_algorithm;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* THREAD_ALGORITHM_H_ */
