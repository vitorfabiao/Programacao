/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Preparacao.c
 * Author: Vitor Fabião 2017009683
 * 
 * Created on 12 de Junho de 2020, 18:28
 */


#include "Espaco.h"

local* carregaLocal(char *ficheiroEspaco, int *tam) { //Esta funçao qaundo concluida retorna o array de estruturas do tipo LOcal

    local *espacos;
    local *p = malloc(sizeof (local));
    if (!p) {
        fprintf(stderr, "Erro ao alocar memoria para pessoas %s\n");
        return NULL;
    }

    FILE *f = fopen(ficheiroEspaco, "rb"); //Abre o ficheiro binario indicado pelo user
    if (!f) {
        fprintf(stderr, "Erro ao abrir o ficheiro %s\n", ficheiroEspaco);
        return 0;
    }

    while (fread(p, sizeof (local), 1, f)) { //Enquanto conseguir ler estruturas deste tipo ele vai adicionando ao array um estrutura pessoa

        if (p->capacidade < 0) {
            fclose(f);
            free(p);
            return NULL;
        }

        if (p->id < 0) {
            fclose(f);
            free(p);
            return NULL;
        }
        for (int i = 0; i < 3; i++) {
            if (p->liga[i] < -1) {
                fclose(f);
                free(p);
                return NULL;
            }
        }

        if (*tam == 0) {
            espacos = malloc(sizeof (local)); //Se for a primeira posiçao do array entao ele aloca memoria e retorna o ponteiro
            if (!espacos) {
                fclose(f);
                free(p);
                printf("Erro a alocar memoria");
                return espacos;
            }
        } else { //Se ja houver array então ele entra aqui e realoca, devolvendo o ponteiro do inicio do array
            espacos = realloc(espacos, sizeof (local) * (*tam + 1));
            if (!espacos) {
                fclose(f);
                free(p);
                printf("Erro a alocar memoria");
                return espacos;
            }
        }

        espacos[*tam] = *p;
        *tam += 1;
    }


    fclose(f);
    free(p);
    if (validaLigacao(espacos, *tam) == 1) //Chama a função do verifica ligação para ver se as ligações estão todas corretas
        return espacos;
    else {
        printf("Erro nas ligações\n");
        return NULL;
    }

}

void mostraEspaco(local *Local, int tam) { //Esta função mostra os espaços 

    // system("cls");

    for (int i = 0; i < tam; i++) {
        printf("Capacidade: %d \n ID: %d\n", Local[i].capacidade, Local[i].id);
        for (int j = 0; j < 3; j++) {
            printf("Ligacao %d: %d\n", j + 1, Local[i].liga[j]);
        }
    }

}

int validaLigacao(local *e, int tam) { //Esta função quando terminada devolve 0 se as ligações estiverem mal e returna 1 se estiverem bem
    int aux;
    int id;
    int flag;

    for (int i = 0; i < tam; i++) { //Aqui vai verificar se existem ids repetidos
        for (int j = 0; j < tam; j++) {
            if (e[i].id == e[j].id && i != j) {
                printf("Existem ids repetidos\n");
                return 1;
            }
        }
    }

    for (int i = 0; i < tam; i++) { //for que percorre o array de espaços
        for (int j = 0; j < 3; j++) { //for que percorre o vetor de ligaçoes
            if (e[i].liga[j] > 0) {
                flag = 0;
                id = e[i].id;
                aux = e[i].liga[j];
                for (int k = 0; k < tam; k++) {
                    if (e[k].id == aux) {
                        for (int p = 0; p < 3; p++) {
                            if (e[k].liga[p] == id) { //Entra aqui quando as verificações se confirmam
                                flag = 1;
                            }
                        }
                    }
                }
                if (flag == 0) {
                    printf("Erro numa das ligações do ficheiro");
                    return 0;
                }
            }
        }
    }
    return 1;
}