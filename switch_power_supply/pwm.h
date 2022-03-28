/* 
 * File:   pwm.h
 * Author: sh
 *
 * Created on December 13, 2021, 5:09 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void pwm_init( void);
void timer3_init( void);
void pwm_set( int pwm);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

