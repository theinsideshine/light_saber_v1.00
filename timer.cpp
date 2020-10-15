/**
 * File:  Class of software timers based on the millis () function.
 *
 * - Compiler:           Arduino 1.8.13
 * - Supported devices:  Arduino pro or pro mini
 *
 * \author               PT: educacion.ta@gmail.com
 *                       JS: juanschiavoni@gmail.com 
 *                       
* Date:  09-09-2020
 *
 *      The inside shine.
 *
 *
  */
  
#include "timer.h"

CTimer::CTimer()
{
    start();
}

void CTimer::start( void )
{
    timer = millis();
}

bool CTimer::expired( uint32_t ms )
{
    return ((millis() - timer) > ms);
}
