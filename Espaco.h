/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Espaco.h
 * Author: Vitor Fabião 2017009683
 * 
 * Created on 12 de Junho de 2020, 18:28
 */


#ifndef ESPACO_H
#define ESPACO_H
#include "headers.h"
#include "Pessoas.h"
#include "Preparacao.h"


    int validaLigacao(local *L, int tam);//Esta função quando terminada devolve 0 se as ligações estiverem mal e returna 1 se estiverem bem
    local* carregaLocal(char *ficheiroEspaco, int *tam); //Esta funçao qaundo concluida retorna o array de estruturas do tipo LOcal
    void mostraEspaco(local *Local, int tam);//Esta função mostra os espaços 
     



    
    









#endif /* ESPACO_H */
