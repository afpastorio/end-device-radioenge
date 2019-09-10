#include "RadioengeLoraWAN.h"

RadioengeLoraWAN::RadioengeLoraWAN() {
    ///debugSerial.begin(DEBUG_BAUDRATE);
    this->devEui = sendAtCommand("AT+DEUI=?");
    this->appEui = sendAtCommand("AT+APPEUI=?");
    this->appKey = sendAtCommand("AT+APPKEY=?");
    this->appSkey = sendAtCommand("AT+APPSKEY=?");
    this->netSkey = sendAtCommand("AT+NWKSKEY=?");
    this->devAddr = sendAtCommand("AT+DADDR=?");
    this->joinMode = sendAtCommand("AT+NJM=?").equals("1");

    debugSerial.println("Módulo iniciado...");
    printInfo();
}

RadioengeLoraWAN::RadioengeLoraWAN(String appEui, String appSkey, String netSkey, String devAddr) {
    //debugSerial.begin(DEBUG_BAUDRATE);

    this->joinMode = 0;
    sendAtCommand("AT+NJM=" + this->joinMode);
    this->appEui = appEui;
    sendAtCommand("AT+APPEUI=" + parseKey(appEui));
    this->appSkey = appSkey;
    sendAtCommand("AT+APPSKEY=" + parseKey(appSkey));
    this->netSkey = netSkey;
    sendAtCommand("AT+NWKSKEY=" + parseKey(netSkey));
    this->devAddr = devAddr;
    sendAtCommand("AT+DADDR=" + parseKey(devAddr));

    debugSerial.println("Módulo iniciado...");
    printInfo();
}
RadioengeLoraWAN::RadioengeLoraWAN(String appEui, String appKey) {
    //debugSerial.begin(DEBUG_BAUDRATE);

    this->joinMode = 1;
    sendAtCommand("AT+NJM=" + this->joinMode);
    this->appEui = appEui;
    sendAtCommand("AT+APPEUI=" + parseKey(appEui));
    this->appKey = appKey;
    sendAtCommand("AT+APPKEY=" + parseKey(appKey));

    sendAtCommand("AT+JOIN");

    debugSerial.println("Módulo iniciado...");
    printInfo();
}


String RadioengeLoraWAN::sendAtCommand(String command) {
    String result = "";
    unsigned long startTime = millis();
    loraSerial.println(command);
    while (millis() - startTime < 2000) {
        if (loraSerial.available()) {
            char c = loraSerial.read();
            //debugSerial.write(c);
            result += c;
        }
    }
    //debugSerial.println("RESULT: "+ result);
    return result;
}
String RadioengeLoraWAN::sendAtCommand(String command, unsigned long millisenconds) {
    String result = "";
    loraSerial.println(command);
    unsigned long startTime = millis();
    while (millis() - startTime < millisenconds) {
        if (loraSerial.available()) {
            char c = loraSerial.read();
            //debugSerial.write(c);
            result += c;
        }
    }
    //debugSerial.println(result);
    return result;
}
String RadioengeLoraWAN::sendAtCommandVerbose(String command) {
    String result = "";
    debugSerial.print("Enviado: ");
    debugSerial.println(command);
    loraSerial.println(command);
    unsigned long startTime = millis();
    debugSerial.print("Recebido: ");
    while (millis() - startTime < 2000) {
        if (loraSerial.available()) {
            char c = loraSerial.read();
            debugSerial.write(c);
            result += c;
        }
    }
    debugSerial.println();
    return result;
}
void RadioengeLoraWAN::printInfo() {
    if(joinMode) {
        debugSerial.println("Modo de autenticação: OTAA");
        debugSerial.println("DEVEUI: " + devEui);
        debugSerial.println("APPEUI: " + appEui);
        debugSerial.println("APPKEY: " + appKey);
    } else {
        debugSerial.println("Modo de autenticação: ABP");
        debugSerial.println("DEVEUI: " + devEui);
        debugSerial.println("NETSKEY: " + netSkey);
        debugSerial.println("APPSKEY: " + appSkey);
        debugSerial.println("DEVADDR: " + devAddr);
    }
}
void RadioengeLoraWAN::printInfoDevice() {
    if(joinMode) {
        debugSerial.println("Modo de autenticação: OTAA");
        debugSerial.println("DEVEUI: " + sendAtCommand("AT+DEUI=?"));
        debugSerial.println("APPEUI: " + sendAtCommand("AT+APPEUI=?"));
        debugSerial.println("APPKEY: " + sendAtCommand("AT+APPKEY=?"));
    } else {
        debugSerial.println("Modo de autenticação: ABP");
        debugSerial.println("DEVEUI: " + sendAtCommand("AT+DEUI=?"));
        debugSerial.println("NETSKEY: " + sendAtCommand("AT+NWKSKEY=?"));
        debugSerial.println("APPSKEY: " + sendAtCommand("AT+APPSKEY=?"));
        debugSerial.println("DEVADDR: " + sendAtCommand("AT+DADDR=?"));
    }
}
void RadioengeLoraWAN::send(String message) {
    debugSerial.println("Sending... " + message);
    sendAtCommand("AT+SEND=8:" + message);
}
void RadioengeLoraWAN::send(int port, String message) {
    debugSerial.println("Sending... " + message);
    String toSend = "";
    toSend.concat(String(port));
    toSend.concat(":");
    toSend.concat(message);
    sendAtCommand("AT+SEND=" + toSend);
}
void RadioengeLoraWAN::sendHex(String message) {
    debugSerial.println("Sending... " + message);
    sendAtCommand("AT+SENDB=8:" + message);
}
void RadioengeLoraWAN::sendHex(int port, String message) {
    String toSend = "";
    toSend.concat(String(port));
    toSend.concat(":");
    toSend.concat(message);
    sendAtCommand("AT+SENDB=" + toSend);
}


String RadioengeLoraWAN::parseKey(String key) {
    String result = "";
    for(int i = 0; i < key.length(); i=i+2) {
        if(i != 0) result += ":";
        result.concat(key.charAt(i));
        result.concat(key.charAt(i+1));
    }
    return result;
}
String RadioengeLoraWAN::getDevEui() {
    return devEui;
}
String RadioengeLoraWAN::getAppEui() {
    return appEui;
}
String RadioengeLoraWAN::getAppKey() {
    return appKey;
}
String RadioengeLoraWAN::getAppSkey() {
    return appSkey;
}
String RadioengeLoraWAN::getNetSkey() {
    return netSkey;
}
String RadioengeLoraWAN::getDevAddr() {
    return devAddr;
}
bool RadioengeLoraWAN::getJoinMode() {
    return joinMode;
}