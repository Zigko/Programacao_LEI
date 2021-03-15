/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Pessoa.h"

PessoaList * readPessoas(char *filePath) {
    FILE *file;
    int status;
    char nome[NAME_LENGHT];
    int idade, dias_infetado;
    char estado;


    file = fopen(filePath, "r");
    if (file == NULL) {
        printf("\n erro a abrir ficheiro");
        exit(1);
    }
    int c = fgetc(file);
    if (c == EOF) {
        printf("Ficheiro Vazio\n");
        exit(1);
    }

    PessoaList *temp;
    PessoaList *iter, *compara, *anterior = NULL;
    Pessoa aux;
    temp = (PessoaList *) malloc(sizeof (PessoaList));
    if (temp == NULL) {
        printf("ERRO A ALOCAR MEMORIA\n");
        exit(1);
    }
    iter = temp;
    //compara = temp;
    int i = 0;
    while (fscanf(file, "%s %d %c", nome, &idade, &estado) == 3) {
        compara = temp;
        if (i == 0) {
            strcpy(aux.nome, nome);
            if (idade <= 0) {
                printf("Idade tem que ser maior que 0 \n");
                exit(1);
            } else {
                aux.idade = idade;
            }
            if (estado != 'S' && estado != 'I' && estado != 'D') {
                printf("O estado tem que ser S ou I ou D \n ");
                exit(1);
            } else {
                aux.estado = estado;
                if (estado == 'D') {
                    fscanf(file, " %d \n", &dias_infetado);
                    if (dias_infetado < 0) {
                        printf("os dias infetados tem que ser positivos\n");
                        exit(1);
                    } else {
                        aux.dias = dias_infetado;
                    }
                } else {
                    fscanf(file, " \n");
                    aux.dias = 0;
                }
            }
            aux.local = NULL;
        } else {
            while (compara != NULL) {
                if (strcmp(compara->pessoa.nome, nome) == 0) {
                    printf("Ja existe pessoa com nome %s \n", nome);
                    exit(1);
                } else {
                    strcpy(aux.nome, nome);
                    if (idade < 0) {
                        printf("Idade tem que ser maior que 0 \n");
                        exit(1);
                    } else {
                        aux.idade = idade;
                    }
                    if (estado != 'S' && estado != 'I' && estado != 'D') {
                        printf("O estado tem que ser S ou I ou D \n ");
                        exit(1);
                    } else {
                        aux.estado = estado;
                        if (estado == 'D') {
                            fscanf(file, " %d \n", &dias_infetado);
                            if (dias_infetado < 0) {
                                printf("os dias infetados tem que ser positivos ou 0");
                                exit(1);
                            } else {
                                aux.dias = dias_infetado;
                            }
                        } else {
                            fscanf(file, " \n");
                            aux.dias = 0;
                        }
                    }
                    aux.local = NULL;
                }
                compara = compara->next;
            }
        }
        //printf (" Nome: %s \n Idade: %d || Estado: %c || Dias infetado: %d ||\n",aux.nome,aux.idade,aux.estado,aux.dias);

        iter->pessoa = aux;
        iter->next = (PessoaList *) malloc(sizeof (PessoaList));
        if (iter->next == NULL) {
            printf("ERRO A ALOCAR MEMORIA\n");
            exit(1);
        }
        iter->next->next = NULL;
        anterior = iter;
        iter = iter->next;

        i++;
    }

    if (anterior != NULL) {
        anterior->next = NULL;
        free(iter);
    }
    fclose(file);
    return (temp);
}

void printAllPessoas(PessoaList *head) {
    PessoaList *iter;
    iter = head;
    while (iter != NULL) {
        printf(" Nome: %s \n Idade: %d || Estado: %c || Dias infetado: %d  \n", iter->pessoa.nome, iter->pessoa.idade, iter->pessoa.estado, iter->pessoa.dias);
        if (iter->pessoa.local != NULL) {
            printf(" Esta na sala com id: %d \n\n", iter->pessoa.local->id);
        }
        iter = iter->next;
    }
}

void pessoasEntramLocal(PessoaList * head, Local *locais, int tamLocais) {
    PessoaList *iter = head;
    int rand;
    while (iter != NULL) {
        rand = intUniformRnd(0, tamLocais - 1);
        if (locais[rand].capacidade > 0) {
            iter->pessoa.local = &locais[rand];
            locais[rand].capacidade = locais[rand].capacidade - 1;
            //rand = intUniformRnd(0,tamLocais - 1);    
        } else {
            bool x;
            do {
                x = false;
                rand = intUniformRnd(0, tamLocais - 1);
                if (locais[rand].capacidade <= 0) {
                    x = true;
                }
                if (!x) {
                    break;
                }
            } while (true);
            iter->pessoa.local = &locais[rand];
            locais[rand].capacidade = locais[rand].capacidade - 1;
        }
        //printf("%s foi colocado na sala com id %d \n",iter->pessoa.nome,iter->pessoa.local->id);
        iter = iter->next;
    }
}

bool adicionaDoente(PessoaList * head, Local *locais, int tamLocais) {
    int id, idade, dias_infetado;
    char nome[NAME_LENGHT];
    char str[20];
    Pessoa aux;
    PessoaList * ptr, *iter;
    bool x = false;
    Local *local;
    
    for(int i = 0; i<tamLocais;i++){
        printf("Local %d (capacidade -> %d)\n", locais[i].id, locais[i].capacidade);
    }
    do {
        printf("Intruduza o id da sala em que pretende adicionar o doente:\n- ");
        scanf("%s", str);
        id = atoi(str);
        x = false;
        if (id <= 0) {
            x = true;
        } else {
            for (int i = 0; i < tamLocais; i++) {
                if (locais[i].id == id) {
                    if (locais[i].capacidade <= 0) {
                        printf("Sala cheia!!!\n");
                        x = true;
                    } else {
                        local = &locais[i];
                        break;
                    }
                } else if ((i + 1) >= tamLocais) {
                    printf("Nao foi encontrado sala com esse id\n");
                    x = true;
                }
            }

        }
        if (!x) {
            break;
        }
    } while (true);

    do {
        iter = head;
        x = false;
        printf("Intruduza o nome do doente:\n- ");
        scanf("%s", nome);
        while (iter->next != NULL) {

            if (strcmp(iter->pessoa.nome, nome) == 0) {
                printf("Nome ja existe!\n");
                x = true;
            }
            iter = iter->next;
        }
        if (strcmp(iter->pessoa.nome, nome) == 0) {
            printf("Nome ja existe!\n");
            x = true;
        }
        if (!x) {
            break;
        }

    } while (true);

    do {
        x = false;
        printf("Intruduza a idade do doente:\n- ");
        scanf("%s", str);
        idade = atoi(str);
        if (idade <= 0 || idade >= 150) {
            x = true;
        }
        if (!x) {
            break;
        }
    } while (true);

    do {
        x = false;
        printf("Intruduza o numero de dias que o doente esta infetado:\n- ");
        scanf("%s", str);
        dias_infetado = atoi(str);
        if (dias_infetado <= 0) {
            x = true;
        }
        if (!x) {
            break;
        }
    } while (true);
    ptr = (PessoaList *) malloc(sizeof (PessoaList));
    if (ptr == NULL) {
        printf("Erro a alucar memoria");
        exit(1);
    }
    if (iter->next == NULL) {
        strcpy(aux.nome, nome);
        aux.idade = idade;
        aux.estado = 'D';
        aux.dias = dias_infetado;
        aux.local = local;
        ptr->pessoa = aux;
        ptr->next = NULL;
        iter->next = ptr;

        return (true);
    }
    return (false);
}

bool transferPessoas(PessoaList * head, Local *locais, int tamLocais) {
    int n, id, id_destino;
    char str[30];
    Local *origem, *destino;
    PessoaList * iter;
    bool x;
    int sameLocal = 0;
    for (int j = 0; j < tamLocais; j++) {
        printf("Local %d (capacidade -> %d)\n", locais[j].id, locais[j].capacidade);
    }
    
    do {
        x = false;
        printf("ID da sala que pretende transferir:\n- ");
        scanf("%s", str);
        id = atoi(str);
        for (int i = 0; i < tamLocais; i++) {
            if (locais[i].id == id) {
                origem = &locais[i];
                break;
            }
            if ((i + 1) == tamLocais) {
                printf("Nao foi encontrado sala com esse id\n");
                x = true;
            }
        }
        if (!x) {
            iter = head;
            while (iter != NULL) {
                if (iter->pessoa.local->id == id) {
                    sameLocal++;
                }
                iter = iter->next;
            }
            if (sameLocal == 0) {
                printf("Esse local nao tem pessoas \n");
                x = true;
            }
        }

        if (!x) {
            break;
        }
    } while (true);
    
    printf("Conecoes da sala:");
    for (int i = 0; i < MAX_CONECTIONS; i++) {
        if (origem->conections[i] != -1) {
            printf("%d ;", origem->conections[i]);
        }
    }
    printf("\n");
    do {
        x = false;
        printf("ID da sala que pretende para qual deseja transferir:\n- ");
        scanf("%s", str);
        id_destino = atoi(str);
        if (id_destino <= 0) {
            x = true;
        } else {
            for (int i = 0; i < MAX_CONECTIONS; i++) {
                if (origem->conections[i] == id_destino) {
                    for (int j = 0; j < tamLocais; j++) {
                        if (locais[j].id == id_destino) {
                            destino = &locais[j];
                            if (destino->capacidade <= 0) {
                                printf("Esse destino nao tem capacidade para mais ninguem!\n");
                                x = true;
                            }
                            break;
                        }
                    }
                    break;
                }
                if ((i + 1) == MAX_CONECTIONS) {
                    printf("Nao foi encontrado sala com esse id\n");
                    x = true;
                }
            }
        }

        if (!x) {
            break;
        }
    } while (true);

    printf("Capacidade do destino %d: %d\n", destino->id, destino->capacidade);
    printf("Pessoas no local %d: %d \n", origem->id, sameLocal);
    do {
        x = false;
        printf("Quantas pessoas deseja transferir de sala?\n- ");
        scanf("%s", str);
        n = atoi(str);
        if (n <= 0) {
            x = true;
        } else {
            if (n > sameLocal) {
                printf("A sala nao tem tantas pessoas\n");
                x = true;
            }
            if (destino->capacidade < n) {
                printf("A sala destino nao tem capacidade\n");
                x = true;
            }
        }
        if (!x) {
            break;
        }
    } while (true);

    if (n == sameLocal) {
        // not random
        iter = head;
        while (iter != NULL) {
            if (iter->pessoa.local->id == origem->id) {
                iter->pessoa.local = destino;
                origem->capacidade = origem->capacidade + n;
                destino->capacidade = destino->capacidade - n;
                //printf("pessoa %s traferida de %d para %d \n",iter->pessoa.nome,origem->id,destino->id);
            }
            iter = iter->next;
        }
        return (true);
    } else {
        //transfere de forma random
        for (int j = 0; j < n; j++) {
            int count = 0;
            int random = intUniformRnd(0, sameLocal - 1);
            iter = head;
            while (iter != NULL) {
                if (iter->pessoa.local->id == origem->id) {
                    if (count == random) {
                        iter->pessoa.local = destino;
                        destino->capacidade--;
                        origem->capacidade++;
                        sameLocal--;
                        //printf("pessoa %s traferida de %d para %d \n",iter->pessoa.nome,origem->id,destino->id);
                    }
                    count++;
                }
                iter = iter->next;
            }
        }
        return (true);
    }
    return (false);
}

int numPessoas(PessoaList * head) {
    int num = 0;
    PessoaList * iter = head;
    while (iter != NULL) {
        num++;
        iter = iter->next;
    }
    return num;
}

void freePessoas(PessoaList * head) {
    PessoaList * curr = head;
    PessoaList * anterior = NULL;

    while (curr != NULL) {
        anterior = curr;
        curr = curr->next;

        free(anterior);
    }
}