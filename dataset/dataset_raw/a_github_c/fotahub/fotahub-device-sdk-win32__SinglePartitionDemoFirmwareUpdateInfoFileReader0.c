
#include "SinglePartitionDemoFirmwareUpdateInfoFileReader.h"

#include "BinHexConverter.h"
#include "DemoProductInfo.h"
#include "FotaHub.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ctype.h"
#include <errno.h>

static bool isWhitespace(char *str);

static char *separator(void);

static bool createFirmwareUpdateInfoFile(void);

static bool canOpenFirmwareUpdateInfoFile(void);

static void openFirmwareUpdateInfoFile(void);

static bool loadFirmwareUpdateInfoFile(char *updateInfoString, size_t updateInfoStringSize);

static bool parseFirmwareUpdateInfo(char *updateInfoString);

static char lastUpdateInfoString[260 + 1] = { 0 };

static char updateVersion[MAX_UPDATE_VERSION_LENGTH + 1] = { 0 };

static uint8_t *updateVerificationData = NULL;

static bool isWhitespace(char *str)
{
  size_t idx = 0;
  char currentChr = str[idx++];
  while (currentChr != '\0')
  {
    if (isspace(currentChr) == 0) 
    {
      return false;
    }
    currentChr = str[idx++];
  }
  return true;
}

static char *separator(void)
{
  char *os = getenv("OS");
  if (os != NULL && strcmp(os, "Windows_NT") == 0) 
  {
    return "\\";
  }
  else
  {
    return "/";
  }
}

void firmwareUpdateInfoReader_init(void)
{
  size_t updateVerificationDataSize = getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM);
  updateVerificationData = ((uint8_t *)(malloc(updateVerificationDataSize)));
  memset(updateVerificationData, 0, updateVerificationDataSize);
  
  
  if (!createFirmwareUpdateInfoFile()) 
  {
    return;
  }
  
  if (canOpenFirmwareUpdateInfoFile()) 
  {
    openFirmwareUpdateInfoFile();
  }
}

void firmwareUpdateInfoReader_explain(char *programDir)
{
  
  char *sep = (strlen(programDir) > 0) ? (separator()) : ("");
  printf("Waiting for firmware update info to be entered and saved in '%s%s%s' file\n(if this file has not been opened automatically already, just open it manually in an editor of your choice)\n", programDir, sep, DEMO_PRODUCT_UPDATE_INFO_FILE_NAME);
  printf("Expected firmware update info format: <new-version>:<checksum-or-signature> (e.g., 1.1:8639e6e80b089338e51fac17d5faa647c4c05368e46af5c42583fb34c0) \n");
}

void firmwareUpdateInfoReader_run(void)
{
  
  char updateInfoString[260 + 1] = "";
  if (!loadFirmwareUpdateInfoFile(updateInfoString, sizeof(updateInfoString))) 
  {
    memset(lastUpdateInfoString, 0, sizeof(lastUpdateInfoString));
    return;
  }
  
  
  if (strncmp(updateInfoString, lastUpdateInfoString, 260) == 0) 
  {
    return;
  }
  strncpy(lastUpdateInfoString, updateInfoString, 260);
  
  
  if (!parseFirmwareUpdateInfo(updateInfoString)) 
  {
    return;
  }
  
  
  printf("Firmware update request towards version %s received\n", updateVersion);
  fotaUpdateWorkflow_onFirmwareUpdateVersionChanged(updateVersion);
}

static bool createFirmwareUpdateInfoFile(void)
{
  FILE *updateInfoFile = fopen(DEMO_PRODUCT_UPDATE_INFO_FILE_NAME, "wb");
  if (updateInfoFile == NULL) 
  {
    printf("Failed to create %s: %s (error code: %i)\n", DEMO_PRODUCT_UPDATE_INFO_FILE_NAME, strerror(errno), errno);
    return false;
  }
  fclose(updateInfoFile);
  return true;
}

static bool canOpenFirmwareUpdateInfoFile(void)
{
  
  char *os = getenv("OS");
  char command[260 + 1] = "";
  if (os != NULL && strcmp(os, "Windows_NT") == 0) 
  {
    snprintf(command, sizeof(command), "powershell -command \"where.exe code | Measure-Object -Line | Select-Object -ExpandProperty Lines\"");
  }
  else
  {
    snprintf(command, sizeof(command), "which code | wc -l");
  }
  
  
  FILE *commandPipe = popen(command, "r");
  if (commandPipe == NULL) 
  {
    printf("Failed to run '%s' command: %s (error code: %i)\n", command, strerror(errno), errno);
    return false;
  }
  
  
  int32_t count = 0;
  if (fscanf(commandPipe, "%d", &count) != 1) 
  {
    pclose(commandPipe);
    return false;
  }
  pclose(commandPipe);
  return count > 0;
}

static void openFirmwareUpdateInfoFile(void)
{
  
  char command[260 + 1] = "";
  snprintf(command, sizeof(command), "code %s", DEMO_PRODUCT_UPDATE_INFO_FILE_NAME);
  system(command);
}

static bool loadFirmwareUpdateInfoFile(char *updateInfoString, size_t updateInfoStringSize)
{
  FILE *updateInfoFile = fopen(DEMO_PRODUCT_UPDATE_INFO_FILE_NAME, "r");
  if (updateInfoFile == NULL) 
  {
    
    return false;
  }
  memset(updateInfoString, 0, updateInfoStringSize);
  while (isWhitespace(updateInfoString))
  {
    if (fgets(updateInfoString, ((int32_t) updateInfoStringSize), updateInfoFile) == NULL) 
    {
      
      fclose(updateInfoFile);
      return false;
    }
  }
  fclose(updateInfoFile);
  return true;
}

static bool parseFirmwareUpdateInfo(char *updateInfoString)
{
  
  memset(updateVersion, 0, sizeof(updateVersion));
  memset(updateVerificationData, 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
  if (strstr(updateInfoString, UPDATE_INFO_SEPARATOR) == NULL) 
  {
    printf("Firmware update request with missing version and/or verification data entered\n");
    return false;
  }
  
  
  char *parsedVersion = strtok(updateInfoString, UPDATE_INFO_DELIMITERS);
  if (parsedVersion == NULL) 
  {
    printf("Firmware update request with missing version and verification data entered\n");
    return false;
  }
  if (strlen(parsedVersion) > getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM)) 
  {
    printf("Received firmware update version too long (max. length = %hhu)\n", MAX_UPDATE_VERSION_LENGTH);
    return false;
  }
  strncpy(updateVersion, parsedVersion, sizeof(updateVersion));
  
  
  char *parsedVerificationData = strtok(NULL, UPDATE_INFO_DELIMITERS);
  if (parsedVerificationData == NULL) 
  {
    printf("Firmware update request with missing version or verification data entered\n");
    memset(updateVersion, 0, sizeof(updateVersion));
    return false;
  }
  if (strlen(parsedVerificationData) > getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM) << 1) 
  {
    printf("Received firmware update verification data too long (max. length = %hhu)\n", MAX_UPDATE_VERSION_LENGTH << 1);
    memset(updateVersion, 0, sizeof(updateVersion));
    return false;
  }
  if (convertHexString8ToBinData(parsedVerificationData, strlen(parsedVerificationData), updateVerificationData, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM)) == 0) 
  {
    printf("Firmware update request with invalid verification data entered\n");
    memset(updateVersion, 0, sizeof(updateVersion));
    memset(updateVerificationData, 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
    return false;
  }
  
  return true;
}

void fotahub_onProvideFirmwareUpdateVerificationInfo(FirmwareUpdateInfo_t const *pUpdateInfo, FOTAUpdateVerificationAlgorithm_t *pVerificationAlgorithm, uint8_t const  **ppVerificationData)
{
  *pVerificationAlgorithm = DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM;
  *ppVerificationData = updateVerificationData;
}
