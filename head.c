#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

typedef struct {
  int ebomba;
  int aberta;
  int vizinhos;
}
campo;

campo mat[10][20]; //declaração da matriz com campos da struct "campo"

int l, c; //inteiros que assumirão valores de linha e coluna para comparações

void inicializar(int lin, int col,campo mat[lin][col]) { // inicializa a matriz "setando" todos os dados à zero
  for (l = 1; l <= 10; l++) {
    for (c = 1; c <= 20; c++) {
      mat[l][c].ebomba = 0;
      mat[l][c].aberta = 0;
      mat[l][c].vizinhos = 0;
    }
  }
}

void sortearbombas() { //sorteia as bombas aleatoriamente 
  int i;
  srand(time(NULL));
  for (i = 0; i < 40; i++) {
    l = rand() % 10;
    c = rand() % 20;
    if (mat[l][c].ebomba == 0) { //setando campos vazios selecionados como bomba
      mat[l][c].ebomba = 1;
    } else { //voltando com subtração do i em caso a posição já tenha sido escolhida
      i--;
    }
  }
}

int coordval(int l, int c) { //verifica se a coordenada está dentro do limite da matriz e retora 1 para verdadeiro e 0 para falso
  if (l >= 1 && l <= 10 && c >= 1 && c <= 20) {
    return 1;
  } else {
    return 0;
  }
}

int qntbombasvizinhas(int l, int c) { //função que verifica as posições visinhas e retorna o numero de bombas presentes nas 8 casas ao seu redor
  int quantidade = 0;

  if (coordval(l - 1, c) && mat[l - 1][c].ebomba) {
    quantidade++;
  }
  if (coordval(l + 1, c) && mat[l + 1][c].ebomba) {
    quantidade++;
  }
  if (coordval(l, c - 1) && mat[l][c - 1].ebomba) {
    quantidade++;
  }
  if (coordval(l, c + 1) && mat[l][c + 1].ebomba) {
    quantidade++;
  }
  if (coordval(l + 1, c + 1) && mat[l + 1][c + 1].ebomba) {
    quantidade++;
  }
  if (coordval(l - 1, c - 1) && mat[l - 1][c - 1].ebomba) {
    quantidade++;
  }
  if (coordval(l + 1, c - 1) && mat[l + 1][c - 1].ebomba) {
    quantidade++;
  }
  if (coordval(l - 1, c + 1) && mat[l - 1][c + 1].ebomba) {
    quantidade++;
  }
  return quantidade;
}

void contbombas() { //função que seta na posição da matriz e no campo "vizinhos" o numero de bombas ao redor 
  for (l = 1; l <= 10; l++) {
    for (c = 1; c <= 20; c++) {
      mat[l][c].vizinhos = qntbombasvizinhas(l, c);
    }
  }
}

void imprimir() { //imprime a matriz 
  printf("\n\n\t  ");
  for (l = 1; l <= 20; l++) {
    if (l < 10) {
      printf("   %d", l);
    } else {
      printf("  %d", l);
    }
  }
  printf("\n\t   --------------------------------------------------------------------------------- \n");
  for (l = 1; l <= 10; l++) {
    if (l < 10) {
      printf("\t%d  |", l);
      for (c = 1; c <= 20; c++) {
        if (mat[l][c].aberta) {
          if (mat[l][c].ebomba == 1) {
            printf(" * ");
          } else {
            printf(" %d ", mat[l][c].vizinhos);
          }
        } else {
          printf("   ");
        }
        printf("|");
      }
      printf("\n\t   --------------------------------------------------------------------------------- \n");
    } else {
      printf("\t%d |", l);
      for (c = 1; c <= 20; c++) {
        if (mat[l][c].aberta) {
          if (mat[l][c].ebomba == 1) {
            printf(" * ");
          } else {
            printf(" %d ", mat[l][c].vizinhos);
          }
        } else {
          printf("   ");
        }
        printf("|");
      }
      printf("\n\t   --------------------------------------------------------------------------------- \n");
    }
  }
}

void abrir(int l, int c) { //recebe o poto da matriz e faz a ação de abrir as casas, tanto a escolhida, preenchendo no campo "abertas", enquato abre as casas "vazias" ao redor, recursivamente
  if (coordval(l, c) == 1 && mat[l][c].aberta == 0) {

    mat[l][c].aberta = 1;

    if (mat[l][c].vizinhos == 0) {
      abrir(l - 1, c);
      abrir(l + 1, c);
      abrir(l, c - 1);
      abrir(l, c + 1);
      abrir(l + 1, c + 1);
      abrir(l + 1, c - 1);
      abrir(l - 1, c + 1);
      abrir(l - 1, c - 1);
    }
  }
}

int ganha() { //verifica toda a matriz e retorna a quantidade de casas fechadas e sem bombas, se todas as fechadas tiverem bombas a vitória é declarada mais à frente
  int qnt = 0;

  for (l = 1; l <= 10; l++) {
    for (c = 1; c <= 20; c++) {
      if (mat[l][c].aberta == 0 && mat[l][c].ebomba == 0) {
        qnt++;
      }
    }
  }
  return qnt;
}

void dica(int lin, int col) { //percorre a matriz e diz a casa aberta com menor probabilidade de ter uma bomba próxima
  int cont = 0, aberta = 0;
  for (l = 1; l <= 10; l++) {
    for (c = 1; c <= 20; c++) {
      if (mat[l][c].aberta == 1) {
        if (mat[l][c].vizinhos > 0 && mat[l][c].vizinhos < 3) {
          if (coordval(l + 1, c) == 1 && mat[l + 1][c].aberta == 0) {
            lin = l + 1;
            col = c;
            cont++;
            aberta++;
            break;
          } else if (coordval(l - 1, c) == 1 && mat[l - 1][c].aberta == 0) {
            lin = l - 1;
            col = c;
            cont++;
            aberta++;
            break;
          } else if (coordval(l, c + 1) == 1 && mat[l][c + 1].aberta == 0) {
            lin = l;
            col = c + 1;
            cont++;
            aberta++;
            break;
          } else if (coordval(l, c - 1) == 1 && mat[l][c - 1].aberta == 0) {
            lin = l;
            col = c - 1;
            cont++;
            aberta++;
            break;
          } else if (coordval(l + 1, c - 1) == 1 && mat[l + 1][c - 1].aberta == 0) {
            lin = l + 1;
            col = c - 1;
            cont++;
            aberta++;
            break;
          } else if (coordval(l - 1, c + 1) == 1 && mat[l - 1][c + 1].aberta == 0) {
            lin = l - 1;
            col = c + 1;
            cont++;
            aberta++;
            break;
          } else if (coordval(l + 1, c + 1) == 1 && mat[l + 1][c + 1].aberta == 0) {
            lin = l + 1;
            col = c + 1;
            cont++;
            aberta++;
            break;
          } else if (coordval(l - 1, c - 1) == 1 && mat[l - 1][c - 1].aberta == 0) {
            lin = l - 1;
            col = c - 1;
            cont++;
            aberta++;
            break;
          }
        }
      }
    }
    if (aberta != 0) {
      aberta = 0;
      break;
    }
  }
  if (cont == 0) {
    lin = rand() % 10;
    col = rand() % 20;
    cont = 0;
  }
  printf("Eu escolheria: %d %d", lin, col);
}

void BOT() { //joga o jogo sozinho usando a mesma lógica da dica
  int lin, col, men;
  do {
    imprimir();
    do {
      int cont = 0, aberta = 0;
      for (l = 1; l <= 10; l++) {
        for (c = 1; c <= 20; c++) {
          if (mat[l][c].aberta == 1) {
            if (mat[l][c].vizinhos > 0 && mat[l][c].vizinhos < 3) {
              if (coordval(l + 1, c) == 1 && mat[l + 1][c].aberta == 0) {
                lin = l + 1;
                col = c;
                cont++;
                aberta++;
                break;
              } else if (coordval(l - 1, c) == 1 && mat[l - 1][c].aberta == 0) {
                lin = l - 1;
                col = c;
                cont++;
                aberta++;
                break;
              } else if (coordval(l, c + 1) == 1 && mat[l][c + 1].aberta == 0) {
                lin = l;
                col = c + 1;
                cont++;
                aberta++;
                break;
              } else if (coordval(l, c - 1) == 1 && mat[l][c - 1].aberta == 0) {
                lin = l;
                col = c - 1;
                cont++;
                aberta++;
                break;
              } else if (coordval(l + 1, c - 1) == 1 && mat[l + 1][c - 1].aberta == 0) {
                lin = l + 1;
                col = c - 1;
                cont++;
                aberta++;
                break;
              } else if (coordval(l - 1, c + 1) == 1 && mat[l - 1][c + 1].aberta == 0) {
                lin = l - 1;
                col = c + 1;
                cont++;
                aberta++;
                break;
              } else if (coordval(l + 1, c + 1) == 1 && mat[l + 1][c + 1].aberta == 0) {
                lin = l + 1;
                col = c + 1;
                cont++;
                aberta++;
                break;
              } else if (coordval(l - 1, c - 1) == 1 && mat[l - 1][c - 1].aberta == 0) {
                lin = l - 1;
                col = c - 1;
                cont++;
                aberta++;
                break;
              }
            }
          }
        }
        if (aberta != 0) {
          aberta = 0;
          break;
        }
      }
      if (cont == 0) {
        lin = rand() % 10;
        col = rand() % 20;
        cont = 0;
      }

    } while (coordval(l, c) == 1 && mat[l][c].aberta == 0); //se repete enquanto a coordenada for valida e a casa escolhida esteja fechada

    abrir(lin, col); 

  } while (mat[lin][col].ebomba == 0); //se repete enquanto uma bomba não for aberta

  if (mat[lin][col].ebomba == 1) {
    imprimir();
    printf("\nOLHA A BOMBA!!!");
  } else {
    imprimir();
    printf("\nOLHA, CONSEGUIU SAIR COM AS DUAS PERNAS, VOCÊ VENCEU!");
  }
}

void jogadas() { //
  int lin, col, x, z, d, token = 0, filler = 0;
  double cronometro = 0.0;
  time_t inicio, fim;
  char nome[50];

  printf("\nBem vindo ao campo minado, deseja ativar o bot? Digite 1 para sim e 0 para não ");
  scanf("%d", & x);

  if (x == 0) {
    printf("\nQuer ativar as dicas? Digite 1 para sim e 0 para não: ");
    scanf("%d", & z);
  }

  if (x == 0) { //sem bot
    if (z == 0) { //sem dica
      do {
        imprimir();
        do {
          printf("\nQual a sua jogada? (Lembrando que primero a linha, depois coluna, separados por um espaço): ");
          scanf("%d %d", & lin, & col); //escanea as jogadas
          token++;
          if (token == 1) { //se for a primeira jogada começa o timer
            time( & inicio);
          }
          if (coordval(lin, col) == 0) { //verifica se o ponto está dentro da matriz
            printf("\nEssa coordenada não pode...");
          }
        } while (coordval(lin, col) == 0 || mat[lin][col].aberta == 1); //repete o de cima enquanto a coordenada estiver fora da matriz ou a casa já esteja aberta

        abrir(lin, col);

      } while (ganha() != 0 && mat[lin][col].ebomba == 0); //repete enquanto o ponto escolhido não tenha bomba e ganha seja diferente de zero, pois caso seja igual todas as casas fechadas serão bombas e o jogador vence

      if (mat[lin][col].ebomba == 1) { //indica derrota
        printf("\nOLHA A BOMBA!!!");
        imprimir();
      } else { //indica vitória
        printf("\nOLHA, CONSEGUIU SAIR COM AS DUAS PERNAS, VOCÊ VENCEU!");
        imprimir();
        filler++;
      }
      time( & fim); //finaliza o cronômetro
      cronometro = difftime(fim, inicio);//define a variável cronômetro
      printf("tempo: %.2lf", cronometro);
      if (filler != 0){
        FILE *recorde;
        recorde = fopen("recorde", "w");
        char nome[50];
        printf("\n assinatura:");
        setbuf(stdin,NULL);
        fgets(nome, 49, stdin);
        fprintf(recorde, " %s, tempo de jogo: %.2lf", nome, cronometro);
        fclose(recorde); // abre e fecha um arquivo com o recorde do jogador.
      }
    } else { //com dica (faz o mesmo de cima só que pede dicas)
      do {
        imprimir();
        do {
          printf("\nQuer uma dica? 1 para sim 0 para não: ");
          scanf("%d", & d);
          if (d == 1) {
            dica(lin, col);
          }
          printf("\nQual a sua jogada? (Lembrando que primero a linha, depois coluna, separados por um espaço): ");
          scanf("%d %d", & lin, & col);

          if (coordval(lin, col) == 0) {
            printf("\nEssa coordenada não pode...");
          }
        } while (coordval(lin, col) == 0 || mat[lin][col].aberta == 1);

        abrir(lin, col);
      } while (ganha() != 0 && mat[lin][col].ebomba == 0);

      if (mat[lin][col].ebomba == 1) {
        printf("\nOLHA A BOMBA!!!");
        imprimir();
      } else {
        printf("\nOLHA, CONSEGUIU SAIR COM AS DUAS PERNAS, VOCÊ VENCEU!");
        imprimir();
        filler++;
      }
      time( & fim);
      cronometro = difftime(fim, inicio);
      printf("tempo: %.2lf", cronometro);
      if (filler != 0){
        FILE *recorde;
        recorde = fopen("recorde", "w");
        char nome[50];
        printf("\n assinatura:");
        setbuf(stdin,NULL);
        fgets(nome, 49, stdin);
        fprintf(recorde, " %s, tempo de jogo: %.2lf", nome, cronometro);
        fclose(recorde); // abre e fecha um arquivo com o recorde do jogador.
      }
      // abre e fecha um arquivo com o recorde do jogador.
    }
  } else { //com bot
    BOT();
  }
}
