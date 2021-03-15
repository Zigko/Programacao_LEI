/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simulacao.h
 * Author: cenas
 *
 * Created on 17 de abril de 2020, 12:03
 */
#include "Pessoa.h"
#ifndef SIMULACAO_H
#define SIMULACAO_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#define TAXA_DISSEMINACAO 0.3
#define PROB_RECUPERACAO 1
#define MAX_DIAS_INFETADO 5
#define TAXA_IMUNIDADE 0.2  
#define MAX_BACKUP 3

   
//typedef struct simulationIter SimulationIter;
typedef struct simulationIter{
    PessoaList * pessoas;
    Local * locais;
    int iter;
}SimulationIter;
typedef struct backUp{
    //SimulationIter * backupIter[MAX_BACKUP];
    SimulationIter * iter;
    struct backUp * next;
}BackUp; 

void taxaDisseminacao(PessoaList * head,Local *locais,int tamLocais);
bool probRecuperacao(Pessoa pessoa);
bool duracaoMaxInfecao(Pessoa pessoa);
void taxaImunidade(Pessoa pessoa);
void simulation(PessoaList * head,Local *locais,int tamLocais);
void estatisticas(PessoaList * head,Local *locais,int tamLocais,int nInter);
bool endSimulation(BackUp * backup,PessoaList * head, Local * locais, int tamLocais, int nIter);
SimulationIter * saveIteration(PessoaList * head,Local *locais,int tamLocais,int nIter);
BackUp * BackUpIteration(SimulationIter * save, BackUp * backup);
BackUp * returnNIter(BackUp * backup, PessoaList * head, Local * locais,int tamLocais, int * nIter);
void GuardaPop(PessoaList * head);
#endif /* SIMULACAO_H */

