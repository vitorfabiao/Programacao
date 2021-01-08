/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pessoas.h
 * Author: Vitor Fabião 2017009683
 * 
 * Created on 12 de Junho de 2020, 18:28
 */

#ifndef PESSOAS_H
#define PESSOAS_H
#include "headers.h"
#include "Espaco.h"


    


    pessoas* carregaPessoas(char *ficheiroPessoas,int *nPessoas);
    pessoas *novaPessoa();
    void mostraPessoas(pessoas *pessoas, int tam);




#endif /* PESSOAS_H */
