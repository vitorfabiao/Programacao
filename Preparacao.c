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


#include "Preparacao.h"

int main(int argc, char** argv) {
    int opcao, nPessoas = 0, nEspacos = 0, contaIteracoes = 0;
    //-----FUNÇÃO RANDOM-----//
    initRandom();

    //-----ARRAYS PARA AS STRUCTS-----

    pessoas *Pessoas; //Lista ligada onde vão ser guardadas as pessoas
    local *Local; // Array dinamico onde vao ser guardadas as salas
    par *pares; // Array dinamico de estruturas par que vao guardar as informações principais
    ite *Iteracoes = NULL; // Lista ligada das iterações feitas

    //-----CRIAÇÃO DE UM PONTEIRO PARA OS FICHEIROS-----
    char *ficheiroPessoas;
    char nomeFicheiroPessoas[20];
    char *ficheiroEspaco;
    char nomeFicheiroEspaco[20];

    //NOME DO FICHEIRO A CARREGAR

    printf("Qual o nome do documento das pessoas? (.txt) \n");
    scanf("%s", nomeFicheiroPessoas);
    printf("Qual o nome do documento do espaco?  (.bin) \n");
    scanf("%s", nomeFicheiroEspaco);
    printf("\n");
    
    ficheiroEspaco = nomeFicheiroEspaco; //Nome do ficheiro Espaço que o utilizador pretende abrir
    ficheiroPessoas = nomeFicheiroPessoas; //Nome do ficheiro Pessoas que o utilizador pretende abrir



    // FUNÇAO QUE VAI CARREGAR OS FICHEIROS

    Local = carregaLocal(ficheiroEspaco, &nEspacos); //É carregada para a variavel Local o array dinamico das estruturas Sala
    if (Local == NULL) {
        printf("Erro ao carregar os espacos\n");
        return 1;
    }
    Pessoas = carregaPessoas(ficheiroPessoas, &nPessoas); //É carregada para a variavel Pessoas a lista ligada que contem as pessoas
    if (Pessoas == NULL) {
        printf("Erro ao carregar as pessoas\n");
        free(Local);
        return 1;
    }

    pares = emparelhamento(Local, Pessoas, nEspacos, pares, nPessoas); //É carregado para a variavel Conjunto o array de estruturas que contem a sala e as respetivas pessoas
    if (Pessoas == NULL) {
        printf("Erro ao emparelhar as pessoas com salas\n");
        free(Local);
        free(Pessoas);
        return 1;
    }
    //------------FUNÇÃO QUE NAO PERMITE A INSERÇAO DE OUTROS CARACTERES SENAO OS AD3QUADOS--------

    int readInt() {

        int integer;
        char buf[6] = "\0";

        scanf(" %5[^\n]", buf);

        while (fgetc(stdin) != '\n');

        for (int i = 0; i < strlen(buf); i++) {

            if (buf[i] < '0' || buf[i] > '9') {
                return -1;
            }
        }

        integer = atoi(buf);

        return integer;
    }

    ppessoas aux;
    pite auxi;
    //-----MENU PRINCIPAL-----
    do {
        printf("\n\n\n#######--MENU--#######\n\n");
        printf("\t(1) - Mostrar Pessoas\n");
        printf("\t(2) - Mostrar Espacos\n");
        printf("\t(3) - Comecar Simulacao\n");
        printf("\t(4) - Sair\n");
        printf("Opcao: ");
        opcao = readInt();
        switch (opcao) {
            case 1:
                puts("Escolheu a opcao: (1).....\n");
                mostraPessoas(Pessoas, nPessoas); //Função que apresenta no ecra as pessoas daquele momento
                break;
            case 2:
                puts("Escolheu a opcao: (2).....\n");
                mostraEspaco(Local, nEspacos); //Função que apresenta no ecra as salas daquele momento
                break;
            case 3:
                system("cls");
                Logistica(Pessoas, Local, pares, nEspacos, &nPessoas, Iteracoes, &contaIteracoes); //Quando esta função é chamada vai para a simulação.c e é enviada a informação necessária
                while (!Pessoas) { //Free da lista de pessoas
                    aux = Pessoas;
                    Pessoas = Pessoas->next;
                    free(aux);
                }
                for (int i = 0; i < nEspacos; i++) {
                    free(&Local[i]); //Free dos Locais e ao mesmo tempo do conjunto de estruturas que continham as duas estrutras( sala e pessoas) 
                    free(&pares[i]);
                }
                while (!Iteracoes) {
                    auxi = Iteracoes;
                    while (!auxi->lpessoa) {
                        aux = auxi->lpessoa;
                        auxi->lpessoa = auxi->lpessoa->next;
                        free(aux); //Free das listas ligadas guardadas por copia
                    }

                    for (int i = 0; i < nEspacos; i++) {
                        free(auxi->conjuntos[i].sala); //Free das salas guardadas por cópia
                        for (int j = 0; j < auxi->conjuntos[i].total; j++) {
                            free(auxi->conjuntos[i].pessoas[j]); //Free do array de ponteiros de pessoas pertencentes a uma sala 
                        }
                    }

                    Iteracoes = Iteracoes->next;
                    free(auxi); //Free do do nodulo da iteracao

                }
                break;
                //FUNÇÃO QUE DÁ ACESSO AO MENU CAMPEONATO
            case 4:
                puts("Escolheu a opcao: (4). A terminar o programa....\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}

par* emparelhamento(plocal L, ppessoas P, int tame, ppar pares, int tamp) { //Esta função quando chamada escolhe aleatoriamente uma sala para atribuir à pessoa e depois coloca na estrutura par
    ppessoas aux = P;
    int contaP = 0;

    pares = malloc(sizeof (par) * tame); //Cria X estruturas dinamicamente para alocar as informaçoes
    if (!pares) {
        printf("Erro a alocar espaco para a estrutura par");
        return pares;
    }

    for (int i = 0; i < tame; i++) {
        pares[i].sala = (local*) malloc(sizeof (local)); //Aloca sitio para um ponteiro sala e guarda as informacoes diretas da estrutura par
        if (!pares[i].sala) {
            printf("Erro a alocar espaco para a estrutura par");
            return pares;
        }
        pares[i].sala = &L[i];
        pares[i].total = 0;
        pares[i].totalInfetadas = 0;
    }

    int valorS, check, valorP;
    int contador = 0;
    int checksala = 0;

    while (contaP != tamp && salascheias(L,tame,pares) == 1) {
        aux = P;
        valorS = intUniformRnd(0, tame - 1); // Escolhe aleatoriamente no intervalo de X salas, em que sala a pessoa se vai alocar, se livre
        valorP = intUniformRnd(0, tamp - 1); // Escolhe aleatoriamente no intervalo de X pessoas, em que sala a pessoa se vai alocar, se livre
        check = 0;

        if (pares[valorS].total < L[valorS].capacidade) {
            for (int p = 0; p < valorP; p++) {
                aux = aux->next;
            }
            for (int j = 0; j < tame; j++) {
                for (int i = 0; i < pares[j].total; i++) {
                    if (strcmp(pares[j].pessoas[i]->nome, aux->nome) == 0) {
                        check = 1;
                    }
                }
            }
            if (check == 0) {
                if (pares[valorS].total == 0) {
                    pares[valorS].pessoas = (ppessoas*) malloc(sizeof (pessoas*)); //Depois de escolhida a sala ele vai la e aloca espaco caso nao tenha ninguem ainda
                    if (!pares[valorS].pessoas) {
                        printf("Erro a alocar memoria");
                        return pares;
                    }
                } else {
                    pares[valorS].pessoas = (ppessoas*) realloc(pares[valorS].pessoas, sizeof (pessoas*) * (pares[valorS].total + 1)); //Caso ja tenho alguem ele simplesmente realoca
                    if (!pares[valorS].pessoas) {
                        printf("Erro a alocar memoria");
                        return pares;
                    }

                }
                pares[valorS].pessoas[pares[valorS].total] = aux; //Adiciona o Ponteiro da pessoa naquela parte do array
                (pares[valorS].total)++;
                contador++;
                contaP++;
            }
        }
        for(int i=0;i<tame;i++){
        }
    }
    for (int i = 0; i < tame; i++) {
        printf("Pares: %d\n", pares[i].total);
    }
    printf("Numero de pessoas colocadas em salas: %d", contador);

    return pares;
}


int salascheias(plocal L,int tame,ppar pares){
    for(int i=0;i<tame;i++){
        if(L[i].capacidade != pares[i].total){
            return 1;
        } 
    }
    return 0;
}
