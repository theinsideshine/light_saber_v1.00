/**
 * File:  Espada laser electronica simple 
 *        Un sensor acelerometro lee el movimiento de la espada y
 *        reproduce sonidos y contrale un led dependiendo del movimiento 
 *        La espada se prende y se apaga con un pulsador. 
 *        Tiene cinco  estados 
 *        Espada encendiendose 
 *        Espada quieta, 
 *        Espada moviendose, 
 *        Espada golpeada. 
 *        Espada apagandose 
 *        
 *        
 *        
 * 
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

#include "led.h"
#include "timer.h"
#include "button.h"

#include <PCM.h>   // El audio sale por el pin 11 
#include "sound.h"
#include "mpu6050.h"


#define ST_INIT                    0       // Inicializa el programa (carga la configuracion).
#define ST_WAIT_ON                 1       // Espera que se prende el sable
#define ST_ON                      2       // Prende la espada
#define ST_IDLE                    3       // Espada encendida
#define ST_KNOCK                   4       // La espada se golpeo 
#define ST_MOVE                    5       // La espada se movio  
#define ST_OFF                     6       // Apaga la espada



#define N_TILT_SABER                    8       // Veces que se prende y apaga el led    
#define T_TILT_SABER                    100     // Tiempo en milisegundo de togle del led
#define N_MOVE_SOUND2                   2       // Cada N veces se reproduce el sonido 2 de movimiento  

#define T_SOUND_IDLE                    1000    // Tiempo de repeticion del sonido idle
#define T_SOUND_KNOCK                   500    // Tiempo del sonido golpe
#define T_SOUND_MOVE                     800    // Tiempo del sonido giro

CButton Button;
CLed Led;
CMpu6050 Mpu6050;


/*
 *  Inicializa los perfericos de la espada .
 */
 
void setup()
{
    
    Led.init();
    Button.init();
    Mpu6050.init();
    
    Led.tgl() ;         // Señal de reset para el debug
    delay(500); 
    Led.tgl() ;

 }



/*
 * Loop de control de la espada laser
 */
 
void loop()
{
static CTimer   Timer;
static CTimer   Timer_led;
static CTimer   Timer_idle;
static CTimer   Timer_knock;
static CTimer   Timer_move;

static uint8_t  st_loop = ST_INIT;
static uint8_t  count_tilt = N_TILT_SABER ;
static uint8_t  count_move = N_MOVE_SOUND2;


   
    Button.debounce();

   
    switch( st_loop ) {
        
               
        case ST_INIT:
            
            st_loop = ST_WAIT_ON;
                        
        break;

        case ST_WAIT_ON:
        
        // Al presionar el boton se prende el sable
        // realiza un parpadeo del led
        
        if ( Button.is_pressed() ) {
          
             // En este estado, al requerirse el led titilar
             // se prende un timer que en ST_LOOP_ON se va a patear  T_TILT_SABER veces 
             
              st_loop = ST_ON;
             startPlayback(snd_out_saber, sizeof(snd_out_saber)); //Sonido de sable saliendo.
              Timer_led.start();
            }
                  
        break;


        case ST_ON:
        
        // Toglea el led N_TILT_SABER veces y pasa al estado idle
        
        if( Timer_led.expired( T_TILT_SABER ) ) {
                  
                   Led.tgl() ;
                   count_tilt--;
                   Timer_led.start();
              }

        // Al expirar el contador de veces de TILT pasa a IDLE
         
        if ( !count_tilt )  {

           Led.on();           // Prende la luz de la espada.
           Timer_idle.start();
           startPlayback(snd_idle_saber, sizeof(snd_idle_saber)); // Sonido de sable idle
           st_loop = ST_IDLE;
           
        }
                   
        break;

        case ST_IDLE:
        
        // Cada vez que expira el timer repite el sonido.
        
        if( Timer_idle.expired( T_SOUND_IDLE ) ) {
           startPlayback(snd_idle_saber, sizeof(snd_idle_saber)); //Sonido de sable idle
           Timer_idle.start();
        }

        Mpu6050.get_accel();     // Lee la aceleracion 
       
        
        
        if ( Mpu6050.is_knock() ) {
           startPlayback(snd_knock_saber, sizeof(snd_knock_saber)); // Sonido de sable golpeado
           Timer_led.start();
           count_tilt = N_TILT_SABER;
           st_loop = ST_KNOCK;
           
           }else if ( Mpu6050.is_move() ) {
                                       
                     startPlayback(snd_move_2_saber, sizeof(snd_move_2_saber)); // Sonido de sable movimiento 2
                                                                 
                     Timer_move.start();
                     st_loop = ST_MOVE;
                  } 

        if ( Button.is_pressed() ) {
             
              st_loop = ST_OFF;
              startPlayback(snd_in_saber, sizeof(snd_in_saber)); //Ssonido de sable de sable guardandose
            }
            
        break;

         case ST_KNOCK:
         
        //Ttoglea el led N_TILT_SABER veces y pasa al estado IDLE
        
        if( Timer_led.expired( T_TILT_SABER ) ) {
                  
                   Led.tgl() ;
                   count_tilt--;
                   Timer_led.start();
              }
        
        if ( !count_tilt )  {

           Led.on();           
           Timer_idle.start();
           startPlayback(snd_idle_saber, sizeof(snd_idle_saber)); //Sonido de sable idle
           st_loop = ST_IDLE;
           
        }

        
        break;

        case ST_MOVE:
          if( Timer_move.expired( T_SOUND_MOVE ) ) {
           startPlayback(snd_idle_saber, sizeof(snd_idle_saber)); // Sonido de sable idle
           Timer_move.start();
           st_loop = ST_IDLE;
        }
        
         break;

       case ST_OFF:

                 count_tilt = N_TILT_SABER;
                 Led.off() ;
                 st_loop = ST_WAIT_ON;
              
        
         break;
       
        default:
          st_loop = ST_INIT;
        
    }
}
