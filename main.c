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

      void trocar(Prod *i, Prod *j) {

        Prod key;
        strcpy(key.nome, i->nome);
        key.preco = i->preco;
        key.qtd = i->qtd;

        strcpy(i->nome, j->nome);
        i->preco = j->preco;
        i->qtd = j->qtd;

        strcpy(j->nome, key.nome);
        j->preco = key.preco;
        j->qtd = key.qtd;
      }

      void scanInfoRemoveProduct(char nome[101], int *qtdRemover) {
        scanf("%s %d", nome, qtdRemover);
        getchar();
      }

      void debugPrint(int idx) {

        printf("%s %d x %.2lf = %.2lf\n",carrinho[idx].nome,carrinho[idx].qtd,carrinho[idx].preco,
            (carrinho[idx].qtd * carrinho[idx].preco));
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

        // se o preco total for maior que seu orcamento, apenas incluir o maximo de
        // itens possivel
        if (precoTotal + (qtd * preco) > budgetInicial) {
          qtd = (budgetInicial - precoTotal) / preco;
        }
        if (qtd > 0) {
          precoTotal += qtd * preco;
        }

        // Primeiro, checamos se existe um mesmo produto já na lista, caso não, o
        // criamos.
        int existe = checarExistênciaProduto(nome);

        if (existe >= 0) {
          carrinho[existe].qtd += qtd;
          // debugPrint(existe);
          return;
        }

        Prod newProduto;
        strcpy(carrinho[idx].nome, nome);
        carrinho[idx].preco = preco;
        carrinho[idx].qtd = qtd;
        // debugPrint(idx);
        ++idx;
      }

      void removerProduto(char nome[], int qtdRemover) {

        int existe = checarExistênciaProduto(nome);
        if (existe == -1 || carrinho[existe].qtd == 0) {
          printf("ERRO: O produto %s nao esta no carrinho\n", nome);
          return;
        }

        if (qtdRemover > carrinho[existe].qtd) {
          // Faco ressarcimento total do valor
          precoTotal -= carrinho[existe].qtd * carrinho[existe].preco;
          carrinho[existe].qtd = 0;
        } else {
          // Faco ressarcimento apenas dos itens removidos
          precoTotal -= qtdRemover * carrinho[existe].preco;
          carrinho[existe].qtd -= qtdRemover;
        }

        // debugPrint(existe);
      }

      void atualizarPreco() {
        char nome[101];
        double precoNovo;
        scanf("%s %lf", nome, &precoNovo);
        getchar();

        int existe = checarExistênciaProduto(nome);
        if (existe == -1 || carrinho[existe].qtd == 0) {
          printf("ERRO: O produto %s nao esta no carrinho\n", nome);
          return;
        }

        // Remove valor dado a ele durante a compra
        precoTotal -= carrinho[existe].qtd * carrinho[existe].preco;

        carrinho[existe].preco = precoNovo;
        // Caso msm assim, o total seja maior que orçamento, diminua a qtd
        while (precoTotal + (carrinho[existe].qtd * precoNovo) > budgetInicial) {
          --carrinho[existe].qtd;
        }

        // Adicione o preco certo agr
        precoTotal += carrinho[existe].qtd * carrinho[existe].preco;

        // debugPrint(existe);
      }

      void mostrar() {
        if (idx == 0)
          return;

        for (int i = 0; i < idx; i++) {
          for (int j = i + 1; i < idx; i++) {

              if(strlen(carrinho[j].nome)==0){break;}

            if (strcmp(carrinho[i].nome, carrinho[j].nome) > 0) {
              trocar(&carrinho[i], &carrinho[j]);
            }
          }
        }

        for (int i = 0; i < idx; i++) {
          if (carrinho[i].qtd == 0 || strlen(carrinho[i].nome) == 0) {
            continue;
          }
          debugPrint(i);
        }
          printf("TOTAL: %.2lf\n",precoTotal);
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
        if (s == 'A') {
          atualizarPreco();
        }
        if (s == 'M') {
          mostrar();
        }
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