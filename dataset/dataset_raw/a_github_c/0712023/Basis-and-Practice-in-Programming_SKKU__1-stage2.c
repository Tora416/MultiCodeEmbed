{
    int len1 = 0;
  int len2 = 0;
  char tmp1[100] = "";
  char tmp2[100] = "";
  scanf("%d", &len1);
  scanf("%s", tmp1);
  scanf("%d", &len2);
  scanf("%s", tmp2);
  strcat(tmp1, tmp2);
  char *str = (char*) calloc(len1+len2+1, sizeof(char));
  str = tmp1;
  puts(str);
    char str1[100] = "";
    char str2[100] = "";
    for (int i = 0 ; i< len1; i++){
        str1[i] = str[i];
    }
    for (int i = 0 ; i< len2; i++){
        str2[i] = str[i+len1];
    }
    int cnt = 0;
  int *pnt = &cnt;
  for(int i = 0 ; i< len2; i++){
    for(int j = 0 ; j < len1; j++){
      if(str2[i] == str1[j]){
        str1[j] =254;
        *pnt +=1;
                break;
      }
    }
  }
  if(*pnt != len2){
    printf("not subset\n");
  } else {
    printf("subset\n");
  }
}
