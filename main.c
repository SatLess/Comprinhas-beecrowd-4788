#include <stdio.h>
#include <string.h>
#define MAX 1000

struct produto {

  char nome[101];
  int qtd;
  double preco;
};

typedef struct produto Prod;

// Variaveis Globais
double budgetInicial;
double budgetAtual;
double precoTotal = 0;
Prod carrinho[MAX];
int idx = 0;

void scanInfoRemoveProduct(char nome[101], int *qtdRemover) {
  scanf("%s %d", nome, qtdRemover);
  getchar();
}

void debugPrint(int idx) {
  printf("%s %d x %lf, idx %d, dinero: %lf\n", carrinho[idx].nome,
         carrinho[idx].qtd, carrinho[idx].preco, idx, precoTotal);
}

// retorna Idx do produto
int checarExistênciaProduto(char nome[101]) {
  for (int i = 0; i < MAX; i++) {
    if (strcmp(carrinho[i].nome, nome) == 0) {
      return i;
    }
  }
  return -1;
}

void comprarProduto() {

  char nome[101];
  int qtd;
  double preco;

  scanf("%s %lf %d", nome, &preco, &qtd);
  getchar();

  //se o preco total for maior que seu orcamento, apenas incluir o maximo de itens possivel
  if (precoTotal+(qtd * preco) > budgetInicial) {
    qtd = (budgetInicial-precoTotal) / preco;
  }
  if (qtd > 0) {
    precoTotal += qtd * preco;
  }

  // Primeiro, checamos se existe um mesmo produto já na lista, caso não, o
  // criamos.
  int existe = checarExistênciaProduto(nome);

  if (existe >= 0) {
    carrinho[existe].qtd += qtd;
    debugPrint(existe);
    return;
  }

  Prod newProduto;
  strcpy(carrinho[idx].nome, nome);
  carrinho[idx].preco = preco;
  carrinho[idx].qtd = qtd;
  debugPrint(idx);
  ++idx;
}

void removerProduto(char nome[], int qtdRemover) {

  int existe = checarExistênciaProduto(nome);
  if (existe == -1 || carrinho[existe].qtd == 0) {
    printf("ERRO: O produto %s nao esta no carrinho\n", nome);
    return;
  }

  if (qtdRemover > carrinho[existe].qtd) {
    //Faco ressarcimento total do valor
    precoTotal -= carrinho[existe].qtd * carrinho[existe].preco;
    carrinho[existe].qtd = 0;
  } else {
    //Faco ressarcimento apenas dos itens removidos
    precoTotal -= qtdRemover * carrinho[existe].preco;
    carrinho[existe].qtd -= qtdRemover;
  }

  debugPrint(existe);
}

void atualizarPreco(){
  char nome[101];
  int precoNovo;
  scanf("%s %d", nome,&precoNovo);
  getchar();

  int existe = checarExistênciaProduto(nome);
  if (existe == -1 || carrinho[existe].qtd == 0) {
    printf("ERRO: O produto %s nao esta no carrinho\n", nome);
    return;}

  //Remove valor dado a ele durante a compra
  precoTotal -= carrinho[existe].qtd*carrinho[existe].preco;

  
  carrinho[existe].preco = precoNovo;
  //Caso msm assim, o total seja maior que orçamento, diminua a qtd
   while(precoTotal+(carrinho[existe].qtd*precoNovo) >budgetInicial){--carrinho[existe].qtd;}

  //Adicione o preco certo agr
  precoTotal += carrinho[existe].qtd*carrinho[existe].preco;

  debugPrint(existe);
  
}

void scanOperation() {
  char s;
  scanf("%c", &s);
  getchar();

  if (s == 'C') {
    comprarProduto();
  }
  if (s == 'R') {
    char nome[101];
    int qtdRemover;
    scanInfoRemoveProduct(nome, &qtdRemover);
    removerProduto(nome, qtdRemover);
  }
  if(s=='A'){atualizarPreco();}
}

int main(void) {

  int numOperações;

  scanf("%d %lf", &numOperações, &budgetInicial);
  getchar();
  budgetAtual = budgetInicial;

  for (int i = 0; i < numOperações; i++) {
    scanOperation();
  }

  return 0;
}