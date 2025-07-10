#include <stdio.h>


main(){
  int c, aux, cont;
  int abcd[28];
  cont  = aux = 0;
  for(int i = 0; i < 28; i++)
    abcd[i] = 0;
  
  while((c = getchar()) != EOF){
    switch(c){
    case 32:
      break;
    case 9:
      break;
    case 10:
      break;
    case 65:
      abcd[0]++;
      break;
    case 66:
      abcd[1]++;
      break;
    case 67:
      abcd[2]++;
      break;
    case 68:
      abcd[3]++;
      break;
    case 69:
      abcd[4]++;
      break;
    case 70:
      abcd[5]++;
      break;
    case 71:
      abcd[6]++;
      break;
    case 72:
      abcd[7]++;
      break;
    case 73:
      abcd[8]++;
      break;
    case 74:
      abcd[9]++;
      break;
    case 75:
      abcd[10]++;
      break;
    case 76:
      abcd[11]++;
      break;
    case 77:
      abcd[12]++;
      break;
    case 78:
      abcd[13]++;
      break;
    case 165:
      abcd[14]++;
      break;
    case 79:
      abcd[15]++;
      break;
    case 80:
      abcd[16]++;
      break;
    case 81:
      abcd[17]++;
      break;
    case 82:
      abcd[18]++;
      break;
    case 83:
      abcd[19]++;
      break;
    case 84:
      abcd[20]++;
      break;
    case 85:
      abcd[21]++;
      break;
    case 86:
      abcd[22]++;
      break;
    case 87:
      abcd[23]++;
      break;
    case 88:
      abcd[24]++;
      break;
    case 89:
      abcd[25]++;
      break;
    case 90:
      abcd[26]++;
      break;
      
    case 97:
      abcd[0]++;
      break;
    case 98:
      abcd[1]++;
      break;
    case 99:
      abcd[2]++;
      break;
    case 100:
      abcd[3]++;
      break;
    case 101:
      abcd[4]++;
      break;
    case 102:
      abcd[5]++;
      break;
    case 103:
      abcd[6]++;
      break;
    case 104:
      abcd[7]++;
      break;
    case 105:
      abcd[8]++;
      break;
    case 106:
      abcd[9]++;
      break;
    case 107:
      abcd[10]++;
      break;
    case 108:
      abcd[11]++;
      break;
    case 109:
      abcd[12]++;
      break;
    case 110:
      abcd[13]++;
      break;
    case 164:
      abcd[14]++;
      break;
    case 111:
      abcd[15]++;
      break;
    case 112:
      abcd[16]++;
      break;
    case 113:
      abcd[17]++;
      break;
    case 114:
      abcd[18]++;
      break;
    case 115:
      abcd[19]++;
      break;
    case 116:
      abcd[20]++;
      break;
    case 117:
      abcd[21]++;
      break;
    case 118:
      abcd[22]++;
      break;
    case 119:
      abcd[23]++;
      break;
    case 120:
      abcd[24]++;
      break;
    case 121:
      abcd[25]++;
      break;
    case 122:
      abcd[26]++;
      break;
    default:
      abcd[27]++;
      break;
    }      
  }
  int r = 97;
  for(int i = 0; i < 28; i++){
    if(i < 27 ){
      if(i != 14)
    printf(" %2c :", r);
      else{
    printf("  ñ :");
    r= r-1;
      }
      r++;
    }
    else
      printf(" Other characters :");
    
    for(int l = 0; l < abcd[i]; l++)
      printf( "-");    
    printf("\n");
  }
  
}
