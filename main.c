#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    long int valor; //codigo
    int opc,opc_2, qtd_usuario=0,parcelas=0;
    int y=1,l=0; //Utilizados para validar se o char esta vazio
    int total_aux=0,quantidade,soma_estoque;
    int receber=0; //utilizado para validar se o cod existe
    float total = 0,preco;
    char nm[26] = "";

    FILE *fp; //declarar ponteiro para arquivo

    //Variaveis para leitura e salvamento do arquivo
    long int fvalor;
    int fqtd, fqtd_venda;
    float fpreco;
    char fnome[26];

    Lista lista; //declaracao struct

    No *removido; //Atribui No para ponteiro
    No *aux; //Atribui No para ponteiro
    criar_lista(&lista); //Inicializar lista encadeada com null

    do
    {
        printf("\n( 1 ) - Produtos\n( 2 ) - Vendas\n( 0 ) - Sair\n--->");
        scanf("%d",&opc); //Menu principal

        switch(opc)
        {
        //----------------------IMPRIMIR-------------------
        case 1:
            do
            {
                //Submenu
                printf("\n1 - Exibir\n2 - Cadastrar\n3 - Atualizar\n4 - Excluir\n5 - Salvar\n6 - Ler\n0 - Voltar\n--->");
                scanf("%d",&opc_2);
                switch(opc_2)
                {

                case 1:
                    if(lista.tam <= 0) //Se nao houver produtos:
                    {
                        printf("Vazio...\n");
                        break;
                    }
                    imprimir(lista); //impressao de todos os produtos
                    break;
                //----------------CADASTRAR----------------
                case 2:
                    printf("Deseja cadastrar quantos produtos?\n---> ");
                    scanf("%d",&qtd_usuario);
                    for(int i=0; i<qtd_usuario; i++) //for para rodar a qtd que o usuario digitou
                    {
                        do
                        {
                            printf("\n");
                            printf("[%d]Digite o codigo: ",y); //y para printar ao usuario qual posicao esta
                            scanf("%ld",&valor);
                            receber = imprimir_existente(lista, valor); //funcao usada para validar existente
                            if(receber > 0)
                            {
                                printf("\nCodigo Existente!\n"); //if para validar se o cod existe
                            }
                        }
                        while(receber > 0);

                        //captar string
                        validar_vazio(nm);

                        do
                        {
                            printf("[%d]Digite o preco: ",y);
                            scanf("%f",&preco);
                            if(preco <=0)
                            {
                                printf("\nValor incorreto!\n"); //Validar se o preco for negativo ou 0
                            }
                        }
                        while(preco <= 0);

                        do
                        {
                            printf("[%d]Digite a qtd: ",y);
                            scanf("%d",&quantidade);
                            if(quantidade <=0)
                            {
                                printf("\nValor incorreto!\n"); //Validar se a qtd for negativo ou 0
                            }
                        }
                        while(quantidade<=0);
                        y++;
                        inserir_ini(&lista,valor,nm,preco,quantidade); //funcao para inserir os valores no inicio da lista
                    }
                    y=1;
                    break;
                //--------------ATUALIZAR----------------
                case 3:
                    if(lista.tam<=0)
                    {
                        printf("Vazio...\n"); //Se n houver itens
                        break;
                    }

                    do
                    {
                        receber = 0; //incializar receber 0 para garantir q n haja lixo
                        imprimir(lista);
                        printf("Digite o codigo do produto que deseja atualizar: ");
                        scanf("%d",&valor);
                        receber = imprimir_existente(lista, valor); //verificar se cod existe

                        if(receber == 1) // se existir
                        {
                            do
                            {
                                printf("O que deseja atualizar?\n1 - Codigo\n2 - Nome\n3 - Preco\n4 - Quantidade\n---> ");
                                scanf("%d",&opc);

                                switch(opc)
                                {

                                case 1:
                                    editar_cod(&lista,valor);
                                    break;

                                case 2:
                                    editar_char(&lista,valor);
                                    break;

                                case 3:
                                    editar_preco(&lista,valor);
                                    break;

                                case 4:
                                    editar_qtd(&lista,valor);
                                    break;
                                }
                            }
                            while(opc == 'n'); //propositalmente para n ter como sair
                            break;

                        }
                        else
                        {
                            printf("Produto Nao encotrado\n");
                        }
                    }
                    while(valor == aux);

                    break;
                //-----------------REMOVER---------------
                case 4:
                    if(lista.tam <= 0)
                    {
                        printf("Vazio...\n"); //validar se ha produtos
                        break;
                    }
                    imprimir(lista); //impressao dos itens
                    printf("Digite o Codigo desejado:\n---> ");
                    scanf("%d",&valor);
                    printf("\nElemento a ser removido: %d\nDeseja continuar?\n( 1 ) - Sim\n( 2 ) - Nao\n---> ",valor);
                    scanf("%d",&opc);
                    if(opc == 1)
                    {
                        removido = remover(&lista,valor); //remover recebe item removido
                        if(removido)
                        {
                            printf("\nElemento Removido ( %ld )",removido->valor); //printando item removido
                            free(removido);
                        }
                        else
                            printf("\nCodigo Inexistente");
                    }
                    else
                    {
                        printf("Operacao Cancelada..."); //caso o usuario digite nao
                        break;
                    }
                    break;
                //-------------------SALVAR-----------------
                case 5:
                    if(lista.tam <= 0)
                    {
                        printf("Vazio...\n");
                        break;
                    }
                    salvar_txt(lista); //salvar itens no txt
                    break;
                //-------------------LER---------------------
                case 6:
                    fp = fopen("stock.txt","r");

                    if(fp == NULL)
                    {
                        printf("Erro na abertura do arquivo");
                        return 1;
                    }

                    printf("Vai ler quantos Produtos?"); //Deixar dinamico
                    scanf("%d",&l);
                    for(int i=0; i<l; i++) //DEIXAR DINAMICO
                    {
                        fscanf(fp,"%ld\n%s\n%f\n%d\n%d\n",&fvalor,&fnome,&fpreco,&fqtd,&fqtd_venda); //leitura fixa
                        inserir_ini(&lista,fvalor,fnome,fpreco,fqtd); //cadastrar itens lidos
                    }

                    fclose(fp);
                    if(lista.tam <= 0)
                    {
                        printf("Vazio...\n");
                        break;
                    }
                    break;

                case 0:
                    break;

                default:

                    printf("\nOpc invalida!\n");
                    break;
                }

            }
            while(opc_2 != 0);
            break;

        case 2:
            printf("\n1 - Vender\n2 - Relatorio de Vendas\n0 - Voltar");
            scanf("%d",&opc_2);

            if(opc_2 == 1)
            {
                do
                {
                    soma_estoque = imprimir_estoque(lista); //Se o estoque for 0, n tem produto pra vender
                    if(soma_estoque > 0)
                    {
                        printf("Digite o codigo do item desejado para a venda\n---> ");
                        scanf("%d",&valor);
                        receber = imprimir_existente(lista, valor);
                        do
                        {
                            if(receber == 0)
                            {
                                printf("Digite um codigo valido!");
                                scanf("%d",&valor);
                                receber = imprimir_existente(lista, valor); //do para caso digite um valor incorreto
                            }
                        }
                        while(receber != 1);
                        total = vendas(&lista,valor,total); //total recebe da funcao
                    }
                    else
                    {
                        printf("\nNao ha estoque suficiente para vender!");
                    }
                    printf("\nDeseja continuar vendendo?");
                    printf("\n( 1 ) - Sim\n( 0 ) - Nao\n---> ");
                    scanf("%d",&opc);
                }
                while(opc != 0);
                //-------------TIPOS DE PAGAMENTO-----------
                do
                {
                    printf("\nComo deseja pagar?\n( 1 ) - A vista\n( 2 ) - Parcelado\n---> ");
                    scanf("%d",&opc);

                    if(opc != 1 && opc !=2)
                        printf("\nDigite uma opc Valida!");
                }
                while(opc != 1 && opc != 2);

                switch(opc)
                {
                case 1:
                    if(total >0 && total <=50)
                    {
                        total_aux = total*0.05;
                        total = total - total_aux;
                        //CUPOM FISCAL
                        printf("\n-----Cupom Fiscal-----");
                        cupom(lista);
                        printf("----------\n");
                        printf("5%% Desconto\n");
                        printf("\nTotal ---> %.2f\n",total);
                    }
                    if(total >50 && total <=100)
                    {
                        total_aux = total*0.10;
                        total = total - total_aux;
                        //CUPOM FISCAL
                        printf("\n-----Cupom Fiscal-----\n");
                        cupom(lista);
                        printf("----------\n");
                        printf("10%% Desconto\n");
                        printf("\nTotal ---> %.2f\n",total);
                    }
                    if(total >=100)
                    {
                        total_aux = total*0.18;
                        total = total - total_aux;
                        //CUPOM FISCAL
                        printf("\n-----Cupom Fiscal-----");
                        cupom(lista);
                        printf("----------\n");
                        printf("18%% Desconto\n");
                        printf("\nTotal ---> %.2f\n",total);
                    }
                    total = 0,total_aux=0;
                    break;

                case 2:

                    printf("\nDigite o numero de parcelas\n---> ");
                    scanf("%d",&parcelas);

                    while(parcelas <=0)
                    {
                        if(parcelas<=0)
                        {
                            printf("\nValor invalido! \nDigite novamente\n---> ");
                            scanf("%d",&parcelas);
                        }
                    }
                    if(parcelas <=3)
                    {
                        total = total*1.05;
                        //CUPOM FISCAL
                        printf("\n-----Cupom Fiscal-----");
                        cupom(lista);
                        printf("----------\n");
                        printf("3%% juros\n");
                        printf("\nTotal ---> %.2f\n",total);
                    }
                    if(parcelas >3)
                    {
                        total = total*1.08;
                        //CUPOM FISCAL
                        printf("\n-----Cupom Fiscal-----");
                        cupom(lista);
                        printf("----------\n");
                        printf("8%% juros\n");
                        printf("\nTotal ---> %.2f\n",total);
                    }
                    total = 0,total_aux=0;

                    break;

                default:
                    printf("\nDigite um valor valido!\n");
                    break;
                }
                opc = 1;
            }

            if(opc_2 == 2)
            {
                relatorio(lista);//funcao relatorio
            }
            if(opc_2 == 0)
            {
                break;
            }
            break;


        default:
            if(opc != 0 )
            {
                printf("\nOpc invalida!\n");
            }
            break;
        }
    }
    while(opc != 0);

    return 0;
}
