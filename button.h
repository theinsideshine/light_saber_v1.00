/**
 * File:   Clase que controla el boton de configuracion y operacion
 *         del cartel.
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
 
#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "timer.h"

#define PIN_BUTTON                  7       // Pin del pulsador de configuracion.

class CButton
{
  public:
    CButton();
    void init( void );
    bool is_pressed( void );
    void debounce( void );

  private:
      CTimer Timer;
      bool state;                   // TRUE presionado.
};

#endif // BUTTON_H
