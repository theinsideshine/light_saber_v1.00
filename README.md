LightSaber
====
LightSaber is an open source c ++ program to control a prototype of a laser sword, tested on a board [Arduino mini](https://store.arduino.cc/usa/arduino-nano)
The board Arduino mini has an atmega328p processor

The intention is to have a code to be able to evaluate the functionalities of the prototype and decide if it is feasible to use processors of the type atmega328p. If the project advances on this code, the next version will be generated.

The schematic that was used in the prototype is in /docs/light_saber_v1.00.pdf)

The cpu is connected to an audio amplifier [PAM 8403](https://www.amazon.es/HER-PAM8403-Mini-Digital-Amplifier/dp/B073HFGZQC/ref=sr_1_4?dchild=1&keywords=amplifier+pam8403&qid = 1602953847 & sr = 8-4), through a voltage divider, which acts to set the output volume. It has a transistor to control a 1W LED and an accelerometer connected by I2C [MPU 6050] (https://www.ebay.com/c/27003531553?norover=1&mkevt=1&mkrid=21551-220875-27835-0&mkcid=2&keyword= & crlp = 435066188865_ & MT_ID = & geo_id = & rlsatarget = dsa-19959388920 & adpos = & device = c & loc = 1000073 & poi = & abcId = & cmpgn = 1569302356 & sitelnk = & gclid = EAIaIQobEAg3zeTJ74yRCYBAY87MIzeTJ73

To ensure the supply voltage, the battery charger was used [POWER BANK with HT4928](https://www.amazon.in/RV-USB-Charging-Circuit-Indicator/dp/B081H3T67L/ref=pd_lpo_353_img_0/258-3388245 -4850734? _encoding = UTF8 & pd_rd_i = B081H3T67L & pd_rd_r = ca252b08-22a7-4431-b149-0cf23170af52 & pd_rd_w = P1Ejk & pd_rd_wg = Y5PuY & pf_rd_p = 5a903e39-3cff-40f0-9a69-33552e242181 & pf_rd_r = APQJ2ZXVV42FRDD7XHN3 & psc = 1 & refrid = APQJ2ZXVV42FRDD7XHN3)
In the comments of the code you can see the connection pins.


The program was compiled with [Arduino Ide 1.8.13](https://www.arduino.cc/en/Main/software)
![](images/compilado.gif)

Support
-------

If you need assistance, contact me:

* Email      : educacion.ta@gmail.com


Contributing
------------
