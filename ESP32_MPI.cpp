/* EspDeviceInfo.cpp */
#include "ESP32_MPI.h"
#include <esp_mac.h> // Native ESP32 MAC functions


const EntradaTabela TabelaMAC[] = {
  {"98:CD:AC:50:27:98", "192.0.0.1",1}
};

const int NumESPs = sizeof(TabelaMAC) / sizeof(TabelaMAC[0]);

//Consulta a tabela MAC, e retorna o ID da ESP32
int myRank() {
  uint8_t mac[6];
  
  //Lê o MAC
  esp_read_mac(mac, ESP_MAC_WIFI_STA); 

  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
           
  String mac_string = String(macStr);
  for (int i = 0; i < NumESPs; i++) {
    if (mac_string.equalsIgnoreCase(TabelaMAC[i].macAddress)) 
    {
      return TabelaMAC[i].ID; // Encontrou
    }
  }
  return -1; // Retorna código de erro se não achou

}

//Retorna o IP associado a um ID
String getIP(int ID_ESP){

  for (int i = 0; i < NumESPs; i++)
  {
    if (ID_ESP == TabelaMAC[i].ID)
    {
      return String(TabelaMAC[i].IP);
    }
  }

  return String("IP nao encontrado");
}
