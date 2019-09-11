#ifndef RadioengeLoraWAN_h
#define RadioengeLoraWAN_h
/*
----------------------WIP------------------------
Library made to make simple the work with the end device RadioengeLoraWAN.

The target device of interfacing is an ESP32, because of the multiple hardware serial available.

Author: André Pastório - EdanPotter
*/

#include "Arduino.h"

#define debugSerial Serial
#define loraSerial Serial2
#define DEBUG_BAUDRATE 9600

enum AT_COMMANDS{
    DADDR = 0,
    APPKEY,
    APPSKEY,
    NWSKEY,
    APPEUI,
    ADR,
    TXP,
    DR,
    DCS,
    PNM,
    RX2FQ,
    RX2DR,
    RX1DL,
    RX2DL,
    JN1DL,
    JN2DL,
    NJM,
    NWKID,
    CLASS,
    JOIN,
    NJS,
    SENDB,
    SEND,
    VER,
    CFM,
    SNR,
    RSSI,
    BAT,
    BAUDRATE,
    NBTRIALS,
    KEEPALIVE,
    TXCFM,
    CHMASK,
    ADC,
    GPIOC,
    WPIN,
    RPIN
};

class RadioengeLoraWAN {
    private:
        String devEui;
        String appEui;
        String appKey;
        String appSkey;
        String netSkey;
        String devAddr;
        bool joinMode;
    public:
        /*Constructor*/
        RadioengeLoraWAN();
        
        /*Initiate with previous configuration*/
        void begin();
        /*Initiate for ABP mode*/
        void begin(String appEui, String appSkey, String netSkey, String devAddr);
        /*Initiate for OTAA mode*/
        void begin(String appEui, String appKey);

        /*Send AT command trough loraSerial
        [params] 
        @command: String with the command*/
        String sendAtCommand(String command);
        /*Send AT command trough loraSerial with the time set
        [params]
        @command: String with the command
        @milliseconds: String with the command*/
        String sendAtCommand(String command, unsigned long millisenconds);
        /*Send AT command trough loraSerial with debug output
        [params]
        @command: String with the command*/
        String sendAtCommandVerbose(String command);

        /*Print in debugSerial the info of the object*/
        void printInfo();
        /*Print in debugSerial the info in the device*/
        void printInfoDevice();

        /*Parse the keys to match the AT command*/
        String parseKey(String key);

        /*Send a text message in default port(8)*/
        void send(String message);
        /*Send a text message in defined port*/
        void send(int port, String message);
        /*Send a hexadecimal message in default port(8)*/
        void sendHex(String message);
        /*Send a hexadecimal message in defined port*/
        void sendHex(int port, String message);
        /*Get device EUI
        
        Return a string with the device EUI*/
        String getDevEui();
        /*Get application EUI

        Return a string with the application EUI*/
        String getAppEui();
        /*Get application key

        Return a string with the application key*/
        String getAppKey();
        /*Get application session key
        
        Return a string with the application session key*/
        String getAppSkey();
        /*Get network session key
        
        Return a string with the network session key*/
        String getNetSkey();
        /*Get device address
        
        Return a string with the device address*/
        String getDevAddr();
        /*Get join mode
        
        Return a bool corresponding to the mode
        0 -> ABP
        1 -> OTAA*/
        bool getJoinMode();

};

#endif