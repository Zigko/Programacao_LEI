/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Local.h"


int readLocal(Local **locais,char *file){
    FILE *ptr;
    int tam;

    ptr = fopen(file,"rb");
    if(ptr == NULL ){
        printf("erro a abrir ficheiro\n");
        exit(1);
    }
    
    
    Local *tmp = NULL;
    //tmp = realloc(locais, sizeof(Local)*i);
    
    int i=0;
    while(1){
        tmp = realloc(tmp, sizeof(Local)*(i+1));
        if(fread(&tmp[i],sizeof(Local),1,ptr)!= 0){
            i++;
        }else{
            break;
        }
    }
    tam = i;
    for(int j = 0; j < tam; j++ ){
        int id = tmp[j].id;
        int confirmed = 0;
        int n_conections = 0;
        for(int k = 0 ; k < MAX_CONECTIONS ; k++){
            if(tmp[j].conections[k]!= -1){
                //printf("Local %d com conecao para %d\n",locais[j].id,locais[j].conections[k]);
                n_conections++;
                for(int m = 0; m < tam; m++){
                    if(tmp[j].conections[k] == tmp[m].id){
                        for(int l = 0; l<MAX_CONECTIONS;l++){
                            if(tmp[m].conections[l]!= -1){
                                if(tmp[m].conections[l] == id){
                                    //printf("Local com id %d esta ligado ao local com id %d \n",id,locais[m].id);
                                    confirmed ++;
                                    //printf("Local %d foram confirmados: %d \n\n",id,confirmed);
                                }
                            }
                        }
                    }
                }
                if(tmp[j].conections[k] == id){
                    printf("Sala conectada com ela mesma\n");
                    exit(1);
                }
            }
        }
        if(tmp[j].capacidade <= 0 ){
            printf("Capacidade tem que ser maior que 0\n");
            exit(1);
        }
        if(tmp[j].id <= 0 ){
            printf("ID tem que ser posito\n");
            exit(1);
        }
        //printf("Local %d tem %d conecoes %d e foram confirmados: %d \n\n",id,n_conections,confirmed);
        if(n_conections != confirmed){
            printf("AS conecoes entre os locias nao estao corretas\n");
            exit(1);
        }
    }
    if (tmp != NULL) {
      *locais = tmp;
    } else {
        printf("\nErro a realocar memoria\n");
        exit(1);
    }
    
    
    fclose(ptr);
    return(tam);
}

void printAllLocais(Local * locais, int tam){
    for(int i = 0;i < tam; i++ ){
        printf("\n Id: %d \n",locais[i].id);
        printf(" Capacidade: %d \n",locais[i].capacidade);
        for(int j = 0;j < MAX_CONECTIONS;j++){
            if(locais[i].conections[j] != -1){
                printf(" Conectado a Sala: %d \n",locais[i].conections[j]);
            }
        }
    } 
}