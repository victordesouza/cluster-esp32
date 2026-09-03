/* EspDeviceInfo.h */
#ifndef ESP32_MPI
#define ESP32_MPI
#include <Arduino.h> //Para tipo String
#define TABLE_SIZE



struct EntradaTabela {
  const char* macAddress;
  const char* IP;
  int ID;
};



int myRank();
String getIP(int ID_ESP);




#endif