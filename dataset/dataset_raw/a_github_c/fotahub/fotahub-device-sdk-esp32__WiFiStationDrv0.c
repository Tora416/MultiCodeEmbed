
#include "WiFiStationDrv.h"

#include "FotaHub.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include <string.h>

static esp_err_t wifiEventHandlerCallback(void *ctx, system_event_t *event);

void wifi_init(void)
{
  tcpip_adapter_init();
  esp_event_loop_init(&wifiEventHandlerCallback, NULL);
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_mode(WIFI_MODE_STA);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
}

bool wifiStation_connect(char const *ssid, char const *passphrase)
{
  wifi_config_t config = 
  {
    .sta = 
    {
      .bssid_set = false
    }
  };
  size_t ssidLen = strlen(ssid);
  memcpy(config.sta.ssid, ssid, ssidLen);
  if (ssidLen < sizeof(config.sta.ssid)) 
  {
    config.sta.ssid[ssidLen] = 0;
  }
  size_t passphraseLen = strlen(passphrase);
  memcpy(config.sta.password, passphrase, passphraseLen);
  if (passphraseLen < sizeof(config.sta.password)) 
  {
    config.sta.password[passphraseLen] = 0;
  }
  
  esp_wifi_set_config(WIFI_IF_STA, &config);
  esp_wifi_start();
  esp_wifi_connect();
  
  return true;
}

static esp_err_t wifiEventHandlerCallback(void *ctx, system_event_t *event)
{
  switch (event->event_id)
  {
    case SYSTEM_EVENT_STA_GOT_IP:
    {
      fotahub_notifyNetworkStatusChange(NETWORK_ADAPTER_STATUS_CONNECTED);
      break;
    }
    case SYSTEM_EVENT_STA_LOST_IP:
    case SYSTEM_EVENT_STA_DISCONNECTED:
    case SYSTEM_EVENT_STA_STOP:
    case SYSTEM_EVENT_STA_DHCP_TIMEOUT:
    {
      fotahub_notifyNetworkStatusChange(NETWORK_ADAPTER_STATUS_DISCONNECTED);
      break;
    }
    default: {
      break;
    }
  }
  return ESP_OK;
}
