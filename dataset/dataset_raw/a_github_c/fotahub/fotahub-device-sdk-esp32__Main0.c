
#include "Main.h"

#include "DemoFOTAUpdateSelfTest.h"
#include "Configuration.h"
#include "DemoFOTAUpdateWorkflow.h"
#include "SinglePartitionDemoFirmwareUpdateInfoSerialReader.h"
#include "BlinkDrv.h"
#include "DemoProductInfo.h"
#include "FotaHub.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
  nvs_init();
  uart_init(UART_UNIT, &UART_CONFIG, UART_TX_PIN, UART_RX_PIN);
  blink_init(BLINK_PERIOD);
  wifi_init();
  
  printf("\n--------------------------------------------------------------------------\n");
  printf("Running %s %s firmware\n", DEMO_PRODUCT_NAME, DEMO_PRODUCT_FIRMWARE_VERSION);
  printf("--------------------------------------------------------------------------\n\n");
  
  firmwareUpdateInfoReader_init();
  fotaUpdateWorkflow_init();
  fotahub_init(DEMO_PRODUCT_ID, DEMO_PRODUCT_NAME, &ESP32_FOTA_UPDATE_CLIENT_CONFIG);
  
  wifiStation_connect(WIFI_STATION_SSID, WIFI_STATION_PASSPHRASE);
  
  xTaskCreate(&demoTasks,"demoTasks",TASK_DEFAULT_STACK_SIZE * 5,NULL,10,NULL);
}

void demoTasks(void *args)
{
  while (true)
  {
    uart_recvTask();
    firmwareUpdateInfoReader_run();
    fotahub_run();
    blink_run();
    vTaskDelay(10);
  }
}
