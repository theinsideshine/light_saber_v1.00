/**
 * File:   Clase para controlar el buzzer.
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
 * El led prende con un HIGH
 */
 
void CLed::on()
{
    digitalWrite( PIN_LED,HIGH  );
}

void CLed::off()
{
    digitalWrite( PIN_LED, LOW );
}

// Cambia de estado el buzzer.
// Retorna el estado anterior.
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
