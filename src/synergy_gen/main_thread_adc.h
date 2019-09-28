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
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq0;
#ifndef pulseInterruption
void pulseInterruption(external_irq_callback_args_t *p_args);
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;
#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* MAIN_THREAD_ADC_H_ */
