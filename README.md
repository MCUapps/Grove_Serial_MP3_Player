Garan-Arduino
=============

This is my unofficial library and exmaple code to drive [Grove - Serial MP3 Player](http://www.seeedstudio.com/depot/Grove-Serial-MP3-Player-p-1542.html).

It's not perfect, but it's working.

SoftwareSerial works great as the communication channel with it. Just assign a pair of RX/TX, store some MP3 files in the micro-SD card, and your are ready to go.

NOTICES
-------

Although the wiring is simple, you must check the following very carefully

* If you are not using boards with Grove sockets, pick a pair of spare GPIO pins to act as your SoftwareSerial port.
* Better avoid hardare serial port (D0/D1) for other usages, such as an interactive console. 

Compatibilites
--------------

I tested the code mainly on Seeeduino Lotus (Atmega 328P). Since the only required driver is SoftwareSerial, I believe it should work with other Arduino-like development boards without modifications.

Examples
--------

There are 1 examples for now.

* MP3_Console -- Use Serial Monitor and your keyboard to test some commands. It also prints the returned bytes in hex format.
