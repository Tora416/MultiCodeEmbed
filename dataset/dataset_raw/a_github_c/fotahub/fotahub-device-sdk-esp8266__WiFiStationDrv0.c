
#include "WiFiStationDrv.h"

#include "FotaHub.h"
#include <user_interface.h>
#include <string.h>

static void ICACHE_FLASH_ATTR wifiEventHandlerCallback(System_Event_t *sys_evt);

bool ICACHE_FLASH_ATTR wifiStation_connect(char const *ssid, char const *password)
{
  wifi_set_event_handler_cb(&wifiEventHandlerCallback);
  
  uint8_t currentMode = wifi_get_opmode();
  currentMode = ((currentMode |= (STATION_MODE)));
  currentMode = ((currentMode &= ~(SOFTAP_MODE)));
  if (!wifi_set_opmode_current(currentMode)) 
  {
    os_printf("Failed to activate Wi-Fi station mode\n");
    return false;
  }
  
  struct station_config config = { 0 };
  size_t ssidLen = os_strlen(ssid);
  os_memcpy(config.ssid, ssid, ssidLen);
  if (ssidLen < sizeof(config.ssid)) 
  {
    config.ssid[ssidLen] = 0;
  }
  size_t passwordLen = os_strlen(password);
  os_memcpy(config.password, password, passwordLen);
  if (passwordLen < sizeof(config.password)) 
  {
    config.password[passwordLen] = 0;
  }
  if (!wifi_station_set_config_current(&config)) 
  {
    os_printf("Failed to set Wi-Fi station configuration\n");
    return false;
  }
  
  
  wifi_station_connect();
  return true;
}

static void ICACHE_FLASH_ATTR wifiEventHandlerCallback(System_Event_t *sys_evt)
{
  switch (sys_evt->event)
  {
    case EVENT_STAMODE_CONNECTED:
    {
      
      break;
    }
    case EVENT_STAMODE_DISCONNECTED:
    {
      fotahub_notifyNetworkStatusChange(NETWORK_ADAPTER_STATUS_DISCONNECTED);
      break;
    }
    case EVENT_STAMODE_AUTHMODE_CHANGE:
    {
      
      break;
    }
    case EVENT_STAMODE_GOT_IP:
    {
      fotahub_notifyNetworkStatusChange(NETWORK_ADAPTER_STATUS_CONNECTED);
      break;
    }
    case EVENT_STAMODE_DHCP_TIMEOUT:
    {
      os_printf("Failed to obtain Wi-Fi station IP address\n");
      break;
    }
    case EVENT_SOFTAPMODE_PROBEREQRECVED:
    {
      
      break;
    }
    case EVENT_OPMODE_CHANGED:
    {
      
      break;
    }
    default: {
      os_printf("Unexpected Wi-Fi event encountered: %d\n", sys_evt->event);
      break;
    }
  }
}
