#include <thread_display.h>
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"


ULONG f64my_rcv_msg[3] = {0,0,0};

static void update_display(GX_WIDGET *p_widget);



UINT window1_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type)
    {

        case GX_EVENT_SHOW:
            gx_system_timer_start(widget, 101, 10, 10);
            break;
        case GX_EVENT_TIMER:
            update_display(widget->gx_widget_parent);
            break;
        default:
            gx_window_event_process(widget, event_ptr);
            break;
    }

    return result;
}


static void update_display(GX_WIDGET *p_widget)
{
    /*Receive message*/

    tx_queue_receive(&g_main_queue_display,f64my_rcv_msg, 20);
    ssp_err_t err = 0;
    static GX_CHAR txtDuty[4];
    static GX_CHAR txtSpeed[5];
    static GX_CHAR txtSetpoint[5];
    GX_PROMPT *p_prompt = NULL;
    GX_PROGRESS_BAR *p_progress_bar = NULL;
    GX_RADIAL_PROGRESS_BAR *p_progres = NULL;

    /*
     * Functionality for displaying the duty value.
     */
    err = gx_widget_find(p_widget, ID_LBL_DUTY_VALUE, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET **)&p_prompt);
    if(TX_SUCCESS == err)
    {
      gx_utility_ltoa((LONG)  f64my_rcv_msg[0], txtDuty, 4);
        err = gx_prompt_text_set(p_prompt, txtDuty);
        if (err)
            while (1);
    }

    /*
     * Functionality for displaying the setpoint value.
     */
    err = gx_widget_find(p_widget, ID_LBL_SETPOINT_VALUE, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET **)&p_prompt);
    if(TX_SUCCESS == err)
    {
        gx_utility_ltoa((LONG) f64my_rcv_msg[2], txtSetpoint, 5);
        err = gx_prompt_text_set(p_prompt, txtSetpoint);
        if (err)
            while (1);
    }

    /*
     * Functionality for displaying the speed motor value
     */

    err = gx_widget_find(p_widget, ID_LBL_SPEED_VALUE, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET **)&p_prompt);
    if(TX_SUCCESS == err)
    {
        gx_utility_ltoa((LONG) f64my_rcv_msg[1], txtSpeed, 5);
        err = gx_prompt_text_set(p_prompt, txtSpeed);
        if (err)
            while (1);
    }

    /*
     * Functionality for displaying the duty value to progress bar
     */
    err = gx_widget_find(p_widget, ID_PROGRESS_BAR_DUTY_CYCLE, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET ** )&p_progress_bar);
    if (TX_SUCCESS == err)
    {
        err = gx_progress_bar_value_set (p_progress_bar, (INT)f64my_rcv_msg[0]);
        if (err)
            while (1);
    }

    /*
     * Functionality for displaying the speed motor value to progress bar
     */

    err = gx_widget_find(p_widget, ID_RADIAL_PROGRESS_BAR_SPEED, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET ** )&p_progres);
    if (TX_SUCCESS == err)
    {
        err = gx_radial_progress_bar_value_set (p_progres, (INT)-((f64my_rcv_msg[1])*300)/3000);
        if (err)
            while (1);
    }

    /*
       * Functionality for displaying the setpoint value to progress bar.
       */
      err = gx_widget_find(p_widget, ID_RADIAL_PROGRESS_BAR_SET_POINT, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET **)&p_progres);
      if(TX_SUCCESS == err)
      {
          err = gx_radial_progress_bar_value_set (p_progres, -(((INT)f64my_rcv_msg[1])*300)/3000);
          if (err)
              while (1);
      }
}

