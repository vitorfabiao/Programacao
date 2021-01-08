/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   headers.h
 * Author: Vitor Fabião 2017009683
 * 
 * Created on 12 de Junho de 2020, 18:28
 */

#ifndef HEADERS_H
#define HEADERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"


typedef struct Pessoas pessoas, *ppessoas; //Estrutura que vai conter toda a informação individual da pessoa
typedef struct sala local, *plocal; //Estrutura imposta no enunciado que guarda as informações do local
typedef struct Par par, *ppar; //Estrutura que guarda o ponteiro da sala e algumas informaçoes extra, assim como um array de ponteiros de estruturas pessoas
typedef struct Iteracoes ite, *pite;  // Estrutura que guarda o array de estruturas pares e a lista ligada de pessoas

struct Pessoas { 
    char nome[20];
    int idade;
    char estado;
    int doente;
    int diasMax;
   // plocal idSala; //id da sala atribuido
    ppessoas next;
};

struct sala {
    int id; // id numérico do local      
    int capacidade; // capacidade máxima 
    int liga[3]; // id das ligações (-1 nos casos não usados) 
};

struct Par { //Estrutura que guarda um ponteiro para uma sala e um array de ponteiros para pessoas
    plocal sala;
    int total, totalInfetadas;
    ppessoas *pessoas;
};

struct Iteracoes{ //Estrutra que guarda uma iteração completa
    ppar conjuntos;
    ppessoas lpessoa;
    pite next;
};


#endif /* HEADERS_H */

