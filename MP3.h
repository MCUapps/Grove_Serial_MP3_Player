/*
    MP3.h - Library for controlling WT5001 Grove MP3 Serial Player
*/
#ifndef __MP3_h
#define __MP3_h

#include <SoftwareSerial.h>

class MP3
{
    private:
        SoftwareSerial &_serial;
        unsigned char _commandBuff[8];

        void sendCommand();
        void op(uint8_t op);
        void op1(uint8_t op, uint8_t arg1);
        void op2(uint8_t op, uint8_t arg1, uint8_t arg2);
        void op3(uint8_t op, uint8_t arg1, uint8_t arg2, uint8_t arg3);
        void op4(uint8_t op, uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t arg4);

    public:
        MP3(SoftwareSerial &theSerial);
        bool available();

        void playSong(uint16_t no);
        void pausePlay();
        void stop();
        void next();
        void prev();
        void setVolume(uint8_t vol);
        void pushSong(uint16_t no);
        void setMode(uint8_t mode);

        void setDate(uint16_t year, uint8_t month, uint8_t date);
        void setTime(uint8_t hour, uint8_t minute, uint8_t second);
        void setAlarm(uint8_t hour, uint8_t minute, uint8_t second);
        void clrAlarm();

        void getVolume();
        void getStatus();
        void getSongs();
        void currentNo();
        void getCFStr();

        void getDate();
        void getTime();
};

#endif  // __MP3_h
