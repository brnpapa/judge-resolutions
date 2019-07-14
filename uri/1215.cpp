/*
   graph | binary search tree (BST)
   problem: andy's first dictionary
   author: @brnpapa
*/
#include <iostream>
#include <ctype.h>
#include <string.h>
#define MAX 201
using namespace std;

typedef struct llde {
   char info[MAX];
   struct llde *esq, *dir;
} *Tnode;

void insere(Tnode *arv, char info[MAX]) {
   if (*arv == NULL) {
      Tnode p = (Tnode)malloc(sizeof(struct llde));
      strcpy(p->info, info);
      p->dir = p->esq = NULL;
      *arv = p;
   }
   else {
      if (strcmp(info, (*arv)->info) > 0)
         insere(&(*arv)->dir, info);
      if (strcmp(info, (*arv)->info) < 0)
         insere(&(*arv)->esq, info);
   }
}
void percursoInfixo(Tnode arv) {
   if (arv != NULL) {
      percursoInfixo(arv->esq);
      printf("%s\n", arv->info);
      percursoInfixo(arv->dir);
   }
}

int main() {
   char str[MAX], palavra[MAX];
   Tnode arv = NULL;
   while (cin >> str) {
      int c = 0;
      while (true) {
         //até o próximo caracter alfanumérico
         while (!isalpha(str[c]) && c < strlen(str))
            c++;
         if (c == strlen(str))
            break; //não tem mais palavras em str

         //até o próximo caracter não alfanumérico
         int i = 0;
         while (isalpha(str[c]) && c < strlen(str))
            palavra[i++] = tolower(str[c++]);
         palavra[i++] = '\0';

         insere(&arv, palavra);
      }
   }
   percursoInfixo(arv);
   return 0;
}