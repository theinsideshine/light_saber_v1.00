/**
 * File:   Clase para controlar el buzzer
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
 */
#ifndef LED_H
#define LED_H

#include "Arduino.h"

#define PIN_LED                      9       // Pin del buzzer.

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
