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


void comprarProduto(Prod Carrinho[], int * idx){

  char nome[101];
  int qtd;
  double preco;

  scanf("%s %d %lf",nome,&qtd,&preco);
  
  //Primeiro, checamos se existe um mesmo produto já na lista, caso não, o criamos.
  int existe = checarExistênciaProduto(Carrinho, nome);
    
  if(existe >= 0){ 
    Carrinho[existe].qtd+=qtd;
    printf("%s %d x %lf, idx %d\n",Carrinho[existe].nome,Carrinho[existe].qtd,Carrinho[existe].preco,existe);
    return;
  }

  Prod newProduto;
  strcpy(Carrinho[*idx].nome, nome);
  Carrinho[*idx].preco = preco;
  Carrinho[*idx].qtd = qtd;

  printf("%s %d x %lf, idx %d\n",Carrinho[*idx].nome,Carrinho[*idx].qtd,Carrinho[*idx].preco,*idx);
    
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

  for(int i = 0; i<numOperações;i++){comprarProduto(carrinho, &idx);}
  
  return 0;
}