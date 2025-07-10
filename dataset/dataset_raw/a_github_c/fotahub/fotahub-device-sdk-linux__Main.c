
#include "Main.h"

#include "Configuration.h"
#include "DemoFOTAUpdateWorkflow.h"
#include "SinglePartitionDemoFirmwareUpdateInfoFileReader.h"
#include "DemoFOTAUpdateWorkflowFilePersistence.h"
#include "DemoFOTAUpdateSelfTest.h"
#include "DemoProductInfo.h"
#include "FotaHub.h"
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <limits.h>

int32_t main(int32_t argc, char *argv[])
{
  
  char *programDir = dirname(strdup(argv[0]));
  chdir(programDir);
  
  firmwareUpdateInfoReader_init();
  fotaUpdateWorkflow_init();
  fotaUpdateSelfTest_init();
  fotahub_init(argv[0], DEMO_PRODUCT_ID, DEMO_PRODUCT_NAME, &FOTA_UPDATE_CLIENT_CONFIG);
  
  printf("\n--------------------------------------------------------------------------\n");
  printf("Running %s %s firmware\n", DEMO_PRODUCT_NAME, DEMO_PRODUCT_FIRMWARE_VERSION);
  printf("--------------------------------------------------------------------------\n\n");
  
  
  fotahub_notifyNetworkStatusChange(NETWORK_ADAPTER_STATUS_CONNECTED);
  
  char *separator = (strlen(programDir) > 0) ? ("/") : ("");
  printf("Waiting for firmware update info (<new-version>:<checksum-or-signature>) to be entered and saved in '%s%s%s' file\n", programDir, separator, DEMO_PRODUCT_UPDATE_INFO_FILE_NAME);
  
  while (true)
  {
    firmwareUpdateInfoReader_run();
    fotahub_run();
  }
}
