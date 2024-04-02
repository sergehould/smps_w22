/* 
 * File: Tick_core.c
 * Description: 
 *      Tick library implemented using the 32-bit core timer.
 *      The core timer increments once for every two ticks of SYSCLK
 *      For a SYSCLK of 80 MHz, the timer increments every 25 ns. 
 *      Because the timer is 32 bits, it rolls over every 
 *      232 × 25 ns = 107 s.
 * 
 * Author   Date            Comments
 * SH       28 Jan 2021     v1.0
 * SH       3 Feb 2021      v1.1    Add void delay_ticks(unsigned int tics) 
 * SH       25 March 2021   v2.0    Add function TickDiff() 
 * SH       25 March 2021   v2.1    TickGet() returns 2*ticks 
 *                                  delay_ticks() is in sysclk cycles
 * SH		29 Sept. 2021	v2.3	Disable blocking delay_us()
 *									Replaced by a blocking delay that does not use the core timer.	
 *									See util.c
 * SH		28 March 2024	v2.4	Revamp tick_diff()
 *
 *	Warning: Cannot use a blocking delay method along with a clock polling method
 *				because the blocking delay resets the core clock.
 **/
#include <xc.h>
#include <stdint.h>
#include "Tick_core.h"


/* Blocking delay function using tick_core */
 void delay_us(unsigned int us)
 {
     // Convert microseconds us into how many clock ticks it will take
     us *= SYS_FREQ / 1000000 / 2; // Core Timer updates every 2 ticks

     _CP0_SET_COUNT(0); // Set Core Timer count to 0

     while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
 }


/* Blocking delay function 
 * Block for the amount of cycles specified 
 */
void delay_ticks(unsigned int tics)
{
    // Convert microseconds us into how many clock ticks it will take
    tics = tics/2; // Core Timer updates every 2 ticks

    _CP0_SET_COUNT(0); // Set Core Timer count to 0

    while (tics > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
}

/* Gets the core clock timer current tick value */
uint32_t tick_get(void){
    return _CP0_GET_COUNT()*2;
}

uint16_t tick_get2(void){
    return _CP0_GET_COUNT()*2;
}


/* Reset the core clock timer to 0 */
void TickCoreReset(void){
        _CP0_SET_COUNT(0); // Set Core Timer count to 0
}

/* Returns the difference between the current core timer ticks and the latest stamp value   */
/* Stressed tested OK with  a 107 second delay whether stamp is int32_t or uint32_t                   */
/* Does not skip count when the core clock overflows                                         */
uint32_t tick_diff(uint32_t stamp){
    uint32_t diff;
    diff= tick_get()-stamp; // will always calculate correctly even if tick_get < stamp because uint32_t will remove the negative sign
    return (uint32_t)diff;
}

//uint32_t tick_diff3(uint32_t stamp){
//    uint32_t diff;
//    if(TickGet()>=stamp){ 
//        diff= (int64_t)TickGet()-stamp;
//    }
//    else{
//        diff= (int64_t)0x100000000 + (int64_t)TickGet()-(int64_t)stamp;
//    }
//    return (uint32_t)diff;
//}


//uint16_t tick_diff2(uint16_t stamp){
//    uint16_t diff, tick;
//    tick = tick_get2();
//   // if(tick >=stamp){ 
//        diff= tick-stamp;
//   // }
//   // else{
//   //     diff= (int32_t)0x10000 + (int32_t)TickGet()-(int32_t)stamp;
//   // }
//    return (uint16_t)diff;
//}

