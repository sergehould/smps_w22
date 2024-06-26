/* 
 * File:   Tick_core.h
 * Author: sh
 *
 * Created on January 28, 2021
 * Author   Date            Comments
 * SH       28 Jan 2021     v1.0
 * SH       3 Feb 2021      v1.1    Add void delay_ticks(unsigned int tics)  
 * SH       25 March 2021   v2.0    Add function TickDiff() and macro TickDiff2
 * SH       27 April 2021   v2.1    TICKS_PER_SECOND  does not divide SYS_FREQ by two any more.
 * SH       20 May 2021   	v2.2    Add C++ pre-compiler commands: not tested
 * SH       8 Nov. 2022     v2.3    Add tick_diff and tick_get macros. Add TEN_MS
 *                                  and HUNDRED_MS
 */

#ifndef TICK_CORE_H
#define	TICK_CORE_H
//#include "initBoard.h"
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define     TickDiff    tick_diff
#define     TickGet     tick_get

#define     SYS_FREQ            40000000 // Running at 40MHz
//#define     TICKS_PER_SECOND    (SYS_FREQ >> 1)   // The core timer increments once for every two ticks of SYSCLK
#define     TICKS_PER_SECOND    SYS_FREQ   // The core timer increments once for every two ticks of SYSCLK but the APIs set and get in sysclk ticks.
#define     HUNDRED_MS          SYS_FREQ/10   
#define     TEN_MS              SYS_FREQ/100   
/* Macro for some reason does not work with signed int32_t stamp type */
/* but works with a function: see TickDiff(()*/
//#define TickDiff2(a)     (TickGet()>=(int64_t)a ? TickGet()-(int64_t)a: 0x100000000 + TickGet()-(int64_t)a)
//void delay_us(unsigned int us);
uint32_t tick_get(void);
uint16_t tick_get2(void);
void delay_ticks(unsigned int tics);
void TickCoreReset(void);
uint32_t tick_diff(uint32_t stamp);
uint16_t tick_diff2(uint16_t stamp);
void delay_10us( unsigned int );
void delay_us(unsigned int us);



#ifdef	__cplusplus
}
#endif

#endif	/* TICK_CORE_H */



