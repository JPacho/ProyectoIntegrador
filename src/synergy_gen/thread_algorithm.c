/* generated thread source file - do not edit */
#include "thread_algorithm.h"

TX_THREAD thread_algorithm;
void thread_algorithm_create(void);
static void thread_algorithm_func(ULONG thread_input);
static uint8_t thread_algorithm_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.thread_algorithm") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (2) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_Algorithm_Timer) && !defined(SSP_SUPPRESS_ISR_GPT2)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 2);
#endif
#endif
static gpt_instance_ctrl_t Algorithm_Timer_ctrl;
static const timer_on_gpt_cfg_t Algorithm_Timer_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t Algorithm_Timer_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 100, .unit = TIMER_UNIT_PERIOD_USEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 2, .autostart = true, .p_callback = algorithmTimer_callback, .p_context = &Algorithm_Timer, .p_extend =
          &Algorithm_Timer_extend,
  .irq_ipl = (2), };
/* Instance structure to use this module. */
const timer_instance_t Algorithm_Timer =
{ .p_ctrl = &Algorithm_Timer_ctrl, .p_cfg = &Algorithm_Timer_cfg, .p_api = &g_timer_on_gpt };
TX_QUEUE g_main_queue_algorithm;
static uint8_t queue_memory_g_main_queue_algorithm[16];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void thread_algorithm_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_g_main_queue_algorithm;
    err_g_main_queue_algorithm = tx_queue_create (&g_main_queue_algorithm, (CHAR *) "Main Queue Algorithm", 4,
                                                  &queue_memory_g_main_queue_algorithm,
                                                  sizeof(queue_memory_g_main_queue_algorithm));
    if (TX_SUCCESS != err_g_main_queue_algorithm)
    {
        tx_startup_err_callback (&g_main_queue_algorithm, 0);
    }

    UINT err;
    err = tx_thread_create (&thread_algorithm, (CHAR *) "Algorithm Thread", thread_algorithm_func, (ULONG) NULL,
                            &thread_algorithm_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&thread_algorithm, 0);
    }
}

static void thread_algorithm_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    thread_algorithm_entry ();
}
