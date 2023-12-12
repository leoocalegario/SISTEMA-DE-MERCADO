#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//funcao para vendas
float vendas(Lista *lista, int num, float total_tt)
{
    No *aux, *no = NULL;

    float preco,subtotal=0,quant;
    char nomes[26];
    int quantidade;
    long int valor; //codigo

    aux = lista->inicio;
    while(aux && aux->valor != num) //rodar todas posicoes ate achar valor do usuario
        aux = aux->proximo;

    if(aux->valor == num)
    {
        preco = aux->preco; //atribui valores da struct para variavel local
        strcpy(nomes,aux->nome);
        quantidade = aux->quantidade;
        valor = aux->valor;
    }
    printf("\n-----------");
    printf("\n\nCodigo: %ld",valor);
    printf("\nNome: %s",nomes);
    printf("\nPreco: %.2f",preco);
    printf("\nQuantidade: %d\n",quantidade);
    printf("-----------\n");


    printf("\nDigite a quantidade\n---> "); //quant para compra
    scanf("%f",&quant);

    if(quant <=0  || quant > aux->quantidade)
    {
        printf("Quantidade invalida ou insuficiente!");
    }

    if(quant >0  && quant <= aux->quantidade)
    {
        //passar valores para struct CUPOM
        aux->quantidade = aux->quantidade - quant; //Subtrair do estoque real

        //atribuindo valores para o cupom
        aux->preco_cp = preco;
        strcpy(aux->nome_cp, nomes);
        aux->qtd_cp = aux->quantidade;
        aux->valor_cp = valor;

        //valor da venda
        aux->venda = quant*preco;
        aux->qtd_venda = quant;

        subtotal = quant*preco;
        total_tt += subtotal;

        //contagem de vendas
        aux->ctg_vendas++;

        //retornar estado atual do no
        if(aux)
            no = aux;
    }

    //retornar valor total
    return total_tt;
}

//funcao para o cupom
void cupom(Lista lista)
{
    No *no = lista.inicio;
    printf("\nItens: %d\n---------\n",lista.tam);
    while(no) //rodar enquanto ser != NULL
    {
        printf("\nCodigo: %ld ", no->valor_cp);
        printf("\nNome:%s ", no->nome_cp);
        printf("\nPreco: %f ", no->preco_cp);
        printf("\nQuantidade: %d ", no->qtd_venda);
        printf("\nSubtotal: %.2f ", no->venda);
        printf("\n");
        no = no->proximo;
    }
    printf("\n\n");

}

void imprimir(Lista lista)
{
    printf("\n");
    printf("-------------");
    printf("\n");

    No *no = lista.inicio; //declaracao no struct
    printf("Itens %d\n",lista.tam);
    printf("-------------\n\n");
    while(no) //rodar enquanto ser != NULL
    {
        printf("Codigo do Produto: %ld\n", no->valor);
        printf("Nome: %s\n", no->nome);
        printf("Preco: %.2f\n", no->preco);
        printf("Quantidade: %d\n", no->quantidade);
        printf("\n");
        printf("-------------\n");
        printf("\n");
        no = no->proximo;
    }
    printf("\n\n");

}

//funcao usada para comparar valores existentes
int imprimir_existente(Lista lista, int num)
{
    No *no = lista.inicio;

    while(no)
    {
        //printf("%d ", no->valor);
        if(no->valor == num)
        {
            return 1;
        }
        no = no->proximo; //rodar proximo no
    }
}

//mostrar estoque atual
int imprimir_estoque(Lista lista)
{
    int soma;

    No *no = lista.inicio;
    printf("\nProdutos com Estoque: %d\n",lista.tam);
    printf("\n------------\n");
    while(no)
    {
        if(no->quantidade > 0)
        {
            printf("Codigo: %ld ", no->valor);
            printf("\nNome: %s ", no->nome);
            printf("\nPreco: %.2f ", no->preco);
            printf("\nEstoque: %d ", no->quantidade);
            printf("\n------------\n");
            soma += no->quantidade;
        }
        no = no->proximo;
    }
    printf("\n\n");

    return soma;
}

//exclusao de itens
No *remover(Lista *lista, int num)
{
    No *aux,*remover = NULL;

    if(lista->inicio)
    {
        if(lista->inicio->valor == num)
        {
            remover = lista->inicio;
            lista->inicio = remover->proximo;
            lista->tam--; //subtrair tamanho
        }
        else
        {
            aux = lista->inicio;
            while(aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if(aux->proximo)
            {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                lista->tam--;
            }
        }
    }


    return remover;
}

//inicializar lista
void criar_lista(Lista *lista)
{
    lista->inicio = NULL;
    lista->tam = 0;
}

//insercao no inicio da lista
void inserir_ini(Lista *lista,int num, char nomes[26], float pc, int qtds)
{
    No *novo = malloc(sizeof(No));

    novo->qtd_venda = 0;
    novo->ctg_vendas = 0;

    if(novo)
    {
        novo->valor = num; //posicao do no recebe os valores
        strcpy(novo->nome, nomes);
        novo->preco = pc;
        novo->quantidade = qtds;
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        lista->tam++;
    }
    else
        printf("\nErro ao alocar memoria");
}

//editar produtos
No *editar_cod(Lista *lista, int num)
{
    int alterar;

    No *aux;

    if(lista->inicio)
    {
        //Achar primeiro da lista OK
        if(lista->inicio->valor == num)
        {
            printf("\nDigite o valor desejado: ");
            scanf("%d",&alterar);
            lista->inicio->valor =  alterar;
        }
        else
        {
            //Achar proximo da Lista OK
            aux = lista->inicio;
            while(aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if(aux->proximo)
            {
                printf("\nDigite o valor desejado: ");
                scanf("%d",&alterar);
                aux->proximo->valor = alterar;
            }
            else
            {
                printf("\nItem nao Existe!");
            }
        }
    }
}
//editar produtos
No *editar_qtd(Lista *lista, int num)
{
    int alterar;

    No *aux;

    if(lista->inicio)
    {
        //Achar primeiro da lista OK
        if(lista->inicio->valor == num)
        {
            printf("\nDigite o valor desejado: ");
            scanf("%d",&alterar);
            lista->inicio->quantidade =  alterar;
        }
        else
        {
            //Achar proximo da Lista OK
            aux = lista->inicio;
            while(aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if(aux->proximo)
            {
                printf("\nDigite o valor desejado: ");
                scanf("%d",&alterar);
                aux->proximo->quantidade = alterar;
            }
            else
            {
                printf("\nItem nao Existe!");
            }
        }
    }
}
//editar produtos
No *editar_preco(Lista *lista, int num)
{
    float alterar;

    No *aux;

    if(lista->inicio)
    {
        //Achar primeiro da lista OK
        if(lista->inicio->valor == num)
        {
            printf("\nDigite o valor desejado: ");
            scanf("%f",&alterar);
            lista->inicio->preco =  alterar;
        }
        else
        {
            //Achar proximo da Lista OK
            aux = lista->inicio;
            while(aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if(aux->proximo)
            {
                printf("\nDigite o valor desejado: ");
                scanf("%f",&alterar);
                aux->proximo->preco = alterar;
            }
            else
            {
                printf("\nItem nao Existe!");
            }
        }
    }
}
//editar produtos
No *editar_char(Lista *lista, int num)
{
    char alterar[30];

    No *aux;

    if(lista->inicio)
    {
        //Achar primeiro da lista OK
        if(lista->inicio->valor == num)
        {
            printf("\nDigite o valor desejado: ");
            setbuf(stdin,NULL);
            gets(alterar);
            strcpy(lista->inicio->nome, alterar);
        }
        else
        {
            //Achar proximo da Lista OK
            aux = lista->inicio;
            while(aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if(aux->proximo)
            {
                printf("\nDigite o valor desejado: ");
                setbuf(stdin,NULL);
                gets(alterar);
                strcpy(aux->proximo->nome, alterar);
            }
            else
            {
                printf("\nItem nao Existe!\n");
            }
        }
    }
}
//salvar dados
int salvar_txt(Lista lista)
{

    FILE *fp;

    fp = fopen("stock.txt","w");

    if(fp == NULL)
    {
        printf("Erro na abertura do arquivo");
        return 1;
    }

    No *no = lista.inicio;

    while(no)
    {
        if(no->qtd_venda > 100)
        {
            no->qtd_venda = 0;
        }

        fprintf(fp,"%ld", no->valor);
        fprintf(fp,"\n%s", no->nome);
        fprintf(fp,"\n%f", no->preco);
        fprintf(fp,"\n%d", no->quantidade);
        fprintf(fp,"\n%d\n", no->qtd_venda);
        no = no->proximo;
    }
    fclose(fp);
}

void relatorio(Lista lista)
{
    printf("\n\n----- Relatorio de Vendas -----\n");

    No *no = lista.inicio;

    if(no->ctg_vendas>0)
    {

        while(no)
        {
            printf("\nCodigo: %ld ", no->valor_cp);
            printf("\nNome: %s ", no->nome_cp);
            printf("\nPreco: %.2f ", no->preco_cp);
            printf("\nEstoque Atual: %d ", no->quantidade);
            printf("\nEstoque Vendido: %d ", no->qtd_venda);
            printf("\nVendas Efetuadas: %d ", no->ctg_vendas);
            no = no->proximo;
            printf("\n\n");

        }
    }
    printf("---------------------------\n\n");
}

char validar_vazio(char nm[26])
{

    int k=0,j=0,c=0,d=0,y=1,l=0;

    do
    {
        printf("[%d]Digite o nome: ",y);
        setbuf(stdin,NULL); //limpar buf
        gets(nm);

        //validar se eh so espaco
        for(c=0; c<26; c++)
        {
            if(nm[c] != NULL)
            {
                k++;
            }
        }

        for(d=0; d<k; d++)
        {

            if(nm[d] == ' ')
            {
                j++;
            }

        }
        if(j == k)
        {
            printf("\nNome invalido!\n"); //Caso seja apenas espaco
        }
        else
            break;
    }
    while(j == k);

    return nm;
}
