/*  timer.c
 *
 *  This file implements a benchmark timer using timer 2.
 *
 *  COPYRIGHT (c) 1989-1998.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  Ported to LEON implementation of the SPARC by On-Line Applications
 *  Research Corporation (OAR) under contract to the European Space 
 *  Agency (ESA).
 *
 *  LEON modifications of respective RTEMS file: COPYRIGHT (c) 1995. 
 *  European Space Agency.
 *
 *  $Id$
 */


#include <bsp.h>

#if defined(RTEMS_MULTIPROCESSING)
  #define LEON3_TIMER_INDEX \
      ((rtems_configuration_get_user_multiprocessing_table()) ? \
        (rtems_configuration_get_user_multiprocessing_table()->node) - 1 : 1)
#else 
  #define LEON3_TIMER_INDEX 0
#endif

rtems_boolean benchmark_timerfind_average_overhead;

rtems_boolean benchmark_timeris_initialized = FALSE;

extern volatile LEON3_Timer_Regs_Map *LEON3_Timer_Regs;

void benchmark_timerinitialize(void)
{
  /*
   *  Timer runs long and accurate enough not to require an interrupt.
   */
  if (LEON3_Timer_Regs) {
    if ( benchmark_timeris_initialized == FALSE ) {
      /* approximately 1 us per countdown */
      LEON3_Timer_Regs->timer[LEON3_TIMER_INDEX].reload = 0xffffff;
      LEON3_Timer_Regs->timer[LEON3_TIMER_INDEX].value = 0xffffff;
    } else {
      benchmark_timeris_initialized = TRUE;
    }
    LEON3_Timer_Regs->timer[LEON3_TIMER_INDEX].conf = LEON3_GPTIMER_EN | LEON3_GPTIMER_LD;
  }
}

#define AVG_OVERHEAD      3  /* It typically takes 3.0 microseconds */
                             /*     to start/stop the timer. */
#define LEAST_VALID       2  /* Don't trust a value lower than this */

int benchmark_timerread(void)
{
  uint32_t total;

  if (LEON3_Timer_Regs) {
    total = LEON3_Timer_Regs->timer[LEON3_TIMER_INDEX].value;
    
    total = 0xffffff - total;
    
    if ( benchmark_timerfind_average_overhead == 1 )
      return total;          /* in one microsecond units */
    
    if ( total < LEAST_VALID )
      return 0;            /* below timer resolution */

    return total - AVG_OVERHEAD;
  }
  return 0;
}

rtems_status_code benchmark_timerempty_function( void )
{
  return RTEMS_SUCCESSFUL;
}

void benchmark_timerdisable_subtracting_average_overhead(
  rtems_boolean find_flag
)
{
  benchmark_timerfind_average_overhead = find_flag;
}
