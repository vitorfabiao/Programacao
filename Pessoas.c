/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pessoas.c
 * Author: Vitor Fabião 2017009683
 * 
 * Created on 12 de Junho de 2020, 18:28
 */


#include "Pessoas.h"

pessoas* carregaPessoas(char *ficheiroPessoas, int *nPessoas) { //Função que no fim irá devolver a lista de pessoas carregadas do ficheiro

    ppessoas listapessoas = NULL;
    ppessoas aux = NULL;
    pessoas p;
    ppessoas verificaNome;

    FILE *f = fopen(ficheiroPessoas, "rt"); //Abre o ficheiro pedido pela pessoa
    if (!f) {
        fprintf(stderr, "Erro ao abrir o ficheiro %s\n", ficheiroPessoas);
        return NULL;
    }
    while (fscanf(f, "%s %d %c", p.nome, &p.idade, &p.estado) != EOF) { //Enquanto conseguir ler do ficheiro aquelas condições então preenche sempre mais 1 pessoa
        verificaNome = listapessoas;
        while (verificaNome){
            if(strcmp(verificaNome->nome,p.nome)== 0){
                printf("Existem nomes iguais\n");
                return NULL;
            }
            verificaNome = verificaNome->next;
        }
        
        
        if (p.estado != 'D' && p.estado != 'S' && p.estado != 'I') {
            printf("Estado das pessoas nao correto\n");
            return NULL;
        }
        if (p.idade <= 0) {
            printf("Idade inválida\n");
            return NULL;
        }

        if (listapessoas == NULL) { //Se a lista estiver ainda por comecar então entra aqui
            listapessoas = malloc(sizeof (pessoas)); //aloca espaço para uma estrutura daquele tipo e retorna o ponteiro para ela
            if (listapessoas == NULL) {
                printf("Erro a alocar memoria para pessoas\n");
                return NULL;
            }
            listapessoas->next = NULL;
            strcpy(listapessoas->nome, p.nome);
            listapessoas->estado = p.estado;
            listapessoas->idade = p.idade;
            if (listapessoas->estado == 'D') {
                fscanf(f, " %d", &listapessoas->doente);
                listapessoas->diasMax = DurMaxInf(listapessoas->idade,listapessoas->doente);
            }
            aux = listapessoas;
        }
        else { //Se a lista ja tiver sido inicializada então aqui vai dar a sua continuidade
            aux->next = malloc(sizeof (pessoas));
            if (aux == NULL) {
                printf("Erro a alocar memoria para pessoas\n");
                return NULL;
            }
            aux = aux->next;
            strcpy(aux->nome, p.nome);
            aux->estado = p.estado;
            aux->idade = p.idade;
            if (aux->estado == 'D') {
                fscanf(f, " %d", &aux->doente);
                aux->diasMax = DurMaxInf(aux->idade,aux->doente);
            }
            aux->next = NULL;
        }
        (*nPessoas)++; //contador de pessoas alocadas na lista
    }

    printf("Numero de pessoas: %d\n", *nPessoas);
    fclose(f);
    return listapessoas;
}

void mostraPessoas(pessoas *pessoas, int tam) { //Esta função mostra a lista de pessoas ja carregada
    ppessoas aux = pessoas;

    while (aux) {
        printf("%s \t %d \t %c", aux->nome, aux->idade, aux->estado);
        if (aux->estado == 'D') {
            printf("\t%d", aux->doente);
        }
        printf("\n");
        aux = aux->next;

    }
    return;
}