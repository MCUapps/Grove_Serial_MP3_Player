/*
    MP3_Console

    Simple test code to play with Garan Audio Module's commands.

    Email: fox@mcuapps.com
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "MP3.h"

#if !defined(__MSP430_CPU__)
    // for Arduino
    SoftwareSerial mp3Serial(2, 3); // RX, TX
#else
    // for MSP430
    SoftwareSerial mp3Serial(P1_4, P1_5); // RX, TX
#endif

MP3 player(mp3Serial);

void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(9600); 

#if !defined(__MSP430_CPU__)
    // wait for USB CDC serial port to connect.  Arduino Leonardo only
    while (!Serial) {
    }
#endif

    Serial.println("Console is ready!");
}

void loop() {
    if (Serial.available()) {
        switch(Serial.read()) {
        case '1':
            player.playSong(1);
            break;
        case '2':
            player.pushSong(2);
            break;
        case 'p':
            player.pausePlay();
            break;
        case 's':
            player.stop();
            break;
        case ']':
            player.next();
            break; 
        case '[':
            player.prev();
            break;
        case 'i':
            player.getStatus();
            break;
        case 'd':
            player.getDate();
            break;
        case 't':
            player.getTime();
            break;
        default:
            Serial.println("This key maps to none.");     
        }
    }

    /*
     * This is a simple parser which formats the returned bytes more readable.
     */
    static int current_op;
    static int wait_more = 0;

    if (mp3Serial.available()) {
        unsigned char recvByte = mp3Serial.read();
    
    if (wait_more) {
        Serial.print(' ' + String(recvByte, HEX));

        // CR if NO more bytes to wait
        if (!(wait_more -= 1)) Serial.println();
    } else {
        // reserve current_op for future usage
        current_op = recvByte;
        Serial.print(String(current_op, HEX));

        switch(recvByte) {
            case 0xC1:
            case 0xC2:
                wait_more = 1;
                break;
            case 0xC4:
            case 0xC6:
                wait_more = 2;
                break;
            case 0xC7:
            case 0xD1:
                wait_more = 4;
                break;
            case 0xD2:
                wait_more = 3;
                break;
            default:
                // CR
                Serial.println();
            }
        }
    }
}
