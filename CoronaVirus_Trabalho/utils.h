// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//typedef enum {true, false} bool;

#define OPT_FORWARD_ITERATION 10
#define OPT_GET_STATUS 11
#define OPT_ADD_SICK 12
#define OPT_TRANSFER_PEOPLE 13
#define OPT_RETURN_ITERATIONS 14
#define OPT_END_SIMULATION 15
//#define OPT_EXIT 16

// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

int MainMenu();
#endif /* UTILS_H */

