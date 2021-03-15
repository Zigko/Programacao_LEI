/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "simulacao.h"

void taxaDisseminacao(PessoaList * head, Local *locais, int tamLocais) {
    PessoaList * iter;
    int numToInfect;
    int sameLocal;
    int infected;

    for (int i = 0; i < tamLocais; i++) {
        int id = locais[i].id;
        sameLocal = 0, infected = 0;
        iter = head;
        numToInfect = 0;
        while (iter != NULL) {
            if (iter->pessoa.local->id == id) {
                if (iter->pessoa.estado == 'D') {
                    infected++;
                }
                sameLocal++;
            }
            iter = iter->next;
        }
        if (infected > 0) {
            numToInfect = infected * (sameLocal * TAXA_DISSEMINACAO);
            //printf("Numero a infetar: %d || pessoas no local %d: %d \n",numToInfect,id,sameLocal);
        }
        if (numToInfect >= 1) {
            for (int j = 0; i < numToInfect; i++) {
                int random = intUniformRnd(0, sameLocal);
                int count = 0;
                iter = head;
                while (iter != NULL) {
                    if (iter->pessoa.local->id == id) {
                        if (random == count) {
                            if (iter->pessoa.estado != 'I') {
                                if (iter->pessoa.estado != 'D') {
                                    iter->pessoa.estado = 'D';
                                    iter->pessoa.dias = 1;
                                }
                            }
                        }
                        count++;
                    }
                    iter = iter->next;
                }
            }
        }
    }

}

bool probRecuperacao(Pessoa pessoa) {
    if (pessoa.estado != 'S' || pessoa.estado != 'I') {
        float x = PROB_RECUPERACAO / pessoa.idade;
        if (probEvento(x) == 1) {
            pessoa.estado = 'S';
            pessoa.dias = 0;
            return (true);
        }
    }

    return (false);
}

bool duracaoMaxInfecao(Pessoa pessoa) {
    int num;
    if (pessoa.dias != 0 || pessoa.estado == 'D') {
        num = (pessoa.idade) / 10;
        num = num + MAX_DIAS_INFETADO;

        if (pessoa.dias >= num) {
            //printf("%s nao devia passar de: %d",pessoa.nome,num);
            pessoa.dias = 0;
            pessoa.estado = 'S';
            return (true);
        }
    }
    return (false);
}

void taxaImunidade(Pessoa pessoa) {
    if (probEvento(TAXA_IMUNIDADE) == 1) {
        pessoa.estado = 'I';
    }
}

void simulation(PessoaList * head, Local *locais, int tamLocais) {
    PessoaList * iter = head;
    taxaDisseminacao(head, locais, tamLocais);
    while (iter != NULL) {
        if (duracaoMaxInfecao(iter->pessoa) == true) {
            iter->pessoa.dias = 0;
            iter->pessoa.estado = 'S';
            taxaImunidade(iter->pessoa);
        }
        if (probRecuperacao(iter->pessoa) == true) {
            iter->pessoa.dias = 0;
            iter->pessoa.estado = 'S';
            taxaImunidade(iter->pessoa);
        }
        if (iter->pessoa.estado == 'D') {
            iter->pessoa.dias++;
        }
        iter = iter->next;
    }
}

void estatisticas(PessoaList * head, Local *locais, int tamLocais, int nIter) {
    int nInfetados = 0, nSaudaveis = 0, nImunes = 0;
    PessoaList * iter = head;
    int totalPessoas = numPessoas(head);
    int sameLocal = 0;
    int sameLocalInfected = 0;

    //printAllLocais(locais,tamLocais);
    //printf("\n");
    //printAllPessoas(head);

    printf("********* Distribuicao *********\n");
    for (int i = 0; i < tamLocais; i++) {
        printf("Sala %d (capacidade -> %d):\n", locais[i].id, locais[i].capacidade);
        iter = head;
        sameLocal = 0;
        sameLocalInfected = 0;
        while (iter != NULL) {
            if (locais[i].id == iter->pessoa.local->id) {
                sameLocal++;
                if (iter->pessoa.estado == 'D') {
                    printf("Nome: %s || Idade: %d || Estado: %c || Dias infetado: %d;\n", iter->pessoa.nome, iter->pessoa.idade, iter->pessoa.estado, iter->pessoa.dias);
                    nInfetados++;
                    sameLocalInfected++;
                }
                if (iter->pessoa.estado == 'S') {
                    printf("Nome: %s || Idade: %d || Estado: %c;\n", iter->pessoa.nome, iter->pessoa.idade, iter->pessoa.estado);
                    nSaudaveis++;
                }
                if (iter->pessoa.estado == 'I') {
                    printf("Nome: %s || Idade: %d || Estado: %c;\n", iter->pessoa.nome, iter->pessoa.idade, iter->pessoa.estado);
                    nImunes++;
                }
            }
            iter = iter->next;
        }
        printf("Percentagem de infetados na sala %d : %.2f %%",locais[i].id,((float) sameLocalInfected/sameLocal)*100);
        printf("\n");
    }

    printf("\n");
    printf("Numero de Infetados: %d (%f %c)\n", nInfetados, ((float) nInfetados / totalPessoas)*100, '%');
    printf("Numero de Saudaveis: %d (%f %c)\n", nSaudaveis, ((float) nSaudaveis / totalPessoas)*100, '%');
    printf("Numero de Imunes: %d (%f %c)\n", nImunes, ((float) nImunes / totalPessoas)*100, '%');
    printf("Numero de Itereacoes: %d\n", nIter);
}

bool endSimulation(BackUp * backup, PessoaList * head, Local * locais, int tamLocais, int nIter) {
    char outPath[30];
    FILE * file;
    PessoaList * iter = head;
    int nInfetados = 0, nSaudaveis = 0, nImunes = 0;
    int totalPessoas = numPessoas(head);


    printf("Nome do ficheiro para guardar o Relatorio final da simulacao:\n-");
    scanf("%s", outPath);

    file = fopen(outPath, "w");
    if (file == NULL) {
        printf("Erro a abrir o ficheiro\n");
        exit(1);
    }
    fprintf(file, "Distribuicao:\n");
    for (int i = 0; i < tamLocais; i++) {
        fprintf(file, "Sala %d:\n", locais[i].id);
        iter = head;
        while (iter != NULL) {
            if (locais[i].id == iter->pessoa.local->id) {
                if (iter->pessoa.estado == 'D') {
                    fprintf(file, "Nome: %s || Idade: %d || Estado: %c || Dias infetado: %d;\n", iter->pessoa.nome, iter->pessoa.idade, iter->pessoa.estado, iter->pessoa.dias);
                    nInfetados++;
                }
                if (iter->pessoa.estado == 'S') {
                    fprintf(file, "Nome: %s || Idade: %d || Estado: %c;\n", iter->pessoa.nome, iter->pessoa.idade, iter->pessoa.estado);
                    nSaudaveis++;
                }
                if (iter->pessoa.estado == 'I') {
                    fprintf(file, "Nome: %s || Idade: %d || Estado: %c;\n", iter->pessoa.nome, iter->pessoa.idade, iter->pessoa.estado);
                    nImunes++;
                }
            }
            iter = iter->next;
        }
    }

    fprintf(file, "Estatisticas:\n");
    fprintf(file, "Numero de Infetados: %d (%f %c)\n", nInfetados, ((float) nInfetados / totalPessoas)*100, '%');
    fprintf(file, "Numero de Saudaveis: %d (%f %c)\n", nSaudaveis, ((float) nSaudaveis / totalPessoas)*100, '%');
    fprintf(file, "Numero de Imunes: %d (%f %c)\n", nImunes, ((float) nImunes / totalPessoas)*100, '%');
    fprintf(file, "Numero de Itereacoes: %d\n", nIter);

    fclose(file);


    free(locais);
    freePessoas(head);

    BackUp * curr = backup;
    int numBackups = 0;
    while (curr != NULL) {
        numBackups++;
        curr = curr->next;
    }
    if (numBackups == 0) {
        free(curr);
    } else {
        BackUp * anterior = NULL;
        while (curr != NULL) {
            anterior = curr;
            curr = curr->next;

            free(anterior->iter->locais);
            freePessoas(anterior->iter->pessoas);
            free(anterior->iter);
            free(anterior);
        }
        free(curr);
    }
    printf("memoria libertada\n");
    return (true);
}

SimulationIter * saveIteration(PessoaList * head, Local *locais, int tamLocais, int nIter) {
    SimulationIter * save = NULL;
    PessoaList * iter = head;
    PessoaList * newHead = NULL;
    PessoaList * tail = NULL;
    //PessoaList * temp = NULL;
    Local * newLocais = NULL;
    Pessoa aux;

    newLocais = malloc(sizeof (Local) * tamLocais);
    if (newLocais == NULL) {
        printf("ERRO A ALOCAR MEMORIA\n");
        exit(1);
    }
    memcpy(newLocais, locais, sizeof (Local) * tamLocais);
    //newLocais = locais;
    while (iter != NULL) {
        //primeria pessoa
        if (newHead == NULL) {
            newHead = (PessoaList *) malloc(sizeof (PessoaList));
            if (newHead == NULL) {
                printf("ERRO A ALOCAR MEMORIA\n");
                exit(1);
            }
            strcpy(aux.nome, iter->pessoa.nome);
            aux.idade = iter->pessoa.idade;
            aux.estado = iter->pessoa.estado;
            aux.dias = iter->pessoa.dias;
            for (int i = 0; i < tamLocais; i++) {
                if (iter->pessoa.local->id == newLocais[i].id) {
                    aux.local = &newLocais[i];
                }
            }
            newHead->pessoa = aux;
            newHead->next = NULL;
            tail = newHead;
        } else { //pessoas seguintes
            tail->next = (PessoaList *) malloc(sizeof (PessoaList));
            tail = tail->next;
            strcpy(aux.nome, iter->pessoa.nome);
            aux.idade = iter->pessoa.idade;
            aux.estado = iter->pessoa.estado;
            aux.dias = iter->pessoa.dias;
            for (int i = 0; i < tamLocais; i++) {
                if (iter->pessoa.local->id == newLocais[i].id) {
                    aux.local = &newLocais[i];
                }
            }
            tail->pessoa = aux;
            tail->next = NULL;
        }
        iter = iter->next;
    }
    save = malloc(sizeof (SimulationIter));
    if (save == NULL) {
        printf("ERRO A ALOCAR MEMORIA\n");
        exit(1);
    }
    //printAllPessoas(newHead);
    save->iter = nIter;
    save->locais = newLocais;
    save->pessoas = newHead;
    return (save);
}

BackUp * BackUpIteration(SimulationIter * save, BackUp * backup) {

    BackUp * newBackup;
    newBackup = malloc(sizeof (BackUp));
    if (newBackup == NULL) {
        printf("ERRO A ALOCAR MEMORIA\n");
        exit(1);
    }

    // ADICIONA A NOVA ITERAÇAO AO BACKUP E PASSA A SER O PREMEIRO MEMBRO DA LISTA
    newBackup->iter = save;
    newBackup->next = backup;

    BackUp * iterador = newBackup;
    BackUp * anterior;
    int count = 0;

    while (iterador != NULL) {
        count++;
        // SE A LISTA FOR MAIOR QUE 3 O ULTIMO MEMBRO É RETIRADO DA MEMORIA
        if (count > MAX_BACKUP) {

            free(iterador->iter->locais);
            freePessoas(iterador->iter->pessoas);
            free(iterador->iter);
            free(iterador);
            anterior->next = NULL;
            break;

        }
        anterior = iterador;
        iterador = iterador->next;
    }

    return (newBackup);
}

BackUp * returnNIter(BackUp * backup, PessoaList * head, Local * locais, int tamLocais, int * nIter) {
    int num;
    int count = 0;

    BackUp * iterador = backup;
    while (iterador != NULL) {
        count++;
        iterador = iterador->next;
    }
    printf("Tem %d iteracoes guardadas\n", count);
    bool x;
    do {
        x = false;
        printf("Quantas iteracoes deseja voltar a traz? (MAX: %d)\n- ", count);
        scanf("%d", &num);
        if (num > MAX_BACKUP || num <= 0) {
            printf("Intrudiza um numero valido!\n");
            x = true;
        }
        if (num > count) {
            printf("Nao ha tantas iteracoes guardadas \n");
            x = true;
        }
        if (!x) {
            break;
        }
    } while (true);

    iterador = backup;
    BackUp * anterior = NULL;

    for (int i = 0; i < num - 1; i++) {
        anterior = iterador;
        iterador = iterador->next;

        //REMOVE A ITERAÇOES MAIS RECENTES ATE À PRETENDIDA
        free(anterior->iter->locais);
        freePessoas(anterior->iter->pessoas);
        free(anterior->iter);
        free(anterior);

    }

    printf("Voltou para a iteracao : %d", iterador->iter->iter);

    return (iterador);
}
void GuardaPop(PessoaList * head){
    PessoaList * iter = head;
    
    char *  outPath = "PopulacaoFinal.txt";
    FILE * file;
    printf("Pessoas vao ser armazenadas em %s \n",outPath);

    file = fopen(outPath, "w");
    if (file == NULL) {
        printf("Erro a abrir o ficheiro\n");
        exit(1);
    }
    while(iter !=NULL){
        if(iter->pessoa.estado != 'D'){
            fprintf(file,"%s  %d  %c",iter->pessoa.nome,iter->pessoa.idade,iter->pessoa.estado);
        }else{
            fprintf(file,"%s  %d  %c  %d",iter->pessoa.nome,iter->pessoa.idade,iter->pessoa.estado,iter->pessoa.dias);
        }
        iter = iter->next;
    }
    
    
    fclose(file);
}