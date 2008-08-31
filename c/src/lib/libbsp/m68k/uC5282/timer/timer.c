/*
 *  Timer Init
 *
 *  Use the last DMA timer (DTIM3) as the diagnostic timer.
 *
 *  Author: W. Eric Norum <norume@aps.anl.gov>
 *
 *  COPYRIGHT (c) 2005.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#include <rtems.h>
#include <bsp.h>

void
benchmark_timerinitialize(void)
{
    int preScaleDivisor = bsp_get_CPU_clock_speed() / 1000000;
    int div = MCF5282_TIMER_DTMR_CLK_DIV1;

    if (preScaleDivisor > 256) {
        preScaleDivisor /= 16;
        div = MCF5282_TIMER_DTMR_CLK_DIV16;
    }
    MCF5282_TIMER3_DTMR = 0;
    MCF5282_TIMER3_DTMR = MCF5282_TIMER_DTMR_PS(preScaleDivisor - 1) | div |
                          MCF5282_TIMER_DTMR_RST;
}

/*
 * Return timer value in microsecond units
 */
int
benchmark_timerread(void)
{
    return MCF5282_TIMER3_DTCN;
}

/*
 *  Empty function call used in loops to measure basic cost of looping
 *  in Timing Test Suite.
 */
rtems_status_code
benchmark_timerempty_function(void)
{
    return RTEMS_SUCCESSFUL;
}

void
benchmark_timerdisable_subtracting_average_overhead(rtems_boolean find_flag)
{
}
