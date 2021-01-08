
#ifndef SIMULACAO_H
#define SIMULACAO_H
#include "headers.h"
#include "Pessoas.h"
#include "Espaco.h"
#include "Preparacao.h"


void preenchePessoa(ppessoas listap, int *tam); //Esta função quando é chamada pede informações ao utilizador e guarda uma estruturra daquele tipo na variavel novo
pessoas* insereDoente(ppessoas listap, local *sala, int nloc, int *tam, ppar pares);//Esta função quando é chamada insere uma nova pessoa na lista e tambem o ponteiro dela na estrutura par
void disseminacao(ppessoas lista,ppar pares,int tame); //Esta função quando chamada aplica a função de disseminação nas pessoas
int ProbRecuperacao(int idade); //Retorna se ficou infetado ou nao
int DurMaxInf(int idade, int diasPassados);//Esta função calcula a probabilidade de recuperação de uma pessoa
void Logistica(ppessoas lista, plocal locais, ppar pares, int tame, int *tamp, pite it, int *contit);//Função que calcula os dias maximos que a pessoa irá ficar infetada
ite* iteracao(ppar pares, int tame, pite it, int *contit, plocal locais, ppessoas lista);  //Esta função quando terminada devolve a lista de iterações atualizada e no seu decurso ainda avança uma iteração nas pessoas
int ProbRecuperacao(int idade);//Esta função calcula a probabilidade de recuperação de uma pessoa
void estatistica(ppar p,int tame);//Esta função apresenta as estatisticas da iteração atual
void transferir(ppar p, int tame);//Esta função vai transferir um x pessoas de uma sala para a outra
void terminaSimulacao(ppar pares, ppessoas p, plocal sala, int tame, char *fname);//Quando pede para terminar a simulação entao é ativada esta função
ite* AndaTras(ppar pares, ppessoas lista, int contit, pite its);//Quando entra nesta função, dependendo do numero de iterações a recuar, a função irá retornar o nodo correto
ite* guardaIteracao(ppar pares, int tame, pite its, int nIte,local *locais, ppessoas lista);//Função que retorna a lista atualizada das iteraçoesw

#endif /* SIMULACAO_H */
