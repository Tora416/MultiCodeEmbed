
#include "WiFiHelper.h"

static esp_err_t setMode(wifi_mode_t mode, bool enable);

esp_err_t enableStationMode(void)
{
  return setMode(WIFI_MODE_STA, true);
}

esp_err_t disableStationMode(void)
{
  return setMode(WIFI_MODE_STA, false);
}

esp_err_t enableAccessPointMode(void)
{
  return setMode(WIFI_MODE_AP, true);
}

esp_err_t disableAccessPointMode(void)
{
  return setMode(WIFI_MODE_AP, false);
}

static esp_err_t setMode(wifi_mode_t mode, bool enable)
{
  wifi_mode_t currentMode;
  esp_err_t error = ESP_OK;
  
  esp_wifi_get_mode(&currentMode);
  printf("Old wifi mode: %u\n", ((uint32_t)((currentMode))));
  
  bool isEnabled = (currentMode & mode) != 0;
  if (isEnabled != enable) 
  {
    if (enable) 
    {
      error = esp_wifi_set_mode(((wifi_mode_t)((currentMode | mode))));
    }
    else
    {
      wifi_mode_t nextMode = ((wifi_mode_t)((currentMode & (~mode))));
      if (nextMode == WIFI_MODE_NULL) 
      {
        
        esp_wifi_set_mode(WIFI_MODE_NULL);
        error = esp_wifi_stop();
      }
      else
      {
        error = esp_wifi_set_mode(nextMode);
      }
    }
  }
  return error;
}

bool getIPConfig(IPConfig_t *pIPConfig, wifi_mode_t mode)
{
  if (pIPConfig == NULL) 
  {
    return false;
  }
  tcpip_adapter_ip_info_t info;
  if (tcpip_adapter_get_ip_info((mode == WIFI_MODE_AP) ? (TCPIP_ADAPTER_IF_AP) : (TCPIP_ADAPTER_IF_STA), &info) == ESP_OK) 
  {
    pIPConfig->localIPAddress = info.ip.addr;
    pIPConfig->gatewayIPAddress = info.gw.addr;
    pIPConfig->subnetMask = info.netmask.addr;
    return true;
  }
  return false;
}
