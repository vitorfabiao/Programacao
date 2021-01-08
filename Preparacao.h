/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Preparacao.h
 * Author: Vitor Fabião 2017009683
 * 
 * Created on 12 de Junho de 2020, 18:28
 */

#ifndef PREPARACAO_H
#define PREPARACAO_H
#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include "Espaco.h"
#include "Pessoas.h"
#include "simulacao.h"


int salascheias(plocal L,int tame,ppar pares); //Função que verifica se as salas ja estao todas cheias ou não

par* emparelhamento(plocal L, pessoas *P, int tame,ppar par, int tamp); //Esta função quando chamada escolhe aleatoriamente uma sala para atribuir à pessoa e depois coloca na estrutura par


#endif /* PREPARACAO_H */