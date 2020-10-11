/**
 * File:   Clase de timers por software basados en la funcion millis()
 *         de arduino que al estar basada en un timer de la cpu por irq,
           no bloquea la ejecucion. 
 *
 * - Compiler:           Arduino 1.8.13
 * - Supported devices:  mini
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
 
#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

class CTimer
{
  public:
    CTimer();
    void start();
    bool expired(uint32_t);

  private:
      uint32_t timer;
};

#endif // TIMER_H
