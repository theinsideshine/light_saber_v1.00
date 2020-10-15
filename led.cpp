/**
 * File:   Class that controls  led.
 /**
 * File:   Clase que controla el boton de configuracion y operacion
 *         del cartel.
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
 
#include "led.h"

CLed::CLed()
{

}

void CLed::init( void )
{
    pinMode( PIN_LED, OUTPUT );
    off();
}

/*
 * The led turns on with a HIGH
 */
 
void CLed::on()
{
    digitalWrite( PIN_LED,HIGH  );
}

void CLed::off()
{
    digitalWrite( PIN_LED, LOW );
}

// The buzzer changes state.
// Returns the previous state.

bool CLed::tgl()
{
bool state = (digitalRead( PIN_LED ) == LOW);

    if (state){
        on();
    }else{
        off();
    }

    return !state;
}
