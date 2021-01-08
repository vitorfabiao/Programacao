/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simulacao.c
 * Author: Vitor Fabião 2017009683
 * 
 * Created on 12 de Junho de 2020, 18:28
 */

#include "simulacao.h"

void preenchePessoa(ppessoas listap, int *tam) { //Esta função quando é chamada pede informações ao utilizador e guarda uma estruturra daquele tipo na variavel novo
    ppessoas aux = listap;
    printf("Identificador da pessoa: \n");
    scanf(" %99[^\n]", aux->nome);
    printf("Idade: \n");
    scanf("%d", &aux->idade);
    printf("Numero de dias de infecao: \n");
    scanf("%d", &aux->doente);
    aux->estado = 'D';
    (*tam)++;
    aux->next = NULL;
}

pessoas* insereDoente(ppessoas listap, local *sala, int nloc, int *tam, ppar pares) { //Esta função quando é chamada insere uma nova pessoa na lista e tambem o ponteiro dela na estrutura par
    ppessoas novo, aux;
    int x = 0;
    int flag = 0;
    novo = malloc(sizeof (pessoas)); //Aloca espaço numa estrutura nova que depois 
    if (novo == NULL) {
        printf("Erro na alocacao de memoria(4)\n");
        return listap;
    }
    preenchePessoa(novo, tam); //chama a função para que o novo seja preenchido
    do {
        printf("Id da sala: \n");
        scanf("%d", &x);
        for (int i = 0; i < nloc; i++) {
            if (sala[i].id == x) {
                flag = 1;
            }
        }
    } while (flag == 0); //Verifica se o user coloca um ID valido
    if (listap == NULL)
        listap = novo; // Se a lista nao tiver nada cria o primeiro nodulo
    else {
        aux = listap;
        while (aux->next != NULL) //senão vai buscar o ultimo nodulo e adiciona depois desse
            aux = aux->next;
        aux->next = novo;
        (*tam) += 1;
    }

    for (int i = 0; i < nloc; i++) {
        if (pares[i].sala->id == x) {
            pares[i].pessoas = (ppessoas*) realloc(pares[i].pessoas, sizeof (pessoas*) * (pares[i].total + 1)); //Faz o realloc no array de ponteiros das pessoas da estrutura daquela sala 
            if (!pares[i].pessoas) {
                printf("Erro a alocar memoria");
            }
            pares[i].total += 1;
            pares[i].pessoas[pares[i].total - 1] = novo; //Atribui o ponteiro aquele sitio no array das pessoas da estrutura par
        }
    }

    for (int i = 0; i < nloc; i++) {
        printf("Sala: %d\n", pares[i].sala->id);
        for (int j = 0; j < pares[i].total; j++) {
            printf("Pessoa: %s\n", pares[i].pessoas[j]->nome);
        }
    }
    return listap; //Retorna a lista de pessoas 
}

void disseminacao(ppessoas lista, ppar pares, int tame) { //Esta função quando chamada aplica a função de disseminação nas pessoas
    int numpessoas, pessoax, contaDoentes = 0;

    for (int i = 0; i < tame; i++) {
        numpessoas = pares[i].total * 0.05; //Verifica quantas pessoas uma pessoa doente irá infetar
        contaDoentes = 0;
        for (int k = 0; k < pares[i].total; k++) {
            if (pares[i].pessoas[k]->estado == 'D') { //Conta quantos doentes são
                contaDoentes++;
            }
        }

        if ((numpessoas *= contaDoentes) <= pares[i].total) {
            for (int j = 0; j < numpessoas; j++) {
                pessoax = intUniformRnd(0, numpessoas - 1); //Escolhe aleatoriamente uma pessoa a que infetar que nao seja imune
                if (pares[i].pessoas[pessoax]->estado == 'S' && pares[i].totalInfetadas != pares[i].total) {
                    pares[i].pessoas[pessoax]->estado = 'D';
                    pares[i].pessoas[pessoax]->doente = 0;
                    pares[i].pessoas[pessoax]->diasMax = DurMaxInf(pares[i].pessoas[pessoax]->idade, pares[i].pessoas[pessoax]->doente);

                    printf("A pessoa %s foi afetada na sala %d\n", pares[i].pessoas[pessoax]->nome, pares[i].sala->id);
                }
                (pares[i].totalInfetadas)++;
            }
        }
    }
}

int ProbRecuperacao(int idade) { //Esta função calcula a probabilidade de recuperação de uma pessoa
    float prob;
    int Nim;

    prob = 1 / idade;

    Nim = probEvento(prob);

    return Nim;
}

int DurMaxInf(int idade, int diasPassados) { //Função que calcula os dias maximos que a pessoa irá ficar infetada
    int dias;

    dias = 5 + (idade / 10);
    dias = dias - diasPassados;
    return dias;
}

void Logistica(ppessoas lista, plocal locais, ppar pares, int tame, int *tamp, pite it, int *contit) { //Função que faz a gestão dos pedidos conforme o user

    int opcao;
    char fname[50];
    pite aux;

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

    //-----MENU PRINCIPAL-----
    do {
        printf("\n\n\n#######--MENU SIMULACAO--#######\n\n");
        printf("\t(1) - Avancar uma iteracao\n");
        printf("\t(2) - Apresentar estatistica\n");
        printf("\t(3) - Adicionar Doente\n");
        printf("\t(4) - Transferir Pessoa\n");
        printf("\t(5) - Recuar X iteracoes\n");
        printf("\t(6) - Mostrar Pessoas\n");
        printf("\t(7) - Mostrar espacos\n");
        printf("\t(8) - Sair\n");

        printf("Opcao: ");
        opcao = readInt();
        switch (opcao) {
            case 1:
                system("cls");
                puts("Escolheu a opcao: (1).....\n");
                it = iteracao(pares, tame, it, contit, locais, lista); //Esta função quando chamada avança uma iteração e retorna a lista das iterações atualizada
                break;
            case 2:
                system("cls");
                puts("Escolheu a opcao: (2).....\n");
                estatistica(pares, tame); //Esta função apresenta as estatisticas daquele presente momento
                break;
            case 3:
                system("cls");
                puts("Escolheu a opcao: (3).....\n");
                insereDoente(lista, locais, tame, tamp, pares); //Esta função cria um novo cliente nas estruturas e na lista ligada das pessoas
                break;
            case 4:
                system("cls");
                puts("Escolheu a opcao: (4)\n");
                transferir(pares, tame); //Esta função transfere pessoas de uma sala para outra
                break;
                //FUNÇÃO QUE DÁ ACESSO AO MENU CAMPEONATO
            case 5:
                system("cls");
                aux = AndaTras(pares, lista, *contit, it);  //Função que quando chamada retorna o no da iteração correspondente ao recuo
                lista = aux->lpessoa;
                pares = aux->conjuntos;
                puts("Escolheu a opcao: (3).....\n");
                break;
            case 6:
                system("cls");
                mostraPessoas(lista, *tamp);
                break;
            case 7:
                system("cls");
                mostraEspaco(locais, tame);
                break;
            case 8:
                system("cls");
                puts("Escolheu a opcao: (5). A terminar o programa....\n");
                printf("Nome do ficheiro: (.txt)\n");
                scanf("%s", &fname);
                terminaSimulacao(pares, lista, locais, tame, fname); //Esta função termina a simulacao e preenche tanto o relatorio como o ficheiro txt criado pelo user
                break;
        }
    } while (opcao != 8);
}

ite* iteracao(ppar pares, int tame, pite it, int *contit, plocal locais, ppessoas lista) { //Esta função quando terminada devolve a lista de iterações atualizada e no seu decurso ainda avança uma iteração nas pessoas
    ppessoas aux = lista;

    if(*contit == 0){
        it = guardaIteracao(pares, tame, it, *contit, locais, lista); // Aqui ele guarda a iteração original
    }
    
    while (aux) {       
        if (aux->estado == 'D' && aux->diasMax != 0) { //Verifica se a pessoa que ainda esta doente fica curada ou nao e se fica ou nao imune
            if (ProbRecuperacao(aux->idade) == 1) {
                if (probEvento(0.20) == 1) {
                    aux->estado = 'I';
                } else
                    aux->estado = 'S';
            }
            (aux->diasMax)--;
            (aux->doente)++;
        }
        if (aux->estado == 'D' && aux->diasMax == 0) { //aqui é quando a pessoa chega ao fim dos dias maximos de infecao e calcula se fica saudavel ou imune 
            if (probEvento(0.20) == 1) {
                aux->estado = 'I';
            } else
                aux->estado = 'S';
        }

        aux = aux->next;
    }
    (*contit) += 1;
    disseminacao(lista, pares, tame); // Chama a função que determina a disseminação

    it = guardaIteracao(pares, tame, it, *contit, locais, lista); //à medida que vai avançando uma iteração ele guarda uma iteração
    return it;
}

void estatistica(ppar p, int tame) { //Esta função apresenta as estatisticas da iteração atual

    int contaInfetados = 0, saudaveis = 0, imunes = 0, doentes = 0;
    float taxasau, taxadoe, taxaim;

    for (int i = 0; i < tame; i++) {
        printf("Sala %d:\n", p[i].sala->id);
        for (int j = 0; j < p[i].total; j++) {
            printf("\t%d - %s\n", j + 1, p[i].pessoas[j]->nome);
        }
    }
    for (int i = 0; i < tame; i++) { //Verifica quantas pessoas foram infetadas na ultima iteracao
        contaInfetados = 0;
        printf("Sala %d:\n", p[i].sala->id);
        for (int j = 0; j < p[i].total; j++) {
            if (p[i].pessoas[j]->doente == 0 && p[i].pessoas[j]->estado == 'D') {
                contaInfetados++;
            }
        }
        printf("Na ultima iteracao foram infetadas %d pessoas\n", contaInfetados);
    }

    for (int i = 0; i < tame; i++) { //Faz a contagem de quantas pessoas possuem cada tipo de estado
        contaInfetados = 0;
        saudaveis = 0;
        imunes = 0;
        doentes = 0;
        printf("Sala %d:\n", p[i].sala->id);
        for (int j = 0; j < p[i].total; j++) {
            if (p[i].pessoas[j]->estado == 'S') {
                saudaveis++;
            }
            if (p[i].pessoas[j]->estado == 'I') {
                imunes++;
            }
            if (p[i].pessoas[j]->estado == 'D') {
                doentes++;
            }

        }

        taxasau = (float) saudaveis / p[i].total; // Calcula as percentagens correspondentes na sala
        taxasau *= 100;
        printf("Taxa de Saudaveis: %.2f \% \n", taxasau);
        taxaim = (float) imunes / p[i].total;
        taxaim *= 100;
        printf("Taxa de Imunes: %.2f \% \n", taxaim);
        taxadoe = (float) doentes / p[i].total;
        taxadoe *= 100;
        printf("Taxa de Doentes: %.2f \% \n", taxadoe);
    }


}

void transferir(ppar p, int tame) { //Esta função vai transferir um x pessoas de uma sala para a outra
    int numpessoas, origem = 0, destino = 0;
    int checko = 0, checkd = 0; // checks que verificam se os ids existem
    int checka = 0; // Verifica se existe ligacao entre origem e destino
    int espacoDisp; //Verifica se o local de destino tem espaco para receber os manegos
    int ficaramT; //variavel que vai guardar o total de pessoas que vao ficar na sala
    int checkp = 0; //verifica se a pessoa escolhida esta no array 
    int pos = 0; //posicao do array novo das 
    int checku = 0; //verificar se não escolhe pessoas iguais na sala de origem
    int checkz = 0; //verifica a quantidade de pessoas aleatórias 
    int contaAl = 0; //contador para as pessoas aleatórias
    plocal porigem;
    plocal pdestino;
    ppessoas *escolhidas; //ponteiro para o array de ponteiros das pessoas que vao ser transferidas
    ppessoas *ficaram; //ponteiro para o novo array de gajos que ficaram
    int pessoax;

    printf("Para sair desta funcao insira -1\n\n");
    printf("Quantas pessoas pretende transferir? \n");
    scanf("%d", &numpessoas);

    while (checko == 0 && origem != -1) { // Faz as verificações da sala de origem
        printf("Qual o local de origem?\n");
        scanf("%d", &origem);
        for (int i = 0; i < tame; i++) {
            if (p[i].sala->id == origem) {
                if (p[i].total < numpessoas)
                    printf("Nao existem tantas pessoas assim na origem, pah\n");
                else {
                    checko = 1;
                    porigem = p[i].sala;
                }
            }
        }
    }
    while (checkd == 0 && checko == 1 && destino != -1) {// Faz as verificações da sala de destino
        printf("Qual o local de destino?\n");
        scanf("%d", &destino);
        for (int i = 0; i < tame; i++) {
            if (p[i].sala->id == destino && destino != origem) {
                espacoDisp = p[i].sala->capacidade - p[i].total;
                if (numpessoas > espacoDisp)
                    printf("Nao existe espaco disponivel no destino, pah\n");
                else {
                    checkd = 1;
                    pdestino = p[i].sala;
                }
            }
        }
    }

    if (checkd == 1 && checko == 1) {
        for (int i = 0; i < 3; i++) {
            if (porigem->id == pdestino->liga[i])
                checka = 1;
        }
        if (checka == 0) {
            printf("Nao e possivel transferir doentes porque estas salas nao tem ligacao\n");
        }
    }
    // Aqui começa a tratar da sala de origem

    if (checka != 0) {
        escolhidas = (ppessoas*) malloc(sizeof (pessoas*) * numpessoas); //Cria um vetor para as pessoas escolhidas 
        if (!escolhidas) {
            printf("Erro a alocar memoria para o array de pessoas escolhidas para transferir\n");
        }

        for (int i = 0; i < tame; i++) {
            if (p[i].sala == porigem && checkd == 1 && checko == 1) {
                while (contaAl != numpessoas) {
                    pessoax = intUniformRnd(0, p[i].total - 1); //Escolhe as pessoas aleatorias a serem enviadas para a outra sala
                    checku = 0;
                    for (int k = 0; k < numpessoas; k++) {

                        if (escolhidas[k] == p[i].pessoas[pessoax])
                            checku = 1;
                    }
                    if (checku == 0) {
                        escolhidas[contaAl] = p[i].pessoas[pessoax];
                        printf("Escolhida: %s\n", p[i].pessoas[pessoax]);
                        contaAl++;
                    }
                }
                pos = 0;
                ficaramT = p[i].total - numpessoas; 
                ficaram = (ppessoas*) malloc(sizeof (pessoas*) * ficaramT); //recria o novo array para as pessoas que não foram escolhidas para a transferência
                if (!escolhidas) {
                    printf("Erro a alocar memoria para o array de pessoas escolhidas para transferir\n");
                }
                for (int j = 0; j < p[i].total; j++) { //Vai alocando as pessoas uma a uma no array
                    checkp = 0;
                    for (int k = 0; k < numpessoas; k++) {
                        if (p[i].pessoas[j] == escolhidas[k]) {
                            checkp = 1;
                        }
                    }
                    if (checkp == 0) {
                        ficaram[pos] = p[i].pessoas[j];
                        pos++;
                    }
                }
                p[i].pessoas = ficaram; //coloca o array no sitio anterior da estrutura
                p[i].total = p[i].total - numpessoas;
                for (int t = 0; t < p[i].total; t++) {
                    printf("%d - %s\n", t + 1, p[i].pessoas[t]->nome);
                }
            }
        }

        // Aqui começa a tratar da sala de destino
        for (int i = 0; i < tame; i++) {
            if (p[i].sala == pdestino) {
                p[i].total = p[i].total + numpessoas;
                p[i].pessoas = (ppessoas*) realloc(p[i].pessoas, sizeof (pessoas*) * (p[i].total)); //Aqui faz um realloc do array das pessoas para meter aquelas que foram enviadas da outra sala
                if (!p[i].pessoas) {
                    printf("Erro a alocar memoria no destino");
                }

                for (int j = (p[i].total - numpessoas); j < p[i].total; j++) {

                    p[i].pessoas[j] = escolhidas[contaAl - 1];
                    contaAl--;
                }
            }
        }
    }
}

void terminaSimulacao(ppar pares, ppessoas p, plocal sala, int tame, char *fname) { //Quando pede para terminar a simulação entao é ativada esta função

    ppessoas aux = p;
    FILE *f;

    int saudaveis = 0;
    int imunes = 0;
    int doentes = 0;
    float taxasau, taxaim, taxadoe;


    f = fopen("report.txt", "wt"); //Abre o ficheiro apra qeu possa ser escrito
    if (f == NULL) {
        printf("Erro ao criar ficheiro!(1)\n");
        return;
    }

    for (int i = 0; i < tame; i++) { //Escreve no ficheiro as coisas que o relatorio quer

        saudaveis = 0;
        imunes = 0;
        doentes = 0;

        fprintf(f, "Sala %d\n", pares->sala[i].id); //escreve o ID da sala

        for (int j = 0; j < pares[i].total; j++) { //escreve as pessoas
            fprintf(f, "\t%s", pares[i].pessoas[j]->nome);
            fprintf(f, "\t%d", pares[i].pessoas[j]->idade);
            fprintf(f, "\t%c", pares[i].pessoas[j]->estado);
            if (pares[i].pessoas[j]->estado == 'D')
                fprintf(f, "\t%d", pares[i].pessoas[j]->doente);
            fprintf(f, "\n");
        }

        for (int z = 0; z < pares[i].total; z++) { //faz a contagem para depois as estatisticas
            if (pares[i].pessoas[z]->estado == 'S') {
                saudaveis++;
            }
            if (pares[i].pessoas[z]->estado == 'I') {
                imunes++;
            }
            if (pares[i].pessoas[z]->estado == 'D') {
                doentes++;
            }
        }

        fprintf(f, "\t--------------------------\n");

        taxasau = (float) saudaveis / pares[i].total; //faz as conas das estatisticas para o ficheiro
        taxasau *= 100;
        fprintf(f, "\tTaxa de Saudaveis: %.2f % \n", taxasau);
        taxaim = (float) imunes / pares[i].total;
        taxaim *= 100;
        fprintf(f, "\tTaxa de Imunes: %.2f  % \n", taxaim);
        taxadoe = (float) doentes / pares[i].total;
        taxadoe *= 100;
        fprintf(f, "\tTaxa de Doentes: %.2f % \n\n", taxadoe);
    }

    fclose(f);

    FILE *f1;

    f1 = fopen(fname, "wt"); //Abre o ficheiro com o nome pedido pelo user para escrever as infos das pessoas
    if (f1 == NULL) {
        printf("Erro ao criar ficheiro!(2)");
        return;
    }


    while (aux != NULL) { //Insere as informações todas as pessoas daquele momento
        fprintf(f1, "%s", aux->nome);
        fprintf(f1, "\t%d", aux->idade);
        fprintf(f1, "\t%c", aux->estado);
        if (aux->estado == 'D') {
            fprintf(f1, "\t%d", aux->doente);
        }
        fprintf(f1, "\n");

        aux = aux->next;
    }

    fclose(f1);

}

ite* guardaIteracao(ppar pares, int tame, pite its, int nIte, local *locais, ppessoas lista) { //Função que retorna a lista atualizada das iteraçoesw

    ppessoas aux = lista;
    ppessoas pessoait = NULL, auxi;
    pite auxj, auxp;
    int check = 0; //variavel que verifica se ja esta o no criado
    
    //Cria e armazena uma nova lista ligada de pessoas
    while (aux) { //Faz a copia integral da lista das pessoas daquele momento
        if (pessoait == NULL) {       //Se for o primeiro nó então faz isto
            pessoait = (pessoas*) malloc(sizeof (pessoas));
            if (!pessoait) {
                printf("Erro a alocar pessoa ao guardar iteracao\n");
                return its;
            }
            pessoait->diasMax = aux->diasMax;
            pessoait->doente = aux->doente;
            pessoait->estado = aux->estado;
            pessoait->idade = aux->idade;
            strcpy(pessoait->nome, aux->nome);
            pessoait->next = NULL;
            auxi = pessoait;
            aux = aux->next;
        } else {  //Senão continua os nós por ai adiante
            auxi->next = (pessoas*) malloc(sizeof (pessoas));
            if (!auxi->next) {
                printf("Erro a alocar pessoa ao guardar iteracao\n");
                return its;
            }
            auxi = auxi->next;
            auxi->diasMax = aux->diasMax;
            auxi->doente = aux->doente;
            auxi->estado = aux->estado;
            auxi->idade = aux->idade;
            strcpy(auxi->nome, aux->nome);
            auxi->next = NULL;
            aux = aux->next;
        }
    }
    //Como o espaço não se altera, apenas a sua capaciadde e afins então podemos usar sempre o original


    if (nIte <= 3) { //Se o numero de interações for inferior a 3 então ele ainda esta na faze de construção da lista

        if (its == NULL) { //Entra aqui caso seja a primeira iteração original
            its = (pite) malloc(sizeof (ite)); //Aloca espaço para um nodulo daquele tipo
            if (!its) {
                printf("Erro a alocar pessoa ao guardar iteracao\n");
                return its;
            }
            its->conjuntos = malloc(sizeof (par) * tame); // Aloca espaço para um array de estruturas do tipo par
            if (!its->conjuntos) {
                printf("Erro a alocar pessoa ao guardar iteracao\n");
                return its;
            }

            for (int i = 0; i < tame; i++) {//Guarda as informações dentro de cada estrutura para do array 
                its->conjuntos[i].sala = pares[i].sala;
                its->conjuntos[i].total = pares[i].total;
                its->conjuntos[i].totalInfetadas = pares[i].totalInfetadas;
                its->conjuntos[i].pessoas = (ppessoas*) malloc(sizeof (pessoas*) * pares[i].total); //Aloca espaço para um novo array de ponteiros para estruturas do tipo pessoas
                if (!its->conjuntos[i].pessoas) {
                    printf("Erro a alocar pessoa ao guardar iteracao\n");
                    return its;
                }
                for (int j = 0; j < pares[i].total; j++) {
                    its->conjuntos[i].pessoas[j] = (pessoas*) malloc(sizeof (pessoas)); //Aloca espaço para cada pessoa dentro do array de ponteiros
                    if (!its->conjuntos[i].pessoas[j]) {
                        fprintf(stderr, "Erro ao alocar pessoas\n");
                        return NULL;
                    }
                    its->conjuntos[i].pessoas[j]->estado = pares[i].pessoas[j]->estado;
                    if (pares[i].pessoas[j]->estado == 'D') {
                        its->conjuntos[i].pessoas[j]->diasMax = pares[i].pessoas[j]->diasMax;
                        its->conjuntos[i].pessoas[j]->doente = pares[i].pessoas[j]->doente;
                    }

                    its->conjuntos[i].pessoas[j]->idade = pares[i].pessoas[j]->idade;
                    strcpy(its->conjuntos[i].pessoas[j]->nome, pares[i].pessoas[j]->nome);
                    auxi = pessoait;
                    while (auxi) {
                        if (strcmp(pares[i].pessoas[j]->nome, auxi->nome) == 0)
                            its->conjuntos[i].pessoas[j]->next = auxi->next;
                        auxi = auxi->next;
                    }
                }
            }
            its->lpessoa = pessoait;
            its->next = NULL;
            check = 1;
        }
        auxj = its;
        while (auxj->next != NULL) { //aqui avança ate à ultima posição 
            auxj = auxj->next;
        }
        if (auxj->next == NULL && check == 0) { //Aqui entra se ja houver um nodo e depois precisa de adicionar o proximo, o resto das intruções são iguais as de cima
            auxj->next = (pite) malloc(sizeof (ite));
            if (!auxj->next) {
                fprintf(stderr, "Erro ao alocar pessoas\n");
                return NULL;
            }

            auxj = auxj->next;
            auxj->conjuntos = malloc(sizeof (par) * tame);
            if (!auxj->conjuntos) {
                fprintf(stderr, "Erro ao alocar pessoas\n");
                return NULL;
            }
            for (int i = 0; i < tame; i++) {
                auxj->conjuntos[i].sala = pares[i].sala;
                auxj->conjuntos[i].total = pares[i].total;
                auxj->conjuntos[i].totalInfetadas = pares[i].totalInfetadas;
                auxj->conjuntos[i].pessoas = (ppessoas*) malloc(sizeof (pessoas*) * pares[i].total);
                if (!auxj->conjuntos[i].pessoas) {
                    fprintf(stderr, "Erro ao alocar pessoas\n");
                    return NULL;
                }

                for (int j = 0; j < pares[i].total; j++) {
                    auxj->conjuntos[i].pessoas[j] = (pessoas*) malloc(sizeof (pessoas));
                    if (!auxj->conjuntos[i].pessoas[j]) {
                        fprintf(stderr, "Erro ao alocar pessoas\n");
                        return NULL;
                    }
                    auxj->conjuntos[i].pessoas[j]->estado = pares[i].pessoas[j]->estado;
                    if (pares[i].pessoas[j]->estado == 'D') {
                        auxj->conjuntos[i].pessoas[j]->diasMax = pares[i].pessoas[j]->diasMax;
                        auxj->conjuntos[i].pessoas[j]->doente = pares[i].pessoas[j]->doente;
                    }
                    auxj->conjuntos[i].pessoas[j]->idade = pares[i].pessoas[j]->idade;
                    strcpy(auxj->conjuntos[i].pessoas[j]->nome, pares[i].pessoas[j]->nome);
                    auxi = pessoait;
                    while (auxi) {
                        if (strcmp(pares[i].pessoas[j]->nome, auxi->nome) == 0)
                            auxj->conjuntos[i].pessoas[j]->next = auxi->next;
                        auxi = auxi->next;
                    }
                }
            }
            auxj->lpessoa = pessoait;
            auxj->next = NULL;
        }
    } else { //Entra dentro desta condição quando o numero de iteraçoes for superior a 3, as instruçoes sao iguais as anteriores
        auxj = (pite) malloc(sizeof (ite));
        if (!auxj) {
            fprintf(stderr, "Erro ao alocar pessoas\n");
            return NULL;
        }
        auxj->conjuntos = malloc(sizeof (par) * tame);
        if (!auxj->conjuntos) {
            fprintf(stderr, "Erro ao alocar pessoas\n");
            return NULL;
        }
        for (int i = 0; i < tame; i++) {
            auxj->conjuntos[i].sala = pares[i].sala;
            auxj->conjuntos[i].total = pares[i].total;
            auxj->conjuntos[i].totalInfetadas = pares[i].totalInfetadas;
            auxj->conjuntos[i].pessoas = (ppessoas*) malloc(sizeof (pessoas*) * pares[i].total);
            if (!auxj->conjuntos[i].pessoas) {
                fprintf(stderr, "Erro ao alocar pessoas\n");
                return NULL;
            }
            for (int j = 0; j < pares[i].total; j++) {
                auxj->conjuntos[i].pessoas[j] = (pessoas*) malloc(sizeof (pessoas));
                if (!auxj->conjuntos[i].pessoas[j]) {
                    fprintf(stderr, "Erro ao alocar pessoas\n");
                    return NULL;
                }
                auxj->conjuntos[i].pessoas[j]->estado = pares[i].pessoas[j]->estado;
                if (pares[i].pessoas[j]->estado == 'D') {
                    auxj->conjuntos[i].pessoas[j]->diasMax = pares[i].pessoas[j]->diasMax;
                    auxj->conjuntos[i].pessoas[j]->doente = pares[i].pessoas[j]->doente;
                }
                auxj->conjuntos[i].pessoas[j]->idade = pares[i].pessoas[j]->idade;
                strcpy(auxj->conjuntos[i].pessoas[j]->nome, pares[i].pessoas[j]->nome);
                auxi = pessoait;
                while (auxi) {
                    if (strcmp(pares[i].pessoas[j]->nome, auxi->nome) == 0)
                        auxj->conjuntos[i].pessoas[j]->next = auxi->next;
                    auxi = auxi->next;
                }
            }
        }
        auxj->lpessoa = pessoait; 
        auxj->next = NULL;
        auxp = its; 

        while (auxp->next != NULL) // Aqui o que vai fazer é eliminar o primeiro nodo e adicionar o novo no fim
            auxp = auxp->next;
        auxp->next = auxj;
        its = its->next;

    }
    return its;
}

ite* AndaTras(ppar pares, ppessoas lista, int contit, pite its) { //Quando entra nesta função, dependendo do numero de iterações a recuar, a função irá retornar o nodo correto
    int y;
    pite aux;
    aux = its;
    do {
        printf("Quantas iteracoes deseja recuar?\n");
        scanf("%d", &y);
    } while (y > contit);
    if (contit == 1) {
        return aux;
    }
    if (contit == 2) {
        if (y == 2) {
            return aux;
        } else {
            aux = aux->next;
            return aux;
        }
    }
    if (contit >= 3) {
        if (y == 1) {
            while (aux->next != NULL)
                aux = aux->next;
            return aux;
        }
        if (y == 2) {
            aux = aux->next;
            return aux;
        }
        return aux;
    }
}

