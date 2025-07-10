
#include "Main.h"

#include "Configuration.h"
#include "DemoFOTAUpdateWorkflow.h"
#include "SinglePartitionDemoFirmwareUpdateInfoFileReader.h"
#include "DemoProductInfo.h"
#include "FotaHub.h"
#include <string.h>
#include <limits.h>
#include <direct.h>

static char *dirname(char *path);

int32_t main(int32_t argc, char *argv[])
{
  
  char *programDir = dirname(_strdup(argv[0]));
  _chdir(programDir);
  
  printf("\n--------------------------------------------------------------------------\n");
  printf("Running %s %s firmware\n", DEMO_PRODUCT_NAME, DEMO_PRODUCT_FIRMWARE_VERSION);
  printf("--------------------------------------------------------------------------\n\n");
  
  firmwareUpdateInfoReader_init();
  fotaUpdateWorkflow_init();
  fotahub_init(argv[0], DEMO_PRODUCT_ID, DEMO_PRODUCT_NAME, &FOTA_UPDATE_CLIENT_CONFIG);
  
  fotahub_notifyNetworkStatusChange(NETWORK_ADAPTER_STATUS_CONNECTED);
  
  firmwareUpdateInfoReader_explain(programDir);
  
  while (true)
  {
    firmwareUpdateInfoReader_run();
    fotahub_run();
  }
}

static char *dirname(char *path)
{
  char *lastSeparator = strrchr(path, '\\');
  if (lastSeparator != NULL) 
  {
    *lastSeparator = '\0';
    return path;
  }
  else
  {
    *path = '\0';
  }
  return path;
}
