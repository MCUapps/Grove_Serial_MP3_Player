#include "MP3.h"

#include <string.h>

#include <Arduino.h>
#include <SoftwareSerial.h>

// play sound
#define OP_PLAY_SONG  0xA0
#define OP_PAUSE_PLAY 0xA3
#define OP_STOP       0xA4
#define OP_NEXT       0xA5
#define OP_PREV       0xA6
#define OP_SET_VOLUME 0xA7
#define OP_PUSH_SONG  0xA8
#define OP_SET_MODE   0xA9

// write to clock
#define OP_SET_DATE   0xB1
#define OP_SET_TIME   0xB2
#define OP_SET_ALARM  0xB3
#define OP_CLR_ALARM  0xB5

// read back
#define OP_GET_VOLUME 0xC1
#define OP_GET_STATUS 0xC2
#define OP_GET_SONGS  0xC4
#define OP_CURRENT_NO 0xC6
#define OP_GET_CF_STR 0xC7

// read clock
#define OP_GET_DATE   0xD1
#define OP_GET_TIME   0xD2

MP3::MP3(SoftwareSerial &theSerial) : _serial(theSerial)
{
    _serial.begin(9600);
}

bool MP3::available()
{
    return _serial.available();
}

void MP3::sendCommand()
{
    _serial.write(0x7E);

    for (uint16_t i = 0; i < _commandBuff[0]; i++) {
        _serial.write(_commandBuff[i]);
    }

    _serial.write(0x7E);
}

void MP3::op(uint8_t op)
{
    _commandBuff[0] = 0x02;
    _commandBuff[1] = op;

    sendCommand();
}

void MP3::op1(uint8_t op, uint8_t arg1)
{
    _commandBuff[0] = 0x03;
    _commandBuff[1] = op;
    _commandBuff[2] = arg1;

    sendCommand();
}

void MP3::op2(uint8_t op, uint8_t arg1, uint8_t arg2)
{
    _commandBuff[0] = 0x04;
    _commandBuff[1] = op;
    _commandBuff[2] = arg1;
    _commandBuff[3] = arg2;

    sendCommand();
}

void MP3::op3(uint8_t op, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
    _commandBuff[0] = 0x05;
    _commandBuff[1] = op;
    _commandBuff[2] = arg1;
    _commandBuff[3] = arg2;
    _commandBuff[4] = arg3;

    sendCommand();
}

void MP3::op4(uint8_t op, uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t arg4)
{
    _commandBuff[0] = 0x06;
    _commandBuff[1] = op;
    _commandBuff[2] = arg1;
    _commandBuff[3] = arg2;
    _commandBuff[4] = arg3;
    _commandBuff[5] = arg4;

    sendCommand();
}

void MP3::playSong(uint16_t no)
{
    op2(OP_PLAY_SONG, no >> 8, no & 0xFF);
}

void MP3::pushSong(uint16_t no)
{
    op2(OP_PUSH_SONG, no >> 8, no & 0xFF);
}

void MP3::pausePlay()
{
    op(OP_PAUSE_PLAY);
}

void MP3::stop()
{
    op(OP_STOP);
}

void MP3::next()
{
    op(OP_NEXT);
}

void MP3::prev()
{
    op(OP_PREV);
}

void MP3::setVolume(uint8_t vol)
{
    op1(OP_SET_VOLUME, vol);
}

void MP3::setMode(uint8_t mode)
{
    op1(OP_SET_MODE, mode);
}

void MP3::setDate(uint16_t year, uint8_t month, uint8_t date)
{
    op4(OP_SET_DATE, year >> 8, year & 0xFF, month, date);
}

void MP3::setTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    op3(OP_SET_TIME, hour, minute, second);
}

void MP3::setAlarm(uint8_t hour, uint8_t minute, uint8_t second)
{
    op3(OP_SET_ALARM, hour, minute, second);	
}

void MP3::clrAlarm()
{
    op(OP_CLR_ALARM);
}

void MP3::getVolume()
{
    op(OP_GET_VOLUME);
}

void MP3::getStatus()
{
    op(OP_GET_STATUS);
}

void MP3::getSongs()
{
    op(OP_GET_SONGS);
}

void MP3::currentNo()
{
    op(OP_CURRENT_NO);
}

void MP3::getCFStr()
{
    op(OP_GET_CF_STR);
}

void MP3::getDate()
{
    op(OP_GET_DATE);
}

void MP3::getTime()
{
    op(OP_GET_TIME);
}
