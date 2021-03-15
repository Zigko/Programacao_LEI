// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020

#include "utils.h"


void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

int MainMenu(){
    char str[20];
    int op;
    int res = 0;
    do{
        printf("\n------ MENU PRINCIPAL ------ \n");
        printf("1 -Avancar 1 iteracao\n");
        printf("2 -Apresentar Estatistica\n");
        printf("3 -Adicionar Doente\n");
        printf("4 -Transferir Pessoas\n");
        printf("5 -Retornar Iteracoes\n");
        printf("6 -Terminar Simulacao\n");
        printf("- Opcao: ");
        
        res = scanf("%s",str);
        op = atoi(str);
    }while(res != 1 || op < 1 || op > 6);
    
    return (op+9);
}
