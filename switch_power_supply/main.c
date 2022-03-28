/* 
 * Description:
 * 
 * Author       Date                Description
 *              
 * 
 */

#include "util.h"
#include <stdio.h>
#include <xc.h>
#include "initBoard.h"
#include "initBoard.h"
#include "Tick_core.h"
#include "adc.h"
#include <sys/attribs.h>
#include "pwm.h"
#include "config.h"


int main(void) {
    //io_init();
    //pwm_init();
    //adc_init();
    //init_heartbeat();

    while(1){
        heartbeat();
    }
    return 0;
}



