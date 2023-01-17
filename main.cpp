/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: lucas
 *
 * Created on 1 de janeiro de 2023, 14:05
 */

#include <bits/stdc++.h>
using namespace std;

typedef struct no { // estrutura no para composicao da arvore
  int valor;
  struct no *direita, *esquerda;
} NoArv;

NoArv *inserir_versao_1(NoArv *raiz, int num) { // insercao com retorno e recursao
  if (raiz == NULL) {
    NoArv*aux = malloc(sizeof(NoArv));
    aux->valor = num;
    aux->direita = NULL;
    aux->esquerda = NULL;
    return aux;
  } else {
    if (num < raiz->valor) {
      raiz->esquerda = inserir_versao_1(raiz->esquerda, num);
    } else {
      raiz->direita = inserir_versao_1(raiz->direita, num);
    }
    return raiz;
  }
}

int altura(NoArv *raiz) { // altura da arvore
  if (raiz == NULL) {
    return -1;
  } else {
    int esq = altura(raiz->esquerda);
    int dir = altura(raiz->direita);
    if (esq > dir) {
      return esq + 1;
    } else {
      return dir + 1;
    }
  }
}

int quantidade_nos(NoArv *raiz) { // quantidade de nos da arvore
  if (raiz == NULL) {
    return 0;
  } else {
    return 1 + quantidade_nos(raiz->esquerda) + quantidade_nos(raiz->direita);
  }
}

int quantidade_folhas(NoArv *raiz) { // quantidade de folhas da arvore
  if (raiz == NULL) {
    return 0;
  } else if (raiz->esquerda == NULL && raiz->direita == NULL) {
    return 1;
  } else {
    return quantidade_folhas(raiz->esquerda) + quantidade_folhas(raiz->direita);
  }
}

NoArv *remover(NoArv *raiz, int chave) { // remove no da arvore
  if (raiz == NULL) {
    printf("valor nao encontrado\n");
    return NULL;
  } else {
    if (raiz->valor == chave) { // remocao se nao tiiver filhos
      if (raiz->esquerda == NULL && raiz->direita == NULL) {
        free(raiz);
        printf("Elemento folha removido:%d\n", chave);
        return NULL;
      } else { // remocao para quando tiver 2 filhos
        if (raiz->esquerda != NULL && raiz->direita != NULL) {
          NoArv *aux = raiz->esquerda;
          while (aux->direita != NULL) {
            aux = aux->direita;
          }
          raiz->valor = aux->valor;
          aux->valor = chave;
          printf("elemento trocado: %d !\n", chave);
          raiz->esquerda = remover(raiz->esquerda, chave);
          return raiz;

        } else { // remocao para apenas um filho
          NoArv *aux;
          if (raiz->esquerda != NULL) {
            aux = raiz->esquerda;
          } else {
            aux = raiz->direita;
          }
          free(raiz);
          printf("elemento com 1 filho removido: %d !\n", chave);
          return aux;
        }
      }

    } else {
      if (chave < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, chave);
      else
        raiz->direita = remover(raiz->direita, chave);
      return raiz;
    }
  }
}

void imprimir_versao_1(NoArv *raiz) { // imprime em ordem de insercao
  if (raiz) {
    printf("%d  ", raiz->valor);
    imprimir_versao_1(raiz->esquerda);
    imprimir_versao_1(raiz->direita);
  }
}

void imprimir_versao_2(NoArv *raiz) { // imprime em ordem crescente
  if (raiz) {
    imprimir_versao_2(raiz->esquerda);
    printf("%d  ", raiz->valor);
    imprimir_versao_2(raiz->direita);
  }
}

void inserir_versao_2(NoArv **raiz,int num) { // insere sem retorno e com recursao
  if (*raiz == NULL) {
    *raiz = malloc(sizeof(NoArv));
    (*raiz)->valor = num;
    (*raiz)->direita = NULL;
    (*raiz)->esquerda = NULL;
  } else {
    if (num < (*raiz)->valor) {
      inserir_versao_2(&((*raiz)->esquerda), num);
    } else {
      inserir_versao_2(&((*raiz)->direita), num);
    }
  }
}

void inserir_versao_3(NoArv **raiz,int num){ // insere sem retorno e sem recursao
  NoArv *aux = *raiz;

  while (aux) {
    if (num < aux->valor) {
      raiz = &aux->esquerda;
    } else {
      raiz = &aux->direita;
    }
    aux = *raiz;
  }

  aux = malloc(sizeof(NoArv));
  aux->valor = num;
  aux->direita = NULL;
  aux->esquerda = NULL;
  *raiz = aux;
}

NoArv *buscar_versao_1(NoArv *raiz, int num) { // busca recursiva
  if (raiz) {
    if (num == raiz->valor) {
      return raiz;
    } else if (num < raiz->valor) {
      return buscar_versao_1(raiz->esquerda, num);
    } else {
      return buscar_versao_1(raiz->direita, num);
    }
  }
  return NULL;
}

NoArv *buscar_versao_2(NoArv *raiz, int num) { // busca sem recursao
  while (raiz) {
    if (num < raiz->valor) {
      raiz = raiz->esquerda;
    } else if (num > raiz->valor) {
      raiz = raiz->direita;
    } else {
      return raiz;
    }
  }
  return NULL;
}

int main(void) {
  NoArv *raiz = NULL;
  NoArv *busca = NULL;
  int opcao, valor;

  do {
    printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Buscar\n\t4 - "
           "Altura\n\t5 - quantidade\n\t6 - Folhas\n\t7 - remover");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("\n\tDigite um valor:");
      scanf("%d", &valor);
      inserir_versao_3(&raiz, valor);
      break;

    case 2:
      printf("\n\tPrimeirra impressao:\n\t");
      imprimir_versao_1(raiz);
      printf("\n");
      printf("\n\tSegunda impressao:\n\t");
      imprimir_versao_2(raiz);
      printf("\n");

      break;
    case 3:
      printf("\n\t Digite um valor para ser procurado");
      scanf("%d", &valor);

      busca = buscar_versao_2(raiz, valor);
      if (busca) {
        printf("\n\tValor encontrado:\n\t");

      } else
        printf("\n\tValor NAO encontrado:\n\t");

      break;

    case 4:
      printf("\n\tAltura da arvore : %d\n\n", altura(raiz));
      break;

    case 5:
      printf("\nquantidade de nos: %d\n", quantidade_nos(raiz));
      break;

    case 6:
      printf("quantidade de folhas da arvore %d\n", quantidade_folhas(raiz));
      break;

    case 7:
      printf("\t");
      imprimir_versao_2(raiz);
      printf("\n\tDigite o valor a ser removido:");
      scanf("%d  ", &valor);
      raiz = remover(raiz, valor);
      break;

    default:
      if (opcao != 0)
        printf("\n\tOpcao invalida\n");
    }
  } while (opcao != 0);
  return 0;
}
