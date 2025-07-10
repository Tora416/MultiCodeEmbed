char map[64];
int pos = 0;
int goal = 0;

void tail_func(char tmp){
  if(tmp == 'U'){
    if(pos>7 && map[pos-8] != 'W'){
      tail[tailpos] = pos;
      if(tailpos>4){
        map[tail[tailpos-5]] = 'E';
      }
      tailpos++;
      pos-=8;
    }
  } else if (tmp == 'D'){
    if(pos<55 && map[pos+8] != 'W'){
      tail[tailpos] = pos;
      if(tailpos>4){
        map[tail[tailpos-5]] = 'E';
      }
      tailpos++;
      pos+=8;
    }
  } else if (tmp == 'R'){
    if(pos%8!=7 && map[pos+1] != 'W'){
      tail[tailpos] = pos;
      if(tailpos>4){
        map[tail[tailpos-5]] = 'E';
      }
      tailpos++;
      pos++;
    }
  } else if (tmp == 'L'){
    if(pos%8!=0 && map[pos-1] != 'W'){
      tail[tailpos] = pos;
      if(tailpos>4){
        map[tail[tailpos-5]] = 'E';
      }
      tailpos++;
      pos--;
    }
  }
}

void check_stuck(){
  if(pos<8 && map[pos+1] == 'W' && map[pos-1] == 'W' && map[pos+8] == 'W'){
    exit(0);
  } else if(pos>55 && map[pos+1] == 'W' && map[pos-1] == 'W' && map[pos-8] == 'W') {
    exit(0);
  } else if(pos%8==7 && map[pos-8] == 'W' && map[pos-1] == 'W' && map[pos+8] == 'W') {
    exit(0);
  } else if(pos%8==0 && map[pos-8] == 'W' && map[pos+1] == 'W' && map[pos+8] == 'W') {
    exit(0);
  } else if(pos<8 && pos%8==7 && map[pos-1] == 'W' && map[pos+8] == 'W'){
    exit(0);
  } else if(pos%8==7 && pos>55 && map[pos-8] == 'W' && map[pos-1] == 'W'){
    exit(0);
  } else if(pos>55 && pos%8==0 && map[pos-8] == 'W' && map[pos+1] == 'W'){
    exit(0);
  } else if(pos%8==0 && pos<8 && map[pos+1] == 'W' && map[pos+8] == 'W'){
    exit(0);
  } else if(map[pos-8] == 'W' && map[pos+8] == 'W' && map[pos+1] == 'W' && map[pos-1] == 'W'){
    exit(0);
  }
}

void main(){
  
  int x, y, xg, yg;
  scanf("%d %d", &x, &y);
    scanf("%d %d", &xg, &yg);
  pos = x*8+y;
  goal = xg*8+yg;

  
  for(int i = 0 ; i< 136; i++){
        char ch = getchar();
    if(ch != ' '){
      map[(i-i/17)/2] = ch;
    }
    }

  
  map[goal] = 'G';

  
  int turn = 0;
    scanf("%d", &turn);

  
    int cnt = 0;
    char *cmd = (char*) calloc(turn, sizeof(char));
    while(cnt < turn){
    char input[7] = "";
    gets(input);
    if(strncmp(input, "WIND", 4) == 0){
            cmd[cnt-1]='\0';
      strcat(cmd, &input[5]);
    } else if(strncmp(input, "CMD", 3) == 0){
      cnt+=1;
      strcat(cmd, &input[4]);
    }
  }

  
  map[pos] = 'P';
  for(int i=0; i<64; i++) {
        printf("%c ", map[i]);
    if(i%8==7){
      printf("\n");
    }
  }
  printf("\n");

  
  for(int k = 0; k<turn; k++){
    
    map[pos] = 'W';

    
    check_stuck();

    
    tail_func(cmd[k]);


    
    map[pos] = 'P';
    for(int i=0; i<64; i++) {
        printf("%c ", map[i]);
      if(i%8==7){
        printf("\n");
      }
    }
    printf("\n");

    
    if(pos == goal){
            exit(0);
    }

  
  }
  free(cmd);

}
