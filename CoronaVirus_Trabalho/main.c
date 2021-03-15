/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: cenas
 *
 * Created on 2 de abril de 2020, 13:10
 */


#include "simulacao.h"

/*
 * 
 */
int main(int argc, char** argv) {
    int tamLocais, nIter = 0;
    Local * locais = NULL;
    PessoaList * head = NULL;
    char locaisPath[30], pessoasPath[30];
    BackUp * backup = NULL;
    SimulationIter * new = NULL;
    initRandom(); // esta função só deve ser chamada uma vez


    printf("Nome do ficheiro para os Locais:\n- ");
    scanf("%s", locaisPath);
    //strcpy(locaisPath,locaisPath);

    tamLocais = readLocal(&locais, locaisPath);

    printf("Nome do ficheiro para os Pessoas:\n- ");
    scanf("%s", pessoasPath);
    head = readPessoas(pessoasPath);


    pessoasEntramLocal(head, locais, tamLocais);

    int op;
    do {

        op = MainMenu();
        switch (op) {
            case OPT_FORWARD_ITERATION:
                new = saveIteration(head, locais, tamLocais, nIter);
                backup = BackUpIteration(new, backup);

                simulation(head, locais, tamLocais);
                nIter++;
                printf("Iteracao avancada \n");
                break;
            case OPT_GET_STATUS:
                estatisticas(head, locais, tamLocais, nIter);
                break;
            case OPT_ADD_SICK:
                if (adicionaDoente(head, locais, tamLocais) == true) {
                    printf("Doente adicionado com sucesso \n ");
                } else {
                    printf("Nao foi adicionado o doente\n");
                }
                break;
            case OPT_TRANSFER_PEOPLE:
                if (transferPessoas(head, locais, tamLocais) == true) {
                    printf("Transferencia efetuada com sucesso\n");
                } else {
                    printf("Nao foi possivel tranferir pessoas\n");
                }
                break;
            case OPT_RETURN_ITERATIONS:
                backup = returnNIter(backup, head, locais, tamLocais, &nIter);
                locais = backup->iter->locais;
                head = backup->iter->pessoas;
                nIter = backup->iter->iter;
                break;
            case OPT_END_SIMULATION:
                GuardaPop(head);
                if (endSimulation(backup,head, locais, tamLocais, nIter) == true) {
                    printf("Ficherio completo\n");
                    exit(EXIT_SUCCESS);
                }
                break;
        }
    } while (op != OPT_END_SIMULATION);
    return (EXIT_SUCCESS);
}

