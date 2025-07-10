
#include "DemoFOTAUpdateWorkflowFilePersistence.h"

#include "DemoFOTAUpdateWorkflowPersistence.h"

void saveState(int16_t state)
{
  FILE *file = fopen(DEMO_PRODUCT_UPDATE_STATE_FILE_NAME, "wb");
  if (file == NULL) 
  {
    printf("Failed to open %s for writing\n", DEMO_PRODUCT_UPDATE_STATE_FILE_NAME);
    return;
  }
  if (fwrite(&state, sizeof(state), 1, file) != 1) 
  {
    printf("Failed to write statemachine state %hi to %s\n", state, DEMO_PRODUCT_UPDATE_STATE_FILE_NAME);
    fclose(file);
    return;
  }
  fclose(file);
}

int16_t loadState(void)
{
  FILE *file = fopen(DEMO_PRODUCT_UPDATE_STATE_FILE_NAME, "rb");
  if (file == NULL) 
  {
    return 0;
  }
  int16_t state = 0;
  if (fread(&state, sizeof(state), 1, file) != 1) 
  {
    fclose(file);
    return 0;
  }
  fclose(file);
  return state;
}
