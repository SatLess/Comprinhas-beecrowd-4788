  #include <stdio.h>
  #include <string.h>
  #define MAX 1000

  struct produto{

    char nome[101];
    int qtd;
    double preco;
  };

  typedef struct produto Prod;

  //Variaveis Globais
  double budgetInicial;
  double budgetAtual;
  Prod carrinho[MAX];
  int idx = 0;
  

  void debugPrint(int idx){
    printf("%s %d x %lf, idx %d, dinero: %lf\n", carrinho[idx].nome,
       carrinho[idx].qtd, carrinho[idx].preco, idx, budgetAtual);
  }

  //retorna Idx do produto
  int checarExistênciaProduto(char nome[101]){
    for(int i = 0; i<MAX;i++){
      if(strcmp(carrinho[i].nome, nome) == 0){return  i;}
    }
    return -1;
  }

  void comprarProduto() {

    char nome[101];
    int qtd;
    double preco;

    scanf("%s %lf %d", nome, &preco,&qtd);
    getchar();

    if (qtd * preco > budgetAtual) {
      qtd = budgetAtual / preco;
    }
    if (qtd > 0) {
      budgetAtual -= qtd * preco;
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

  void removerProduto(){
    char nome[101];
    int qtdRemover;
    scanf("%s %d",nome,&qtdRemover);
    getchar();
    int existe = checarExistênciaProduto(nome);
    if(existe == -1){
      printf("ERRO: O produto %s nao esta no carrinho\n",nome);
      return;}


    if(qtdRemover>carrinho[existe].qtd){
      budgetAtual += carrinho[existe].qtd * carrinho[existe].preco;
      carrinho[existe].qtd = 0;
    }
    else{
      budgetAtual += qtdRemover*carrinho[existe].preco;
      carrinho[existe].qtd -= qtdRemover;}
  
    debugPrint(existe);
  }

  void scanOperation(){
    char s;
    scanf("%c",&s);
    getchar();

    if(s=='C'){comprarProduto();}
    if(s=='R'){removerProduto();}
  }


  int main(void) {

    int numOperações;

    scanf("%d %lf",&numOperações,&budgetInicial);
    getchar();
    budgetAtual = budgetInicial;

    for(int i = 0; i<numOperações;i++){scanOperation();}

    return 0;
    }