



#include <stdio.h>
#include <stdlib.h>

#define PATH "/dev/chardev_leds"

int main(int argc, char * argv[]){
    
    if (argc!=2){
        fprintf(stderr, "Uso: %s cont_binario/rotativo (Elegir uno de los dos modos)\n", argv[0]);
        exit(1);
    }

    
    FILE * file = fopen(PATH, "r+");
    if (file == NULL){
        printf("No se puede abrir el archivo\n");
        exit(1);
    }
    fclose(file);

    
    if(strcmp(argv[1], "cont_binario") == 0){
        cont_binario();
    }

    
    else if(strcmp(argv[1], "rotativo") == 0){
        rotativo();
    }
    
    else{
        fprintf(stderr, "Modo: %s no valido\n", argv[1]);
        exit(1);
    }

    return 0;
}


void rotativo(){

    
    char  leds[] = "0";

    
    FILE * file;

    
    int i = 1;
    while(1){
        file = fopen(PATH, "r+");

        
        sprintf(leds, "%d", i);

        fwrite(leds, sizeof(char), strlen(leds), file);

        printf("He encendido el led %s\n", leds);
        fclose(file);

        sleep(1);

        i = (i%3) + 1;
    }
}


void cont_binario(){

    
    char leds[] = "000";

    
    FILE * file;

    int i = 0;
    
    while(1){
        int num = i;
        file = fopen(PATH, "r+");

        
        if(num >= 4){
            leds[0] = '1';
            num = num -4;
        }

        
        if (num >= 2){
            leds[1] = '2';
            num = num -2;
        }

        
        if(num >= 1){
            leds[2] = '3';
        }

        
        fwrite(leds, sizeof(char), strlen(leds), file);

        printf("He encendido los leds %s\n", leds);

        fclose(file);

        
        sleep(1);

        i = (i+1)%8;

        leds[0] = '0';
        leds[1] = '0';
        leds[2] = '0';
    }
}