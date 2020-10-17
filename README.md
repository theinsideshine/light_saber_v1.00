LightSaber
====
LightSaber is an open source c ++ program to control a prototype of a laser sword, tested on a board [Arduino mini](https://store.arduino.cc/usa/arduino-nano)
The board Arduino mini has an atmega328p processor

The intention is to have a code to be able to evaluate the functionalities of the prototype and decide if it is feasible to use processors of the type atmega328p. If the project advances on this code, the next version will be generated.

The prototype has the cpu connected to an audio amplifier [PAM 8403](https://www.amazon.es/HER-PAM8403-Mini-Amplificador-Digital/dp/B073HFGZQC/ref=sr_1_4?dchild=1&keywords=amplificador+pam8403&qid=1602953847&sr=8-4) ,
 an LED controller , and an accelerator connected by I2C[MPU 6050](https://www.ebay.com/c/27003531553?norover=1&mkevt=1&mkrid=21551-220875-27835-0&mkcid=2&keyword=&crlp=435066188865_&MT_ID=&geo_id=&rlsatarget=dsa-19959388920&adpos=&device=c&loc=1000073&poi=&abcId=&cmpgn=1569302356&sitelnk=&gclid=EAIaIQobChMIzeTJ74y87AIVVgaRCh3-zg7qEAAYBCAAEgLMjfD_BwE) ,
 in the comments of the code you can see the connection pins. 
The schematic that was used in the prototype is:
![](docs/light_saber_v1.00.pdf)


The program was compiled with [Arduino Ide 1.8.13](https://www.arduino.cc/en/Main/software)
![](images/compilado.gif)

Support
-------

If you need assistance, contact me:

* Email      : educacion.ta@gmail.com


Contributing
------------
