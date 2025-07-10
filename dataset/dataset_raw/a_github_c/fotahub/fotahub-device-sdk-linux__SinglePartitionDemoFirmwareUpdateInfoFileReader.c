
#include "SinglePartitionDemoFirmwareUpdateInfoFileReader.h"

#include "BinHexConverter.h"
#include "DemoProductInfo.h"
#include "FotaHub.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ctype.h"
#include <errno.h>
#include <unistd.h>

static bool isWhitespace(char *str);

static bool createFirmwareUpdateInfoFile(void);

static void openFirmwareUpdateInfoFileInVSCode(void);

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

void firmwareUpdateInfoReader_init(void)
{
  size_t updateVerificationDataSize = getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM);
  updateVerificationData = ((uint8_t *)(malloc(updateVerificationDataSize)));
  memset(updateVerificationData, 0, updateVerificationDataSize);
  
  if (!createFirmwareUpdateInfoFile()) 
  {
    return;
  }
  
  openFirmwareUpdateInfoFileInVSCode();
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
  FILE *updateInfoFile = fopen(DEMO_PRODUCT_UPDATE_INFO_FILE_NAME, "w");
  if (updateInfoFile == NULL) 
  {
    printf("Failed to create %s: %s (error code: %i)\n", DEMO_PRODUCT_UPDATE_INFO_FILE_NAME, strerror(errno), errno);
    return false;
  }
  fclose(updateInfoFile);
  return true;
}

static void openFirmwareUpdateInfoFileInVSCode(void)
{
  char vsCodePath[260 + 1] = "";
  char *os = getenv("OS");
  if (os != NULL && strcmp(os, "Windows_NT") == 0) 
  {
    snprintf(vsCodePath, sizeof(vsCodePath), "C:\\Users\\%s\\AppData\\Local\\Programs\\Microsoft VS Code\\bin\\code", getenv("USERNAME"));
  }
  else
  {
    snprintf(vsCodePath, sizeof(vsCodePath), "/usr/bin/code");
  }
  
  if (access(vsCodePath, F_OK) != -1) 
  {
    char openCommand[260 + 1] = "";
    snprintf(openCommand, sizeof(openCommand), "code %s", DEMO_PRODUCT_UPDATE_INFO_FILE_NAME);
    system(openCommand);
  }
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
