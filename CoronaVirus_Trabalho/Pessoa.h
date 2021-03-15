/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pessoa.h
 * Author: cenas
 *
 * Created on 2 de abril de 2020, 19:36
 */

#ifndef PESSOA_H
#define PESSOA_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif
#include "Local.h"

#define NAME_LENGHT 100

typedef struct pessoa  Pessoa;
struct pessoa {
    char nome[NAME_LENGHT];
    int idade;
    char estado;
    int dias;
    Local *local;
};
typedef struct pessoaList PessoaList;
struct pessoaList{
    Pessoa pessoa;
    struct pessoaList *next;
};

PessoaList * readPessoas(char *filePath);
void printAllPessoas(PessoaList * head);
void pessoasEntramLocal(PessoaList * head,Local *locais,int tamLocais);
bool adicionaDoente(PessoaList * head,Local *locais,int tamLocais);
bool transferPessoas(PessoaList * head,Local *locais,int tamLocais);
int numPessoas(PessoaList * head);
void freePessoas(PessoaList * head);

#endif /* PESSOA_H */

