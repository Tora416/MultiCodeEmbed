#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    
    char name[80];
    int lotMax; 
    int contLot;
    int tipEnt;
    int contPag;
    int contEsco;
    int contIntMax;
    int contInt;
    int contMeiaMax;
    int contMeia;
    float priceMeia;
    float pricePag;
    float troco;
    float lucro;
    float price;
    
    
    
    printf("Digite o nome do evento (utilize de ( / ) para espaco):\n");
    scanf("%s", &name);
    
    do{
        
    printf("\nDigite a capacidade maxima de pessoas(somente multiplos de 5):\n");
    scanf("%i" ,&lotMax);
    
    }while (lotMax%5!=0 || lotMax <= 0);
    
    do{
    
    printf("\nDigite o preco do ingresso:\n");
    scanf("%f" ,&price);
    
    }while (price<0);
    
    
    
    
    
    
    
    priceMeia=price/2;
    contLot=lotMax;
    lucro=0;
    contIntMax=lotMax*0.6;
    contInt=contIntMax;
    contMeiaMax=lotMax*0.4;
    contMeia=contMeiaMax;
    
    printf("\n\nEvento: %s\n" ,name);
    
    do{
        
        do{
            printf("\nDigite 1 para comprar um ingresso inteira.\nDigite 2 para comprar um ingresso meia.\n");
            scanf("%i" ,&tipEnt);
            
            switch(tipEnt){
            
                case 1:
                                    
                                                        
                    contEsco=0;
                                            
                    if(contInt>0){
                        
                        contLot--;
                        contInt--;
                        do{
                        
                            printf("\nVoce deve pagar %f.\n" ,price);
                            printf("Digite o preco pago:\n");
                            scanf("%f" ,&pricePag);
                            
                            if(pricePag<price){
                            
                                contPag=0;
                                printf("\nVoce nao pagou o suficiente, pague novamente.\n");
                                                    
                            }
                            
                            if(pricePag==price){
                                
                                contPag=1;
                                printf("\nVoce efetuou seu pagamento, Obrigado e volte sempre\n");
                                lucro=lucro+price;
                                                    
                            }
                            if(pricePag>price){
                                
                                contPag=1;
                                troco=pricePag-price;
                                printf("\nVoce recebe de troco %f.\n\n" ,troco);
                                lucro=lucro+price;
                                
                            }
                            
                        }while(contPag==0);
                        
                    
                    }
                    else{
                        
                        printf("\nAcabou os ingressos do tipo inteiro.\n");
                        
                    }
                    
                    break;
                case 2:
                    
                    contEsco=0;
                    
                    if(contMeia>0){
                        
                        contLot--;
                        contMeia--;
                        do{                         
                            printf("\nVoce deve pagar %f.\n" ,priceMeia);
                            printf("Digite o preco pago:\n");
                            scanf("%f" ,&pricePag);
                        
                            if(pricePag<priceMeia){
                            
                                contPag=0;
                                printf("\nVoce nao pagou o suficiente, pague novamente.\n\n");
                            
                            }
                            
                            if(pricePag==priceMeia){
                                
                                contPag=1;
                                printf("\nVoce efetuou seu pagamento, Obrigado e volte sempre\n");
                                lucro=lucro+priceMeia;
                                                    
                            }
                            if(pricePag>priceMeia){
                                
                                contPag=1;
                                troco=pricePag-priceMeia;
                                printf("\nVoce recebe de troco %f.\n\n" ,troco);
                                lucro=lucro+priceMeia;
                                
                            }
                            
                        }while(contPag==0);
                        
                    }
                    else{
                        
                        printf("\nAcabou os ingressos do tipo meia.\n");
                        
                    }
                    
                    break;
                    
                default:
                        
                    contEsco=1;
                    printf("\nDigite novamente sua escolha.\n\n");
                        
                    break;
                                    
            }
            
        }while(contEsco==1);
        
        printf("\n\nEvento: %s\n" ,name);
        printf("\nAinda se tem %i ingressos do tipo inteiro.\n" ,contInt);
        printf("Ainda se tem %i ingressos do tipo meia.\n" ,contMeia);
        printf("Voce tem um lucro de %f.\n\n" ,lucro);
        
    }while (contLot>0);
    
    printf("\n\nEvento: %s\n" ,name);   
    printf("\nacabou os ingressos.\n");
    printf("voce teve um lucro total de %f.\n" ,lucro);
    
    
    
    return 0;
}
