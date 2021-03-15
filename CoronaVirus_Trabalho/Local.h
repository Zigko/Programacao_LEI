/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Local.h
 * Author: cenas
 *
 * Created on 2 de abril de 2020, 16:30
 */

#ifndef LOCAL_H
#define LOCAL_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif
#include "utils.h"
#define MAX_CONECTIONS 3
typedef struct local Local;
struct local{
    int id;
    int capacidade;
    int conections[MAX_CONECTIONS];
};

int readLocal(Local **locais,char *file);
void printAllLocais(Local * locais,int tam);

#endif /* LOCAL_H */

