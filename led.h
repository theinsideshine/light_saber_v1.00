/**
 * File:   Class that controls  led.
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
 */
#ifndef LED_H
#define LED_H

#include "Arduino.h"

#define PIN_LED                      9       // Led pin.

class CLed
{
  public:
    CLed();
    void init( void );
    void on();
    void off();
    bool tgl();

  private:
};

#endif // LED_H
