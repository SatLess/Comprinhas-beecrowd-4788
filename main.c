#include <stdio.h>
#include <string.h>
#define MAX 1000

struct produto{

  char nome[101];
  int qtd;
  double preco;

};

typedef struct produto Prod;

//retorna Idx do produto
int checarExistênciaProduto(Prod Carrinho[], char nome[101]){
  for(int i = 0; i<MAX;i++){
    if(strcmp(Carrinho[i].nome, nome) == 0){return  i;}
  }
  return -1;
}

void comprarProduto(Prod Carrinho[], int *idx, double *budget) {

  char nome[101];
  int qtd;
  double preco;

  scanf("%s %d %lf", nome, &qtd, &preco);

  if (qtd * preco > *budget) {
    qtd = *budget / preco;
    printf("%d", qtd);
  }
  if (qtd > 0) {
    *budget -= qtd * preco;
  }

  // Primeiro, checamos se existe um mesmo produto já na lista, caso não, o
  // criamos.
  int existe = checarExistênciaProduto(Carrinho, nome);

  if (existe >= 0) {
    Carrinho[existe].qtd += qtd;
    printf("%s %d x %lf, idx %d, dinero: %lf\n", Carrinho[existe].nome,
           Carrinho[existe].qtd, Carrinho[existe].preco, existe, *budget);
    return;
  }

  Prod newProduto;
  strcpy(Carrinho[*idx].nome, nome);
  Carrinho[*idx].preco = preco;
  Carrinho[*idx].qtd = qtd;

  printf("%s %d x %lf, idx %d, dinero: %lf\n", Carrinho[*idx].nome,
         Carrinho[*idx].qtd, Carrinho[*idx].preco, *idx, *budget);

  ++*idx;
}

int main(void) {

  int numOperações;
  double budgetInicial;
  double budgetAtual;
  char operação;

  Prod carrinho[MAX];
  int idx = 0;

  scanf("%d %lf",&numOperações,&budgetInicial);
  budgetAtual = budgetInicial;

  for(int i = 0; i<numOperações;i++){comprarProduto(carrinho, &idx,&budgetAtual);}

  return 0;
  }