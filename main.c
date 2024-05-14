#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include "head.h"

int main(void) { //com todas as funções a serem chamadas em ordem de execução

  inicializar();
  
  sortearbombas();
  
  contbombas();
  
  jogadas();

  return 0;
}

