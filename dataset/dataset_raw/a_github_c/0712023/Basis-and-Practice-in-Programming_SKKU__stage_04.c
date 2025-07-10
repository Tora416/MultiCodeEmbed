void stage_04(char input_list[INPUT_LEN][BUF_SIZ])
{
  printf("\n");
  char pnt[20] = ".";
  char exc[20] = "!";
  char qes[20] = "?";
  char at[20] = "@";
  char unb[20] = "_";

  char buffer[50] = "";
  for(int i = 0; i<7;i++){
    strcpy(buffer, pnt);
    strcat(buffer, input_list[i]);
    crack(4, buffer);
    for(int j = 0; j<strlen(input_list[i]);j++){
      char tmp[2] = {};
      tmp[0] = buffer[j];
      buffer[j] = buffer[j+1];
      buffer[j+1] = tmp[0];
      crack(4, buffer);
    }
  }

  for(int i = 0; i<7;i++){
    strcpy(buffer, exc);
    strcat(buffer, input_list[i]);
    crack(4, buffer);
    for(int j = 0; j<strlen(input_list[i]);j++){
      char tmp[2] = {};
      tmp[0] = buffer[j];
      buffer[j] = buffer[j+1];
      buffer[j+1] = tmp[0];
      crack(4, buffer);
    }
  }

  for(int i = 0; i<7;i++){
    strcpy(buffer, qes);
    strcat(buffer, input_list[i]);
    crack(4, buffer);
    for(int j = 0; j<strlen(input_list[i]);j++){
      char tmp[2] = {};
      tmp[0] = buffer[j];
      buffer[j] = buffer[j+1];
      buffer[j+1] = tmp[0];
      crack(4, buffer);
    }
  }

  for(int i = 0; i<7;i++){
    strcpy(buffer, at);
    strcat(buffer, input_list[i]);
    crack(4, buffer);
    for(int j = 0; j<strlen(input_list[i]);j++){
      char tmp[2] = {};
      tmp[0] = buffer[j];
      buffer[j] = buffer[j+1];
      buffer[j+1] = tmp[0];
      crack(4, buffer);
    }
  }

  for(int i = 0; i<7;i++){
    strcpy(buffer, unb);
    strcat(buffer, input_list[i]);
    crack(4, buffer);
    for(int j = 0; j<strlen(input_list[i]);j++){
      char tmp[2] = {};
      tmp[0] = buffer[j];
      buffer[j] = buffer[j+1];
      buffer[j+1] = tmp[0];
      crack(4, buffer);
    }
  }
  return;
}
