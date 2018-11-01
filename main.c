#include <stdio.h>
#include <stdlib.h>
#define MAX 3

struct Estacionamento
{
    int vaga[MAX];
    int inicio;
    int fim;

};

struct PilhaRetirarCarro
{
    int topo;
    int dados[MAX];

};

int menuRemover();

void listaDeCarros(struct Estacionamento *estacionamento,struct Estacionamento *filaespera);



void inserirNoEstacionamento(struct Estacionamento *f1, int PlacaX);

int menuChegouCarro(struct Estacionamento *f2,int Placay);

void menu();

int inserirFilaDeEspera(int PlacaZ,struct Estacionamento *espera);

void InserirNaPilha(int PlacaM,struct PilhaRetirarCarro *p1);

int removerComTrocaFila(struct Estacionamento *f5,int *PlacaK);

int removerDaPilha(struct PilhaRetirarCarro *p2);

int cheia (struct Estacionamento *fila);


int main()
{

    char opc;
    int Placa;

    struct Estacionamento estacionamento;
    estacionamento.fim=0;
    estacionamento.inicio=0;

    struct Estacionamento filaEspera;
    filaEspera.fim=0;
    filaEspera.inicio=0;

    struct Estacionamento movimento;
    movimento.fim=0;
    movimento.inicio=0;

    struct PilhaRetirarCarro pilha;
    pilha.topo=-1;

    struct PilhaRetirarCarro pilhaMovimentos;
    pilhaMovimentos.topo=-1;


    do
    {
        system("cls");
        menu();
        scanf("%s",&opc);

        if(opc=='C' || opc=='c')
        {
            printf("Digite a placa do carro\n");
            scanf("%d",&Placa);

            int i,ok,flag,retornoFuncao,j;
            for(j=0; j<=1; j++)
            {
                //Testando placa no estacionamento

                do
                {
                    ok=0;
                    for(i=0; i<estacionamento.fim; i++)
                    {
                        if(estacionamento.vaga[i]==Placa)
                        {
                            do
                            {
                                printf("Esta placa ja esta registrada\nDigite outra placa\n\n");
                                scanf("%d",&Placa);
                                ok=1;
                            }
                            while(estacionamento.vaga[i]==Placa);
                        }
                    }
                    flag=0;
                }
                while(ok==1);

                //Testando placa na fila de espera
                if(flag==0)
                {
                    do
                    {
                        ok=0;
                        for(i=0; i<filaEspera.fim; i++)
                        {
                            if(filaEspera.vaga[i]==Placa)
                            {
                                do
                                {
                                    printf("Esta placa ja esta registrada\nDigite outra placa\n\n");
                                    scanf("%d",&Placa);
                                    ok=1;
                                }
                                while(estacionamento.vaga[i]==Placa);
                            }
                        }
                    }
                    while(ok==1);
                }
            }
            retornoFuncao=menuChegouCarro(&estacionamento,Placa);

            if(retornoFuncao==1)
            {
                inserirNoEstacionamento(&estacionamento,Placa);
                printf("\n\nChegou um carro!!\n");
                printf("Carro foi estacionado\n\n\n");
                system("pause");
                movimento.vaga[movimento.fim]=0;
                movimento.fim++;
            }
            else if(retornoFuncao==2)
            {

            }
            else if(retornoFuncao==3)
            {
                inserirFilaDeEspera(Placa,&filaEspera);
                system("pause");
            }
            else
            {

            }

        }
        else if(opc=='p' || opc=='P')
        {

            int verificar=cheia(&estacionamento);
            int pegar=menuRemover();
            if(pegar==1)
            {
                if(verificar!=2)
                {

                    printf("Qual a placa do carro?\n");
                    scanf("%d",&Placa);


                    int con=0;
                    int saiuDaFilaDeEspera;

                    int estacCheio=cheia(&estacionamento);
                    int filaEsperaComCarros=cheia(&filaEspera);

                    if(estacCheio==1 && filaEsperaComCarros!=2)
                    {
                        do
                        {
                            if(estacionamento.vaga[0]==Placa)
                            {
                                int guarda=removerComTrocaFila(&movimento,&movimento.vaga[0]);
                                removerComTrocaFila(&estacionamento,&Placa);
                                printf("O carro com a placa %d foi retirado\n\n",Placa);
                                printf("O carro fez %d movimentos\n\n",guarda);
                                system("pause");
                            }
                            else
                            {
                                InserirNaPilha(estacionamento.vaga[0],&pilha);
                                InserirNaPilha(movimento.vaga[0],&pilhaMovimentos);
                                removerComTrocaFila(&estacionamento,&estacionamento.vaga[0]);
                                removerComTrocaFila(&movimento,&movimento.vaga[0]);
                                int CarroVolto=removerDaPilha(&pilha);
                                int movimentoVolto=removerDaPilha(&pilhaMovimentos);
                                inserirNoEstacionamento(&estacionamento,CarroVolto);
                                inserirNoEstacionamento(&movimento,(movimentoVolto+=1));
                            }
                            con++;
                        }
                        while(con<=estacionamento.fim);

                        saiuDaFilaDeEspera=removerComTrocaFila(&filaEspera,&filaEspera.vaga[0]);
                        inserirNoEstacionamento(&estacionamento,saiuDaFilaDeEspera);
                        movimento.vaga[movimento.fim]=0;
                        movimento.fim++;

                    }
                    else
                    {
                        do
                        {
                            if(estacionamento.vaga[0]==Placa)
                            {
                                int guarda=removerComTrocaFila(&movimento,&movimento.vaga[0]);
                                removerComTrocaFila(&estacionamento,&estacionamento.vaga[0]);
                                printf("O carro com a placa %d foi removido\n\n",Placa);
                                printf("O carro fez %d movimentos\n\n",guarda);
                                system("pause");

                            }
                            else
                            {
                                InserirNaPilha(estacionamento.vaga[0],&pilha);
                                InserirNaPilha(movimento.vaga[0],&pilhaMovimentos);
                                removerComTrocaFila(&estacionamento,&estacionamento.vaga[0]);
                                removerComTrocaFila(&movimento,&movimento.vaga[0]);
                                int CarroVolto=removerDaPilha(&pilha);
                                int movimentoVolto=removerDaPilha(&pilhaMovimentos);
                                inserirNoEstacionamento(&estacionamento,CarroVolto);
                                inserirNoEstacionamento(&movimento,(movimentoVolto+=1));
                            }
                            con++;
                        }
                        while(con<=estacionamento.fim);
                    }

                }
                else
                {
                    printf("Estacionamento ta vazio\n");
                    system("pause");
                }
            }
            else
            {
                int verificar=cheia(&filaEspera);
                if(verificar!=2)
                {

                    printf("Qual a placa do carro?\n");
                    scanf("%d",&Placa);

                    int con=0;
                    do
                    {
                        if(filaEspera.vaga[0]==Placa)
                        {
                            removerComTrocaFila(&filaEspera,&filaEspera.vaga[0]);
                            printf("O carro com a placa %d foi removido\n\n",Placa);
                            system("pause");

                        }
                        else
                        {
                            InserirNaPilha(filaEspera.vaga[0],&pilha);
                            removerComTrocaFila(&filaEspera,&filaEspera.vaga[0]);
                            int CarroVolto=removerDaPilha(&pilha);
                            inserirNoEstacionamento(&filaEspera,CarroVolto);
                        }
                        con++;
                    }while(con<=filaEspera.fim);

                }else{
                    printf("Fila de espera vazia\n");
                    system("pause");
                }
            }
        }
        else if(opc=='l' || opc=='L')
        {
            listaDeCarros(&estacionamento,&filaEspera);
        }
    }
    while(opc!='S' && opc!='s');

    return 0;
}

//O CARRO CHEGOU
int menuChegouCarro(struct Estacionamento *f2,int Placay)
{
    system("cls");
    int opc;

    int verificar=cheia(&(*f2));

    if(verificar!=1)
    {
        printf("\nHa vagas no estaciomento!!!\n\n");
        printf("*********************************\n");
        printf("     Deseja estacionar o carro?  \n");
        printf("1-SIM                            \n");
        printf("2-NAO                            \n");
        printf("*********************************\n");
        scanf("%d",&opc);
        if(opc==1)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        printf("\nNao ha vagas no estacionamento!!!!\n\n");
        printf("****************************************************\n");
        printf("      Deseja colocar o carro na fila de espera?     \n");
        printf("1-SIM                                               \n");
        printf("2-NAO                                               \n");
        printf("****************************************************\n");
        scanf("%d",&opc);
        if(opc==1)
        {
            return 3;
        }
        else
        {
            return 4;
        }
    }

}

void inserirNoEstacionamento(struct Estacionamento *f1, int PlacaX)
{

    system("cls");

    if((*f1).fim==MAX)
    {
        printf("O estacionamento está cheio\n");
        system("pause");
    }
    else
    {
        (*f1).vaga[(*f1).fim]=PlacaX;
        (*f1).fim++;
    }
}

int inserirFilaDeEspera(int PlacaZ,struct Estacionamento *espera)
{

    if((*espera).fim==MAX)
    {
        return 0;
    }
    else
    {
        (*espera).vaga[(*espera).fim]=PlacaZ;
        (*espera).fim++;
        return 1;
    }

}

int removerComTrocaFila(struct Estacionamento *f5,int *PlacaK)
{

    if((*f5).inicio==(*f5).fim)
    {
        return 0;
    }
    else
    {
        int a=0;
        if(a==0)
        {
            *PlacaK=(*f5).vaga[(*f5).inicio];
            a=*PlacaK;
        }
        for(int i=0; i<MAX-1; i++)
        {
            (*f5).vaga[i]=(*f5).vaga[i+1];
        }
        (*f5).fim--;
        return a;
    }

}

int cheia (struct Estacionamento *fila)
{
    if((*fila).fim==MAX)
    {
        return 1;
    }
    else if((*fila).fim==0)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void menu()
{
    printf("C- Chegou um carro\n");
    printf("P- Retirar carro do estacionamento\n");
    printf("L- Lista de carros estacionados\n");
    printf("S- Sair\n");
}

void InserirNaPilha(int PlacaM,struct PilhaRetirarCarro *p1)
{

    system("cls");
    (*p1).dados[(++(*p1).topo)]=PlacaM;

}

int removerDaPilha(struct PilhaRetirarCarro *p2)
{

    return((*p2).dados[(*p2).topo--]);
}

void listaDeCarros(struct Estacionamento *estacionamento,struct Estacionamento *filaespera)
{

    printf("Lista de carros no estacionamento: \n");
    int i;
    for(i=0; i<(*estacionamento).fim; i++)
    {
        printf("%d ",(*estacionamento).vaga[i]);
    }
    printf("\n\n");

    if((*filaespera).fim==0)
    {
        printf("Fila de espera esta vazia\n\n");
        system("pause");
    }
    else
    {
        printf("\nCarros na fila de espera:\n");
        for(i=0; i<(*filaespera).fim; i++)
        {
            printf("%d ",(*filaespera).vaga[i]);
        }
        printf("\n\n");
        system("pause");
    }

}

int menuRemover()
{

    system("cls");
    printf("Deseja remover de qual estacionamento?\n");
    printf("1-Para remover do estacionamento\n");
    printf("2-Para remover da fila de espera\n");
    int opc;
    scanf("%d",&opc);

    if(opc==1)
    {
        return 1;
    }
    else
    {
        return 2;
    }

}
