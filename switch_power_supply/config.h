/* 
 * File:   public.h
 * Author: sh
 *
 * Created on December 14, 2021, 11:54 AM
 */

#ifndef PUBLIC_H
#define	PUBLIC_H

#define DEBUG
#ifdef	__cplusplus
extern "C" {
#endif

#if defined  MX3
    #define LED  LATAbits.LATA7
#elif defined MICROSTICK_II
    #define LED  LATAbits.LATA0
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* PUBLIC_H */

